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
#include "execution.h"

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

void	redirect_in(int temp_fd, int input, int is_first)
{
	if (is_first)
	{
		if (input != STDIN_FILENO)
			dup2(input, STDIN_FILENO);
	}
	else
	{
		dup2(temp_fd, input);
		close(temp_fd);
	}
}

void	redirect_out(int pipefd[2], int output, int is_last)
{
	if (is_last)
	{
		if (output != STDOUT_FILENO)
			dup2(output, STDOUT_FILENO);
	}
	else
	{
		dup2(pipefd[WRITE_END], output);
		close(pipefd[READ_END]);
		close(pipefd[WRITE_END]);
	}
}
