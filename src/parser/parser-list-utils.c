/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser-list-utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:03:00 by danielji          #+#    #+#             */
/*   Updated: 2025/12/05 09:34:26 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	node->input = STDIN_FILENO;
	node->output = STDOUT_FILENO;
	node->pid = -1;
	node->status = -1;
	node->is_forkable = 1;
	node->is_heredoc = 0;
	node->delimiters = NULL;
	node->shell = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
