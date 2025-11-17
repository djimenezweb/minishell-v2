/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser-list-utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:03:00 by danielji          #+#    #+#             */
/*   Updated: 2025/11/09 23:17:13 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Take a node as parameter and free its content.
Free the node but do NOT free the next node. */
void	ft_cmdnode_free(t_cmd *node)
{
	if (node->cmd)
	{
		free_strings_array(node->cmd);
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
