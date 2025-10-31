/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser-list-utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:03:00 by danielji          #+#    #+#             */
/*   Updated: 2025/10/23 10:03:00 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

/* Add the node `new` after the node `prev` */
void	ft_cmdlist_insert(t_cmd *prev, t_cmd *new)
{
	t_cmd	*temp;

	temp = prev->next;
	prev->next = new;
	new->next = temp;
	new->next->prev = new;
}

/* Add the node `new` at the beginning of the list `lst`
if it's empty or at the end of the list */
void	ft_cmdlist_add(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

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
void	ft_cmdnode_free(t_cmd *node)
{
	if (node->cmd)
	{
		// to do: free array of strings
		//free(node->cmd);
		node->cmd = NULL;
	}
	if (node->path)
	{
		free(node->path);
		node->path = NULL;
	}
	free(node);
	node = NULL;
}

/* Delete and free the given node and all its successors.
Finally, set the pointer to the list to `NULL`.*/
void	ft_cmdlist_clear(t_cmd **lst)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		ft_cmdnode_free(current);
		current = next;
	}
	*lst = NULL;
}

/* Allocate memory for a new node and return it. */
t_cmd	*ft_new_cmdnode(void)
{
	t_cmd	*node;

	node = NULL;
	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->cmd = NULL;
	node->path = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
