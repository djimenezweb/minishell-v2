/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution-child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 22:52:00 by danielji          #+#    #+#             */
/*   Updated: 2025/11/27 12:30:25 by danielji         ###   ########.fr       */
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
	if (!cmd->cmd || !cmd->cmd[0])
	{
		close_child_fds(temp_fd, pipefd, is_last(cmd));
		free_shell(cmd->shell, EXIT_SUCCESS);
	}
	if (cmd->input == -1 || cmd->output == -1)
	{
		close_child_fds(temp_fd, pipefd, is_last(cmd));
		free_shell(cmd->shell, EXIT_FAILURE);
	}
	redirect_in(temp_fd, cmd->input, is_first(cmd));
	redirect_out(pipefd, cmd->output, is_last(cmd));
	close_child_fds(temp_fd, pipefd, is_last(cmd));
	if (is_builtin(cmd->cmd[0]))
		free_shell(cmd->shell, call_to_builtins(cmd, envp, NULL));
	else if (is_executable(cmd))
	{
		child_signals();
		execve(cmd->path, cmd->cmd, envp);
		perror("execve");
		free_shell(cmd->shell, 126);
	}
}

/* Read from file if `input` is other than STDIN
Read from `temp_fd` except if it's the first command */
void	redirect_in(int temp_fd, int input, int first)
{
	if (input != STDIN_FILENO)
		safe_dup2(input, STDIN_FILENO);
	else if (!first && temp_fd != -1)
		safe_dup2(temp_fd, STDIN_FILENO);
}

/* Write to file if `output` is other than STDOUT
Write to pipe except if it's the last command */
void	redirect_out(int pipefd[2], int output, int last)
{
	if (output != STDOUT_FILENO)
		safe_dup2(output, STDOUT_FILENO);
	else if (!last && pipefd[WRITE_END] != -1)
		safe_dup2(pipefd[WRITE_END], output);
}

/*- Always close `temp_fd` in the child
- Child never needs the pipe read end,
close it unless it has been already closed
- Close write end except if it's the last command
(parent already closed it) */
void	close_child_fds(int temp_fd, int pipefd[2], int last)
{
	if (temp_fd != -1)
		safe_close(temp_fd);
	if (pipefd[READ_END] != -1 && pipefd[READ_END] != temp_fd)
		safe_close(pipefd[READ_END]);
	if (!last && pipefd[WRITE_END] != -1)
		safe_close(pipefd[WRITE_END]);
}
