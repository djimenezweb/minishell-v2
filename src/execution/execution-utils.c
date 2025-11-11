/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution-utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:08:09 by danielji          #+#    #+#             */
/*   Updated: 2025/11/10 18:08:09 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe(int pipefd[2])
{
	close(pipefd[READ_END]);
	close(pipefd[WRITE_END]);
}

int	is_last(t_cmd *cmd)
{
	if (cmd->next == NULL)
		return (1);
	return (0);
}

int	is_first(t_cmd *cmd)
{
	if (cmd->prev == NULL)
		return (1);
	return (0);
}

// TODO: Should add a condition if pipe doesn't exist!
void	redirect_in(int temp_fd, int input)
{
	if (input != STDIN_FILENO)
		dup2(input, STDIN_FILENO);
	else
		dup2(temp_fd, input);
	if (temp_fd != -1)
		close(temp_fd);
}

// TODO: Should add a condition if pipe doesn't exist!
void	redirect_out(int pipefd[2], int output)
{
	if (output != STDOUT_FILENO)
		dup2(output, STDOUT_FILENO);
	else
		dup2(pipefd[WRITE_END], output);
	if (pipefd[READ_END] > 0 && pipefd[WRITE_END] > 0)
		close_pipe(pipefd);
}
