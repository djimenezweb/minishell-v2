/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:47:48 by danielji          #+#    #+#             */
/*   Updated: 2025/11/25 20:48:35 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_new_env_vars(char *input, t_env_var *env_list, int *flag)
{
	t_env_var	*new_node;

	new_node = NULL;
	new_node = ft_new_env(input);
	if (!new_node)
		*flag = 1;
	ft_env_addback(&env_list, new_node);
	//if (!ft_strchr(input, '='))
		//remove_equal();TODO
}

int	ft_export(char **cmd, t_env_var *env_list, char **envp)
{
	int	error_flag;

	error_flag = 0;
	if (!cmd[1])
		return (ft_env(cmd, envp));//debug. Here we should sort env vars
	else
	{
		cmd += 1;
		while (*cmd && !error_flag)
		{
			create_new_env_vars(*cmd, env_list, &error_flag);
			//Check if env_list is modified
			++cmd;
		}
		if  (error_flag)
			ft_putendl_fd("env: failed creating new env_var", 2);
	}
	return (error_flag);
}
