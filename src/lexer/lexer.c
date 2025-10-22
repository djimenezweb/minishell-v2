/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:41:33 by danielji          #+#    #+#             */
/*   Updated: 2025/10/09 18:35:32 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Allocate memory for a new node, initialize `type` and return node. */
t_lextoken	*ft_new_lex_token(t_lex_type type)
{
	t_lextoken	*node;

	node = NULL;
	node = (t_lextoken *)malloc(sizeof(t_lextoken));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

/* Return new `TOK_PIPE` (`|`), `TOK_HEREDOC` (`<<`), `TOK_REDIR_IN` (`<`),
`TOK_APPEND` (`>>`) or `TOK_REDIR_OUT` (`>`) token.
Advance `*i` 1 or 2 characters accordingly. */
t_lextoken	*ft_new_operator_token(char c, char next_c, int *i)
{
	t_lextoken	*node;

	node = NULL;
	if (c == PIPE)
		node = ft_new_lex_token(TOK_PIPE);
	if (c == LESS)
	{
		if (next_c && next_c == LESS)
			node = ft_new_lex_token(TOK_HEREDOC);
		else
			node = ft_new_lex_token(TOK_REDIR_IN);
	}
	else if (c == GREATER)
	{
		if (next_c && next_c == GREATER)
			node = ft_new_lex_token(TOK_APPEND);
		else
			node = ft_new_lex_token(TOK_REDIR_OUT);
	}
	if (node->type == TOK_HEREDOC || node->type == TOK_APPEND)
		(*i)++;
	(*i)++;
	return (node);
}

/* Return new `TOK_WORD` with `value` containing a substring. */
t_lextoken	*ft_new_word_token(char *str, int *i)
{
	t_lextoken	*node;

	node = NULL;
	node = ft_new_lex_token(TOK_WORD);
	if (!node)
		return (NULL);
	node->value = parse_word(str, i);
	if (!node->value)
		return (NULL);
	return (node);
}

/* Skip leading spaces.
Skip trailing spaces by placing a `\0` before the spaces. */
void	skip_spaces(char *str, int *i)
{
	size_t	len;

	len = ft_strlen(str);
	while (ft_isspace(str[*i]))
		(*i)++;
	while (len > 0 && ft_isspace(str[len - 1]))
		len--;
	str[len] = '\0';
}

/* Return a `t_token` list containing tokens that represent the
passed string. List ends with `TOK_EOF` token. */
t_lextoken	*lexer(char *str)
{
	int			i;
	t_lextoken	*node;
	t_lextoken	*list;

	i = 0;
	list = NULL;
	node = NULL;
	while (str[i])
	{
		skip_spaces(str, &i);
		if (str[i] == PIPE | str[i] == LESS | str[i] == GREATER)
			node = ft_new_operator_token(str[i], str[i + 1], &i);
		else
			node = ft_new_word_token(str, &i);
		if (!node)
			return (ft_lexlist_clear(&list), NULL);
		ft_lexlist_add(&list, node);
	}
	ft_lexlist_add(&list, ft_new_lex_token(TOK_EOF));
	return (list);
}
