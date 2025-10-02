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

/* Returns `1` if a character is `|`, `<`, or `>` */
int	ft_ismetachar(char c)
{
	if (c == PIPE || c == LESS || c == GREATER)
		return (1);
	return (0);
}

/* Adds the node `new` at the beginning of the list `lst`
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
	}
}

/* Takes a node as parameter and frees its content.
Frees the node itself but does NOT free the next node. */
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

/* Deletes and frees the given node and all its successors.
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
