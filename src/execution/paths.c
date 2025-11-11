/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:41:38 by danielji          #+#    #+#             */
/*   Updated: 2025/11/06 15:43:40 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Return an array of directory strings */
char	**get_path_dirs(t_env_var *env_list)
{
	char	*path;
	char	**paths;

	path = NULL;
	paths = NULL;
	if (!env_list)
	{
		//TODO
	}
	path = get_env_value(env_list, "PATH");
	if (path == NULL)
	{
		// TODO
	}
	else
		paths = ft_split(path, ':');
	if (paths == NULL)
	{
		// TODO
	}
	return (paths);
}

/* Add a `/` to the beginning of a string `str` if it's missing. */
static char	*add_slash(char *str)
{
	if (ft_strnstr(str, "/", 1))
		return (ft_strdup(str));
	return (ft_strjoin("/", str));
}

/* Return the first valid executable path of `cmd` in `paths` directories.
If not a valid command, return `NULL` */
// TODO: Too many lines
char	*get_exec_path(char *cmd, char **paths)
{
	int		i;
	char	*cmd_slash;
	char	*exec_path;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	if (!paths || !paths[0])
	{
		return (cmd);
	}
	if (!cmd)
	{
		// return (ft_strdup("")); ??
		return (NULL);
	}
	i = 0;
	cmd_slash = add_slash(cmd);
	while (paths[i])
	{
		exec_path = ft_strjoin(paths[i], cmd_slash);
		if (access(exec_path, X_OK) == 0)
		{
			free(cmd_slash);
			return (exec_path);
		}
		free(exec_path);
		i++;
	}
	free(cmd_slash);
	return (NULL);
}

int	is_builtin(char *cmd)
{
	size_t	len;

	len = ft_strlen(cmd);
	if (len == 2 && !ft_strncmp("cd", cmd, len))
		return (1);
	else if (len == 3)
	{
		if (!ft_strncmp("pwd", cmd, len) || !ft_strncmp("env", cmd, len))
			return (1);
	}
	else if (len == 4)
	{
		if (!ft_strncmp("echo", cmd, len) || !ft_strncmp("exit", cmd, len))
			return (1);
	}
	else if (len == 5 && !ft_strncmp("unset", cmd, len))
		return (1);
	else if (len == 6 && !ft_strncmp("export", cmd, len))
		return (1);
	return (0);
}
