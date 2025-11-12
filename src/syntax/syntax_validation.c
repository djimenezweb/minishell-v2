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

/* Return `1` if node is the last one */
int	is_tok_last(t_lextoken *node)
{
	if (node->next == NULL)
		return (1);
	if (node->next->type == TOK_EOF)
		return (1);
	return (0);
}

/* Return `1` if node is the first one */
int	is_tok_first(t_lextoken *node)
{
	if (node->prev == NULL)
		return (1);
	return (0);
}

/* Return `1` if node is adjacent to a node of the same type */
int	is_tok_consecutive(t_lextoken *node)
{
	if (node->next->type && (node->type == node->next->type))
		return (1);
	if (node->prev->type && (node->type == node->prev->type))
		return (1);
	return (0);
}

/* Return `1` if list passes syntax validation.
On error print error message and return `0`. */
int	syntax_validation(t_lextoken *node)
{
	while (node)
	{
		if (node->type == TOK_PIPE)
		{
			if (is_tok_first(node) || is_tok_last(node) || is_tok_consecutive(node))
				return (ft_putendl_fd("Syntax error near `|`", STDERR_FILENO), 0);
		}
		if (node->type == TOK_REDIR_OUT)
		{
			if (is_tok_last(node) || is_tok_consecutive(node))
				return (ft_putendl_fd("Syntax error near `>`", STDERR_FILENO), 0);
		}
		if (node->type == TOK_APPEND)
		{
			if (is_tok_last(node) || is_tok_consecutive(node))
				return (ft_putendl_fd("Syntax error near `>>`", STDERR_FILENO), 0);
		}
		if (node->type == TOK_REDIR_IN)
		{
			if (is_tok_last(node) || is_tok_consecutive(node))
				return (ft_putendl_fd("Syntax error near `<`", STDERR_FILENO), 0);
		}
		if (node->type == TOK_HEREDOC)
		{
			if (is_tok_last(node) || is_tok_consecutive(node))
				return (ft_putendl_fd("Syntax error near `<<`", STDERR_FILENO), 0);
		}
		node = node->next;
	}
	return (1);
}
