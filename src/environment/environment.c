/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:23:02 by danielji          #+#    #+#             */
/*   Updated: 2025/10/13 11:23:02 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/* Iterates through the list and returns a `t_env_var` node whose name is
the same as the passed parameter `name` */
t_env_var	*ft_find_env_var(t_env_var *list, char *name)
{
	t_env_var	*current;

	current = list;
	while (current)
	{
		if (ft_strnstr(current->name, name, ft_strlen(name)) != NULL)
			return (current);
		current = current->next;
	}
	return (NULL);
}

/* Initializes `name` and `value` from the passed string `str`.
The string `str`must be formatted as `NAME=VALUE` */
void	set_name_value(t_env_var *node, char *str)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	while (str[end] && str[end] != '=')
		end++;
	node->name = ft_substr(str, 0, end);
	start = end++;
	end = start;
	start++;
	while (str[end])
		end++;
	node->value = ft_substr(str, start, end);
}

/* Sets default variable `PATH` if it's missing */
void	set_default_env_vars(t_env_var **list)
{
	if (ft_find_env_var(*list, "PATH") == NULL)
	{
		ft_env_addback(list, ft_new_node(DEFAULT_PATH));
	}
}

/* Returns a list of environment variables based on passed `envp` */
t_env_var	*set_env_vars(char *envp[])
{
	int			i;
	t_env_var	*list;

	i = 0;
	list = NULL;
	while (envp[i])
	{
		ft_env_addback(&list, ft_new_node(envp[i]));
		i++;
	}
	return (list);
}
