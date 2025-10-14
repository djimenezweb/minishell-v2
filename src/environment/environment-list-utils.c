/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment-list-utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:22:22 by danielji          #+#    #+#             */
/*   Updated: 2025/10/14 10:22:22 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/* Allocates memory for a new `t_env_var` node and returns it.
Initalizes `name` and `value` variables based on the passed parameter `str`.
The variable `next` is initialized to `NULL`. */
t_env_var	*ft_new_node(char *str)
{
	t_env_var	*node;

	if (!str)
		return (NULL);
	node = (t_env_var *)malloc(sizeof(t_env_var));
	if (!node)
		return (NULL);
	set_name_value(node, str);
	node->next = NULL;
	return (node);
}

/* Adds the node `new` at the end of the list `lst` */
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
	}
}
