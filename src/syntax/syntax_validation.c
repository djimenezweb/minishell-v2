/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:51:03 by danielji          #+#    #+#             */
/*   Updated: 2025/11/04 13:57:42 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Return `1` if node passes pipe syntax validation.
A syntax error occurs when: 
- `|` is the first or the last node.
- There are two consecutive `|` */
int	pipe_validation(t_lextoken *node)
{
	if (!node->next || !node->prev)
	{
		printf("Syntax error near `%c`\n", PIPE);
		return (0);
	}
	if (node->next->type == TOK_PIPE || node->prev->type == TOK_PIPE)
	{
		printf("Syntax error near `%c`\n", PIPE);
		return (0);
	}
	return (1);
}

/* Return `1` if node passes redirection syntax validation.
A syntax error occurs when: 
- There are two consecutive `<` or `>` */
// TODO ¿Cuáles son los requisitos?
int	redir_validation(t_lextoken *node)
{
	(void)node;
	return (1);
}

/* Return `1` if list passes syntax validation */
int	syntax_validation(t_lextoken *node)
{
	while (node)
	{
		if (node->type == TOK_PIPE)
			return (pipe_validation(node));
		if (node->type == TOK_REDIR_IN)
			return (redir_validation(node));
		node = node->next;
	}
	return (1);
}
