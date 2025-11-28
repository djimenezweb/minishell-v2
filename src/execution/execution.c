/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:34:13 by danielji          #+#    #+#             */
/*   Updated: 2025/11/28 12:21:15 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* - Find paths
- Call `execute_cmd_list` to run commands
- Get exit status from `wait_children`
- Set last exit status and free allocated memory*/
void	execution(t_shell *data)
{
	int	status;

	data->envp = get_envp(data->env_list);
	preprocess_cmdlist(data);
	execute_cmd_list(data->cmd_list, data);
	status = wait_children(data->cmd_list);
	set_last_exit_status(data->env_list, status);
	data->last_status = status;
	ft_cmdlist_clear(&(data->cmd_list));
}

/* For each command:
- Assign reference to shell data
- Find executable path (except builtins)
- Assign `is_builtin` and `is_heredoc`*/
void	preprocess_cmdlist(t_shell *data)
{
	t_cmd	*cmd;
	char	**paths;

	cmd = data->cmd_list;
	paths = get_path_dirs(data->env_list);
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
	if (paths != NULL)
	{
		free_strings_array(paths);
		paths = NULL;
	}
}

/* Initialize everything to `-1` to prevent bad `close` or `dup2` calls.
- Run builtin, Create pipe (if needed), Fork process
- Return `-1` on error */
int	execute_cmd_list(t_cmd *cmd, t_shell *data)
{
	int	temp_fd;
	int	pipefd[2];

	temp_fd = -1;
	init_pipe(pipefd);
	while (cmd)
	{
		if (!cmd->is_forkable && is_single_cmd(cmd))
		{
			cmd->status = call_to_builtins(cmd, data->envp, data->env_list);
			break ;
		}
		if (cmd->is_heredoc && heredoc(cmd) < 0)
			return (perror("minishell: heredoc"), -1);
		if (g_heredoc_signal == 2)
			break ;
		if (!is_last(cmd) && (pipe(pipefd) < 0))
			return (perror("minishell: pipe"), -1);
		cmd->pid = fork_cmd(cmd, &temp_fd, pipefd, data->envp);
		if (cmd->pid < 0)
			return (perror("minishell: fork"), close_pipe(pipefd), -1);
		cmd = cmd->next;
	}
	return (0);
}

pid_t	fork_cmd(t_cmd *cmd, int *temp_fd, int pipefd[2], char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (pid);
	if (pid == 0)
		child_process(cmd, *temp_fd, pipefd, envp);
	parent_process(cmd, temp_fd, pipefd);
	return (pid);
}

/* Parent process:
- Close previous read end 
- Save current read end for next child
- Close current write end
- Reset `temp_fd` to `-1`
- If they were opened, close input & output files */
void	parent_process(t_cmd *cmd, int *temp_fd, int pipefd[2])
{
	parent_ignore_sigint();
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
