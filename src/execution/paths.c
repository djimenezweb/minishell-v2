/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:41:38 by danielji          #+#    #+#             */
/*   Updated: 2025/11/16 18:48:45 by enrgil-p         ###   ########.fr       */
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
		return (NULL);
	path = get_env_value(env_list, "PATH");
	if (!path)
		return (NULL);
	else
		paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

/* Return the first valid executable path of `cmd` in `paths` directories.
Return `cmd` if it contains a `/` or if `paths` is empty.
If not a valid command, return `NULL` */
//! Should return ft_strdup("") instead of NULL ????
char	*get_exec_path(char *cmd, char **paths)
{
	int		i;
	char	*cmd_slash;
	char	*exec_path;

	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd, SLASH) != NULL || !paths || !paths[0])
		return (ft_strdup(cmd));
	i = 0;
	cmd_slash = ft_strjoin("/", cmd);
	while (paths[i])
	{
		exec_path = ft_strjoin(paths[i], cmd_slash);
		if (access(exec_path, F_OK) == 0)
			return (free(cmd_slash), exec_path);
		free(exec_path);
		i++;
	}
	free(cmd_slash);
	return (NULL);
}

/* Return `1` if the command `cmd` should be executed in a forked process.
Only builtins `env`, `pwd` and `echo` should be forked. */
int	is_forkable(char *cmd)
{
	size_t	len;

	len = ft_strlen(cmd);
	if (len == 3)
	{
		if (!ft_strncmp("env", cmd, len) || !ft_strncmp("pwd", cmd, len))
			return (1);
	}
	else if (len == 4)
	{
		if (!ft_strncmp("echo", cmd, len))
			return (1);
	}
	return (0);
}

/* Check if the string `cmd` is one of the builtin commands:
`cd`, `pwd`, `env`, `echo`, `exit`, `unset`, or `export`, */
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
