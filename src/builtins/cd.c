/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 11:06:43 by danielji          #+#    #+#             */
/*   Updated: 2025/11/22 20:50:14 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_oldpwd(t_env_var *node, char *new_path)
{
	if (node->value)
		free(node->value);
	node->value = ft_strdup(new_path);
	if (!node->value)
		return (0);//malloc error
	return (1);
}

/*If HOME is not set, cd works only if a path is specified*/
char	*set_home_as_path(t_shell *data)
{
	t_env_var	*home_node;
	
	home_node = find_env_var(data->env_list, "OLDPWD");
	if (home_node)
		return (home_node->value);
	return (NULL);
}

int	execute_cd(char *current_path, char *new_path, t_shell *data)
{
	t_env_var	*oldpwd;
	
	if (!new_path)//new_path must be cmd[1]
	{
		new_path = set_home_as_path(data);
	}
	else
	{
		
		if (chdir(new_path) < 0)
		{
			perror("No such file or directory");//May change this message?
			exit(EXIT_FAILURE);
		}
		ft_putendl_fd("cd test", STDOUT_FILENO);
		return (0);
	}
	oldpwd = find_env_var(data->env_list, "OLDPWD");
	if (!change_oldpwd(oldpwd, new_path))
		//return or exit?
	//OLDPWD=current_path
}

/*
int main(int argc, char **argv)
{
	char	*current_dir;

	current_dir = NULL;
	current_dir = getcwd(current_dir, 0); 
	printf("current dir is %s\n", current_dir);
	if (argc > 1)
	{
		chdir(argv[1]);
		current_dir = getcwd(NULL, 0); 
		printf("current dir is %s\n", current_dir);
	}
	return (0);
}*/
