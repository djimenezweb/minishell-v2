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

/*- Child no longer needs `temp_fd`
- Child never reads from the pipe
- Child doesn't write if it's the last command */
void	close_child_fds(int temp_fd, int pipefd[2], int last)
{
	if (temp_fd != -1)
		close(temp_fd);
	if (pipefd[READ_END] != -1)
		close(pipefd[READ_END]);
	if (last && pipefd[WRITE_END] != -1)
		close(pipefd[WRITE_END]);
}

/* Read from file if input is other than STDIN
Read from temp_fd except if it's the first command */
void	redirect_in(int temp_fd, int input, int first)
{
	if (input != STDIN_FILENO)
		dup2(input, STDIN_FILENO);
	else if (!first && temp_fd != -1)
		dup2(temp_fd, STDIN_FILENO);
}

/* Write to file if output is other than STDOUT
Write to pipe except if it's the last command */
void	redirect_out(int pipefd[2], int output, int last)
{
	if (output != STDOUT_FILENO)
		dup2(output, STDOUT_FILENO);
	else if (!last && pipefd[WRITE_END] != -1)
		dup2(pipefd[WRITE_END], output);
}
