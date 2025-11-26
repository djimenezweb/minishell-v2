/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 11:06:43 by danielji          #+#    #+#             */
/*   Updated: 2025/11/26 18:35:07 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_pwd(t_env_var *node)
{
	char	*new_path;

	new_path = getcwd(NULL, 0);
	if (!new_path)
	{
		perror("getcwd failed");
		return (0);
	}
	if (!change_env_value(node, new_path))
	{
		free(new_path);
		return (0);
	}
	free(new_path);
	return (1);
}

/*Check env_list looking for HOME. 
 * HOME must be set, if not, cd with args doesn't work*/
static int	set_home_as_path(t_env_var *env_list, char **new_path)
{
	t_env_var	*home_node;

	home_node = find_env_var(env_list, "HOME");
	if (!home_node)
		return (0);
	*new_path = home_node->value;
	return (1);
}

/*new_path is route called by cd. If there's not new_path, cd use HOME
 * enviorment variable to set it as new path. In bash, if !HOME, cd alone
 * doesn't works. We did it, too*/
int	execute_cd(char **cmd, char *new_path, t_env_var *env_list)
{
	t_env_var	*current_pwd;
	t_env_var	*old_pwd;

	if (cmd[1] && cmd[2])
	{
		perror("minishell: cd: too many arguments");
		return (2);
	}
	current_pwd = find_env_var(env_list, "PWD");
	old_pwd = find_env_var(env_list, "OLDPWD");
	if (!change_pwd(old_pwd))
		return (12);
	if (!new_path && !set_home_as_path(env_list, &new_path))
	{
		perror("minishell: cd: HOME not set");
		return (2);
	}
	if (chdir(new_path) < 0)
	{
		perror("No such file or directory");
		return (2);
	}
	if (!change_pwd(current_pwd))
		return (12);
	return (0);
}
