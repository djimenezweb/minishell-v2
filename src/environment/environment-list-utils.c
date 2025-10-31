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

#include "minishell.h"

/* Allocate memory for a new `t_env_var` node and return it.
Initalize `name` and `value` variables based on the passed parameter `str`.
The variables `next` and `prev` are initialized to `NULL`. */
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

/* Free the content of a node and the node itself */
void	ft_envnode_free(t_env_var *node)
{
	if (node->value)
	{
		free(node->value);
		node->value = NULL;
	}
	if (node->name)
	{
		free(node->name);
		node->value = NULL;
	}
	node->next = NULL;
	node->prev = NULL;
	free(node);
	node = NULL;
}

/* Delete and free the given node and all its successors.
Set the list pointer to `NULL`.*/
void	ft_envlist_clear(t_env_var **lst)
{
	t_env_var	*current;
	t_env_var	*next;

	if (!lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		ft_envnode_free(current);
		current = next;
	}
	*lst = NULL;
}
