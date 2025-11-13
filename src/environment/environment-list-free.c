/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment-list-free.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:22:22 by danielji          #+#    #+#             */
/*   Updated: 2025/10/14 10:22:22 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		node->name = NULL;
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
