/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:34:13 by danielji          #+#    #+#             */
/*   Updated: 2025/11/24 23:18:23 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Child process:
- Redirect input & output
- Close unused fd
- Check if command is builtin, is found, is executable
- Execute command. If execve fails, print error and exit */
void	child_process(t_cmd *cmd, int temp_fd, int pipefd[2], char **envp)
{
	if (cmd->input == -1 || cmd->output == -1)
	{
		//! Should close child fds?
		exit(EXIT_FAILURE);
	}
	redirect_in(temp_fd, cmd->input, is_first(cmd));
	redirect_out(pipefd, cmd->output, is_last(cmd));
	close_child_fds(temp_fd, pipefd, is_last(cmd));
	if (is_builtin(cmd->cmd[0]))
	{
		exit(call_to_builtins(cmd, envp, NULL));//NULL == env_list, 
						  //not needed at this point of
						  //builtins (env, pwd, echo)
	}
	else if (is_executable(cmd->path, cmd->cmd[0]))
	{
		execve(cmd->path, cmd->cmd, envp);
		perror("execve");
		exit(126);
	}
}

/* Parent process:
- Close previous read end 
- Save current read end for next child
- Close current write end
- Reset `temp_fd` to `-1`
- If they were opened, close input & output files */
void	parent_process(t_cmd *cmd, int *temp_fd, int pipefd[2])
{
	if (*temp_fd != -1)
		safe_close(*temp_fd);
	if (!is_last(cmd))
	{
		*temp_fd = pipefd[READ_END];
		safe_close(pipefd[WRITE_END]);
	}
	else
		*temp_fd = -1;
	if (cmd->input != STDIN_FILENO)
		safe_close(cmd->input);
	if (cmd->output != STDOUT_FILENO)
		safe_close(cmd->output);
}

/* Initialize everything to `-1` to prevent bad `close` or `dup2` calls.
For each command in the command list:
- Create a pipe except on last command
- Fork process
- Return `-1` on error */
int	execute_cmd_list(t_cmd *cmd, char **envp, t_shell *data)
{
	int	pipefd[2];
	int	temp_fd;

	temp_fd = -1;
	pipefd[READ_END] = -1;
	pipefd[WRITE_END] = -1;
	while (cmd)
	{
		if (cmd->is_forkable == 0 && is_first(cmd) && is_last(cmd))
		{
			cmd->status = call_to_builtins(cmd, envp, data->env_list);
			break ;
		}
		if (cmd->is_heredoc && heredoc(cmd) < 0)
			return (perror("heredoc"), -1);
		if (!is_last(cmd) && (pipe(pipefd) < 0))
			return (perror("pipe"), -1);
		cmd->pid = fork();
		if (cmd->pid < 0)
			return (perror("fork"), close_pipe(pipefd), -1);
		if (cmd->pid == 0)
			child_process(cmd, temp_fd, pipefd, envp);
		parent_process(cmd, &temp_fd, pipefd);
		cmd = cmd->next;
	}
	return (0);
}

/* Wait for each child process and return the
exit status of the last child process */
int	wait_children(t_cmd *cmd)
{
	int	wstatus;
	int	last_status;

	while (cmd)
	{
		if (cmd->is_forkable)
		{
			if (waitpid(cmd->pid, &wstatus, 0) < 0)
				perror("waitpid");
			if (WIFEXITED(wstatus))
				cmd->status = WEXITSTATUS(wstatus);
			else if (WIFSIGNALED(wstatus))
				cmd->status = 128 + WTERMSIG(wstatus);
		}
		last_status = cmd->status;
		cmd = cmd->next;
	}
	return (last_status);
}

/* For each command:
- Assign reference to shell data
- Find executable path (except builtins)
- Assign `is_builtin` and `is_heredoc`*/
void	preprocess_cmdlist(t_shell *data, char **paths)
{
	t_cmd	*cmd;

	cmd = data->cmd_list;
	while (cmd)
	{
		cmd->shell = data;
		if (cmd->cmd[0] && is_builtin(cmd->cmd[0]))
		{
			if (!is_forkable(cmd->cmd[0]))
				cmd->is_forkable = 0;
		}
		else
			cmd->path = get_exec_path(cmd->cmd[0], paths);
		if (cmd->is_heredoc)
			cmd->env_list = data->env_list;
		cmd = cmd->next;
	}
}

/* - Find paths
- Call `execute_cmd_list` to run commands
- Get exit status from `wait_children`
- Set last exit status and free allocated memory*/
void	execution(t_shell *data)
{
	char	**paths;
	char	**envp;
	int		status;

	paths = get_path_dirs(data->env_list);
	envp = get_envp(data->env_list);
	preprocess_cmdlist(data, paths);
	execute_cmd_list(data->cmd_list, envp, data);
	status = wait_children(data->cmd_list);
	set_last_exit_status(data->env_list, status);
	free_strings_array(paths);
	free_strings_array(envp);
	ft_cmdlist_clear(&(data->cmd_list));
}
