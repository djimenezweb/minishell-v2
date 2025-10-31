/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:51:03 by danielji          #+#    #+#             */
/*   Updated: 2025/10/21 11:14:27 by danielji         ###   ########.fr       */
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
int	redir_validation(t_lextoken *node)
{
	// ¿Cuáles son los requisitos?
	return (1);
}

/* Return `1` if list passes syntax validation */
/*
		if (node->type == TOK_REDIR_IN)
			// TO DO
		if (node->type == TOK_REDIR_OUT)
			// TO DO
		if (node->type == TOK_HEREDOC)
			// TO DO
		if (node->type == TOK_APPEND)
			// TO DO

*/
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
