/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution-child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 22:52:00 by danielji          #+#    #+#             */
/*   Updated: 2025/11/11 22:52:00 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	safe_dup2(int oldfd, int newfd)
{
	if (oldfd >= 0 && newfd >= 0 && dup2(oldfd, newfd) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
}

/* Close `fd` only if it's `0` or greater */
void	safe_close(int fd)
{
	if (fd >= 0 && close(fd) < 0)
	{
		perror("close");
		exit(EXIT_FAILURE);
	}
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
