/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:34:13 by danielji          #+#    #+#             */
/*   Updated: 2025/11/16 19:28:42 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Child process:
- Redirect input & output
- Close unused fd
- Execute command. If execve fails, print error and exit */
void	child_process(t_cmd *cmd, int temp_fd, int pipefd[2], char **envp)
{
	if (cmd->input == -1 || cmd->output == -1)
		exit(EXIT_FAILURE);
	redirect_in(temp_fd, cmd->input, is_first(cmd));
	redirect_out(pipefd, cmd->output, is_last(cmd));
	close_child_fds(temp_fd, pipefd, is_last(cmd));
	execve(cmd->path, cmd->cmd, envp);
	perror("execve");
	exit(EXIT_FAILURE);
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

int	heredoc(t_cmd *cmd)
{
	int		i;
	int		here_pipe[2];
	char	*line;

	i = 0;
	here_pipe[READ_END] = -1;
	here_pipe[WRITE_END] = -1;
	while (cmd->delimiters[i])
	{
		if (here_pipe[READ_END] != -1)
			safe_close(here_pipe[READ_END]);
		if (here_pipe[WRITE_END] != -1)
			safe_close(here_pipe[WRITE_END]);
		if ((pipe(here_pipe) < 0))
			return (perror("heredoc pipe"), -1);
		line = NULL;
		while (1)
		{
			line = readline("> ");
			if (ft_strncmp(cmd->delimiters[i], line, ft_strlen(line) + 1) == 0)
			{
				free(line);
				break ;
			}
			ft_putendl_fd(line, here_pipe[WRITE_END]);
			free(line);
		}
		i++;
	}
	safe_close(here_pipe[WRITE_END]);
	cmd->input = here_pipe[READ_END];
	return (0);
}

/* Initialize everything to `-1` to prevent bad `close` or `dup2` calls.
For each command in the command list:
- Create a pipe except on last command
- Fork process
- Return `-1` on error */
int	execute_cmd_list(t_cmd *cmd, char **envp)
{
	int	pipefd[2];
	int	temp_fd;

	temp_fd = -1;
	pipefd[READ_END] = -1;
	pipefd[WRITE_END] = -1;
	while (cmd)
	{
		if (cmd->is_builtin)
		{
			printf("%s is builtin\n", cmd->cmd[0]);
			// TODO
			cmd = cmd->next;
			continue ;
		}
		if (cmd->is_heredoc)
		{
			if (heredoc(cmd) < 0)
				return (perror("heredoc"), -1);
		}
		if (!is_last(cmd) && (pipe(pipefd) < 0))
			return (perror("pipe"), -1);
		cmd->pid = fork();
		if (cmd->pid < 0)
		{
			perror("fork");
			close_pipe(pipefd);
			return (-1);
		}
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
	int	status;

	while (cmd)
	{
		if (cmd->is_builtin == 0)
		{
			if (waitpid(cmd->pid, &status, 0) < 0)
				perror("waitpid");
		}
		cmd = cmd->next;
	}
	return (WEXITSTATUS(status));
}

void	execution(t_shell *data)
{
	t_cmd	*cmd;
	char	**paths;
	char	**envp;
	int		status;

	cmd = data->cmd_list;
	//!print_cmd_list(cmd); //!debug
	paths = get_path_dirs(data->env_list);
	envp = get_envp(data->env_list);
	while (cmd)
	{
		if (cmd->cmd[0] && is_builtin(cmd->cmd[0]))
			cmd->is_builtin = 1;
		else
			cmd->path = get_exec_path(cmd->cmd[0], paths);
		cmd = cmd->next;
	}
	execute_cmd_list(data->cmd_list, envp);
	status = wait_children(data->cmd_list);
	free_strings_array(paths);
	free_strings_array(envp);
	ft_cmdlist_clear(&(data->cmd_list));
	// TODO: return status??
	(void)status;
}
