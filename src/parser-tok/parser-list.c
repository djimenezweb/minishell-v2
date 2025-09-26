/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser-list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:24:38 by danielji          #+#    #+#             */
/*   Updated: 2025/09/26 13:05:30 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

/* Counts the number of nodes in the list `lst`. */
int	ft_toklstsize(t_token *lst)
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

/* Returns the last node of the list. */
t_token	*ft_toklstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/* Adds the node `new` at the end of the list */
void	ft_toklstadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		last = ft_toklstlast(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

/* Takes a node as parameter and frees its content.
Free the node itself but does NOT free the next node. */
void	ft_free_node(t_token *node)
{
	if (node->value)
	{
		free(node->value);
		node->value = NULL;
	}
	free(node);
}

/* Deletes and frees the given node and all its successors.
Finally, set the pointer to the list to `NULL`.*/
void	ft_clear_toklist(t_token **lst)
{
	t_token	*current;
	t_token	*next;

	if (!lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		ft_free_node(current);
		current = next;
	}
	*lst = NULL;
}
