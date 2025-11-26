/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:47:48 by danielji          #+#    #+#             */
/*   Updated: 2025/11/26 21:01:05 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_new_env_vars(char *input, t_env_var *env_list, int *flag)
{
	t_env_var	*new_node;
	t_env_var	*already_exist_env_var;

	new_node = NULL;
	new_node = ft_new_env(input);
	if (!new_node)
	{
		*flag = 1;
		return ;
	}
	already_exist_env_var = find_env_var(env_list, new_node->name);
	if (!already_exist_env_var)
		ft_env_addback(&env_list, new_node);
	else
	{
		change_env_value(already_exist_env_var, new_node->value);
		ft_envnode_free(new_node);
	}
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
			++cmd;
		}
		if (error_flag)
			ft_putendl_fd("env: failed creating new env_var", 2);
	}
	return (error_flag);
}
