/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser-list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:24:38 by danielji          #+#    #+#             */
/*   Updated: 2025/09/26 11:48:46 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

/* Allocates memory and returns a new node.
The `content` variable is initialized with the given parameter `content`.
The variable `next` is initialized to `NULL`. */
t_token	*ft_add_new_token(t_token_type type, char *string, int start, size_t len)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->type = type;
	if (type == TOK_WORD)
		node->value = ft_substr(string, start, len);
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

/* Counts the number of nodes in the list `lst`. */
int	ft_lstsize(t_token *lst)
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
t_token	*ft_lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/* Adds the node `new` at the end of the list */
void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

/* Adds the node `new` at the beginning of the list `lst`.*/
/* void	ft_lstadd_front(t_token **lst, t_token *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
} */

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
void	ft_clear_list(t_token **lst)
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

/* Iterates through the list `lst` and applies the function `f`
to the content of each node.*/
/* void	ft_lstiter(t_token *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
} */

/* Iterates through the list `lst`, applies the function `f` to each node's
content, and creates a new list resulting of the successive applications of
the function `f`.
The `del` function is used to delete the content of a node if needed.*/
/* t_token	*ft_lstmap(t_token *lst, void *(*f)(void *), void (*del)(void *))
{
	t_token	*new_list;
	t_token	*new_node;
	void	*new_content;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		new_node = ft_lstnew(new_content);
		if (!new_node)
		{
			del(new_content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
} */
