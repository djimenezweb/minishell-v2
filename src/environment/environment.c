/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:23:02 by danielji          #+#    #+#             */
/*   Updated: 2025/11/04 13:54:06 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Iterate through the list and return a `t_env_var` node whose name is
the same as the passed parameter `name` followed by `\0` */
t_env_var	*find_env_var(t_env_var *list, char *name)
{
	size_t	len;

	len = ft_strlen(name);
	while (list)
	{
		if (ft_strncmp(list->name, name, len + 1) == 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}

/* Return the value of the passed parameter `name`.
Works as a substitute for `getenv`. */
char	*get_env_value(t_env_var *list, char *name)
{
	t_env_var	*node;

	node = find_env_var(list, name);
	if (!node)
		return (NULL);
	return (node->value);
}

/* Initialize `name` and `value` from the passed string `str`.
The string `str` must be formatted as `NAME=VALUE` */
void	set_name_value(t_env_var *node, char *str)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	while (str[end] && str[end] != EQUALS)
		end++;
	node->name = ft_substr(str, 0, end);
	start = end++;
	end = start;
	start++;
	while (str[end])
		end++;
	node->value = ft_substr(str, start, end);
}

/* Set default variables `PATH` and `PWD` if they are missing.
TODO: Add other variables */
int	set_default_env_vars(t_env_var **list)
{
	t_env_var	*node;

	node = ft_new_env_name_value("?", "0");
	if (!node)
		return (-1);
	ft_env_addback(list, node);
	if (find_env_var(*list, "PATH") == NULL)
	{
		node = ft_new_env(DEFAULT_PATH);
		if (!node)
			return (-1);
		ft_env_addback(list, node);
	}
	if (find_env_var(*list, "PWD") == NULL)
	{
		node = ft_new_env_name_value("PWD", getcwd(NULL, 0));
		if (!node)
			return (-1);
		ft_env_addback(list, node);
	}
	return (0);
}

/* Return a list of environment variables based on passed `envp`.
If `envp` is missing, set default variables.
Return `NULL` if memory allocation fails.*/
t_env_var	*set_env_vars(char *envp[])
{
	t_env_var	*list;
	t_env_var	*node;

	list = NULL;
	while (envp && *envp)
	{
		node = ft_new_env(*envp);
		if (!node)
			return (ft_envlist_clear(&list), NULL);
		ft_env_addback(&list, node);
		envp++;
	}
	if (set_default_env_vars(&list) < 0)
		return (ft_envlist_clear(&list), NULL);
	return (list);
}
