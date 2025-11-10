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
	printf("cmd node to free is %p, cmd is %p, arg 0 == %s\n", node, node->cmd, node->cmd[0]);//debug
	if (node->cmd)
	{
		printf("Free strings array after this line\n");//debug
		free_strings_array(node->cmd);//Added by Enrique, in libft
		printf("Free strings array done\n");//debug
		//free(node->cmd);//Not needed at hte end, is it?
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

	printf("cmd list to free is %p, cmd is %p, arg 0 == %s\n", *lst, (*lst)->cmd,(*lst)->cmd[0]);//debug
	if (!lst)
		return ;
	current = *lst;
	while (current)
	{
		printf("current to free is %p\n", current);//debug
		printf("cmd current to free is %p, cmd is %p, arg 0 == %s\n", current, current->cmd, current->cmd[0]);//debug
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
