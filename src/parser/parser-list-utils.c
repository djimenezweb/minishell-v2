/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser-list-utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:03:00 by danielji          #+#    #+#             */
/*   Updated: 2025/11/20 16:54:07 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

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
	node->is_builtin = NOT_BUILTIN;
	node->is_heredoc = 0;
	node->delimiters = NULL;
	node->env_list = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

/* Return size of a command list */
int	ft_cmdlist_size(t_cmd *lst)
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
