/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:47:48 by danielji          #+#    #+#             */
/*   Updated: 2025/11/30 19:24:18 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_not_valid_identifier(char *input)
{
	ft_dprintf(2, "minishell: export: `%s': not a valid identifier\n",
		input);
}

static int	check_name_chars(char *name, int *error_flag, char *input)
{
	int	i;

	i = 0;
	if (!ft_isalpha(name[i]) && name[i] != '_')
	{
		if (*error_flag == 0)
			*error_flag = 1;
		print_not_valid_identifier(input);
		return (0);
	}
	while (name[++i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			if (*error_flag == 0)
				*error_flag = 1;
			print_not_valid_identifier(input);
			return (0);
		}
	}
	return (1);
}

/*Export could have many values. If some of it are wrong, returns 1,
 * but still creates any env_var asked if it is possible*/
static void	create_new_env_vars(char *input, t_env_var *env_list, int *flag)
{
	t_env_var	*new_node;
	t_env_var	*already_exist_env_var;

	new_node = NULL;
	new_node = ft_new_env(input);
	if (!new_node || !check_name_chars(new_node->name, flag, input))
	{
		if (!new_node)
			*flag = 2;
		else
			ft_envnode_free(new_node);
		return ;
	}
	already_exist_env_var = find_env_var(env_list, new_node->name);
	if (!already_exist_env_var)
		ft_env_addback(&env_list, new_node);
	else if (ft_strchr(input, '='))
	{
		change_env_value(already_exist_env_var, new_node->value);
		ft_envnode_free(new_node);
	}
	else
		ft_envnode_free(new_node);
}

int	ft_export(char **cmd, t_env_var *env_list, char **envp)
{
	int	error_flag;

	error_flag = 0;
	if (!cmd[1])
		return (ft_env(cmd, envp, 1));//debug. Here we should sort env vars
	else if (env_list)
	{
		cmd += 1;
		while (*cmd && error_flag != 2)
		{
			create_new_env_vars(*cmd, env_list, &error_flag);
			++cmd;
		}
		if (error_flag == 2)
			ft_putendl_fd("env: failed creating new env_var", 2);
	}
	return (error_flag);
}
