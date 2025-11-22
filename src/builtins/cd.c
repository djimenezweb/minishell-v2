/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 11:06:43 by danielji          #+#    #+#             */
/*   Updated: 2025/11/22 22:02:50 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_pwd(t_env_var *node, char *new_path)
{
	if (node->value)
		free(node->value);
	node->value = ft_strdup(new_path);
	if (!node->value)
		return (0);//malloc error
	return (1);
}

/*Check env_list looking for HOME. 
 * HOME must be set, if not, cd with args doesn't work*/
static char	*set_home_as_path(t_shell *data)
{
	t_env_var	*home_node;
	
	home_node = find_env_var(data->env_list, "OLDPWD");
	if (!home_node)
	{
		perror("minishell: cd: HOME not set");
		exit(EXIT_FAILURE);//In case of cd working as a child process
	}
	return (home_node->value);
}

void	execute_cd(char *new_path, t_shell *data)
{
	t_env_var	*current_pwd;
	t_env_var	*old_pwd;
	char	*current_pwd;
	
	current_pwd = find_env_var(data->env_list, "PWD");
	old_pwd = find_env_var(data->env_list, "OLDPWD");
	if (!change_pwd(oldpwd, current_pwd->value))
		//return or exit a malloc error
	if (!new_path)//new_path must be cmd[1]
		new_path = set_home_as_path(data);
	if (chdir(new_path) < 0)
	{
		perror("No such file or directory");//May change this message?
		exit(EXIT_FAILURE);
	}
	if (!change_pwd(current_pwd, new_path))
		//return or exit a malloc error
	//return or exit success
	exit(EXIT_SUCCESS);
	//
	//
//	ft_putendl_fd("cd test", STDOUT_FILENO);//test
//	return (0);//test
//	"DON'T FORGET" TO REMOVE TEST BELOW
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
