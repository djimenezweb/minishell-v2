/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer-utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:24:38 by danielji          #+#    #+#             */
/*   Updated: 2025/10/02 10:29:20 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Add the node `new` after the node `prev` */
void	ft_lexlist_insert(t_lextoken *prev, t_lextoken *new)
{
	t_lextoken	*temp;

	temp = prev->next;
	prev->next = new;
	new->next = temp;
	new->next->prev = new;
}

/* Add the node `new` at the beginning of the list `lst`
if it's empty or at the end of the list */
void	ft_lexlist_add(t_lextoken **lst, t_lextoken *new)
{
	t_lextoken	*last;

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

/* Take a node as parameter and free its content.
Free the node but do NOT free the next node. */
void	ft_lexnode_free(t_lextoken *node)
{
	if (node->value)
	{
		free(node->value);
		node->value = NULL;
	}
	free(node);
	node = NULL;
}

/* Delete and free the given node and all its successors.
Finally, set the pointer to the list to `NULL`.*/
void	ft_lexlist_clear(t_lextoken **lst)
{
	t_lextoken	*current;
	t_lextoken	*next;

	if (!lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		ft_lexnode_free(current);
		current = next;
	}
	*lst = NULL;
}
