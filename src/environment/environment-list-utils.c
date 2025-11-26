/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment-list-utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:22:22 by danielji          #+#    #+#             */
/*   Updated: 2025/11/26 18:33:07 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Allocate memory for a new `t_env_var` node based
on the passed parameters `name` and `value`. */
t_env_var	*ft_new_env_name_value(char *name, char *value)
{
	char		*str;
	t_env_var	*node;

	str = ft_strjoin3(name, "=", value);
	if (!str)
		return (NULL);
	node = ft_new_env(str);
	free(str);
	return (node);
}

/* Allocate memory for a new `t_env_var` node and return it.
Initalize `name` and `value` variables based on the passed parameter `str`.
The string `str` must be formatted as `NAME=VALUE`. */
t_env_var	*ft_new_env(char *str)
{
	t_env_var	*node;

	if (!str)
		return (NULL);
	node = (t_env_var *)malloc(sizeof(t_env_var));
	if (!node)
		return (NULL);
	set_name_value(node, str);
	if (!node->name || !node->value)
		return (NULL);
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

/* Add the node `new` at the end of the list `lst` */
void	ft_env_addback(t_env_var **lst, t_env_var *new)
{
	t_env_var	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new;
		new->prev = last;
	}
}

/* Return size of a list of env variables */
int	ft_envlist_size(t_env_var *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

int	change_env_value(t_env_var *node, char *new_value)
{
	if (node->value)
		free(node->value);
	node->value = ft_strdup(new_value);
	if (!node->value)
		return (0);
	return (1);
}
