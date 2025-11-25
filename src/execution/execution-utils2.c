/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution-utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:04:33 by danielji          #+#    #+#             */
/*   Updated: 2025/11/25 14:17:19 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	is_directory(const char *path)
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
