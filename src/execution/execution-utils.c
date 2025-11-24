/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution-utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:08:09 by danielji          #+#    #+#             */
/*   Updated: 2025/11/24 17:37:22 by danielji         ###   ########.fr       */
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

void	print_error_exit(char *cmd, char *msg, int exit_status)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(exit_status);
}

int	is_directory(const char* path)
{
	struct stat	file_status;

	if (stat(path, &file_status) < 0)
	{
		perror("minishell: stat");
		exit(126);
	}
	if (S_ISDIR(file_status.st_mode))
		return (1);
	return (0);
}

int	is_executable(char *path, char *cmd)
{
	if (!path || !path[0])
		print_error_exit(cmd, "command not found", 127);
	else if (access(path, F_OK) < 0)
		print_error_exit(cmd, "No such file or directory", 127);
	else if (is_directory(path))
		print_error_exit(cmd, "Is a directory", 126);
	else if (access(path, X_OK) != 0)
		print_error_exit(cmd, "permission denied", 126);
	return (1);
}
