/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution-utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:04:33 by danielji          #+#    #+#             */
/*   Updated: 2025/11/27 09:18:32 by danielji         ###   ########.fr       */
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
		return (-1);
		//exit(126);
	}
	if (S_ISDIR(file_status.st_mode))
		return (1);
	return (0);
}

int	is_executable(t_cmd *cmd)
{
	if (!cmd->path || !cmd->path[0])
	{
		print_exec_error(cmd->cmd[0], "command not found");
		free_shell(cmd->shell, 127);
	}
	else if (access(cmd->path, F_OK) < 0)
	{
		print_exec_error(cmd->cmd[0], "No such file or directory");
		free_shell(cmd->shell, 127);
	}
	else if (is_directory(cmd->path))
	{
		print_exec_error(cmd->cmd[0], "Is a directory");
		free_shell(cmd->shell, 126);
	}
	else if (access(cmd->path, X_OK) != 0)
	{
		print_exec_error(cmd->cmd[0], "permission denied");
		free_shell(cmd->shell, 126);
	}
	return (1);
}
