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
- `|` is the first node.
- `|` is the last node.
- There is not a `TOK_WORD` before or after a `|` */
int	pipe_validation(t_lextoken *node)
{
	if (!node->next || !node->prev)
	{
		printf("Syntax error near `%c`\n", PIPE);
		return (0);
	}
	if (node->next->type != TOK_WORD || node->prev->type != TOK_WORD)
	{
		printf("Syntax error near `%c`\n", PIPE);
		return (0);
	}
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
		node = node->next;
	}
	return (1);
}
