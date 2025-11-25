/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution-utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:08:09 by danielji          #+#    #+#             */
/*   Updated: 2025/11/25 14:17:55 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe(int pipefd[2])
{
	safe_close(pipefd[READ_END]);
	safe_close(pipefd[WRITE_END]);
}

void	init_pipe(int pipefd[2])
{
	pipefd[READ_END] = -1;
	pipefd[WRITE_END] = -1;
}

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

void	print_error_exit(char *cmd, char *msg, int exit_status)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(exit_status);
}
