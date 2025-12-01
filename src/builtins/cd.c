/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 11:06:43 by danielji          #+#    #+#             */
/*   Updated: 2025/12/01 19:46:04 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_in_cd(char *message, int status, char **new_oldpwd)
{
	if (new_oldpwd)
		free(*new_oldpwd);
	if (message)
		ft_putendl_fd(message, STDERR_FILENO);
	return (status);
}

static int	call_to_getcwd(char **cwd)
{
	*cwd = getcwd(NULL, 0);
	if (*cwd == NULL)
		return (0);
	return (1);
}

static int	change_pwd(t_env_var *node, char **path_already_gotten)
{
	char	*new_path;

	if (node)
	{
		if (!path_already_gotten && !call_to_getcwd(&new_path))
			return (0);
		else if (path_already_gotten)
			new_path = *path_already_gotten;
		if (!change_env_value(node, new_path))
		{
			free(new_path);
			return (0);
		}
		free(new_path);
		return (1);
	}
	if (path_already_gotten)
		free(*path_already_gotten);
	return (0);
}

/*Check env_list looking for HOME. 
 * HOME must be set, if not, cd with args doesn't work*/
static int	set_home_as_path(t_env_var *env_list, char **new_path,
		char **envp)
{
	t_env_var	*home_node;
	int			i;

	if (env_list)
	{
		home_node = find_env_var(env_list, "HOME");
		if (!home_node)
			return (0);
		*new_path = home_node->value;
	}
	else
	{
		i = 0;
		while (!(*new_path) && envp[i])
			*new_path = ft_strnstr(envp[i++], "HOME=", 5);
		if (!(*new_path))
			return (0);
		(*new_path) += 5;
	}
	return (1);
}

/*new_path is route called by cd. If there's not new_path, cd use HOME
 * enviorment variable to set it as new path. In bash, if !HOME, cd alone
 * doesn't works. We did it, too*/
int	execute_cd(char **cmd, char *new_path, t_env_var *env_list, char **envp)
{
	t_env_var	*current_pwd;
	t_env_var	*old_pwd;
	char		*new_oldpwd;

	if (cmd[1] && cmd[2])
		return (error_in_cd(CD_ARGS, 2, NULL));
	if (cmd[1] && !is_directory(new_path))
	{
		ft_dprintf(2, "minishell: cd: %s: Not a directory\n", cmd[1]);
		return (1);
	}
	current_pwd = find_env_var(env_list, "PWD");
	old_pwd = find_env_var(env_list, "OLDPWD");
	new_oldpwd = NULL;
	if (!call_to_getcwd(&new_oldpwd))
		return (error_in_cd(CD_GETCWD, 1, &new_oldpwd));
	if (!new_path && !set_home_as_path(env_list, &new_path, envp))
		return (error_in_cd(CD_NO_HOME, 2, &new_oldpwd));
	if (chdir(new_path) < 0)
		return (error_in_cd(CD_NO_DIR, 2, &new_oldpwd));
	if (!env_list)
		return (error_in_cd(NULL, 0, &new_oldpwd));
	if (!change_pwd(old_pwd, &new_oldpwd) || !change_pwd(current_pwd, NULL))
		return (error_in_cd(CD_GETCWD, 1, NULL));
	return (0);
}
