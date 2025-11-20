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
	safe_close(pipefd[READ_END]);
	safe_close(pipefd[WRITE_END]);
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

void	command_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	exit(127);
}

void	permission_denied(char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": permission denied", STDERR_FILENO);
	exit(126);
}
