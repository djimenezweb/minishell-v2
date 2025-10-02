/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:41:33 by danielji          #+#    #+#             */
/*   Updated: 2025/10/02 10:32:40 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Allocates memory for a new node, initializes `type` and returns node.
Advances `*i` 1 character if it's passed as an argument. */
static t_lextoken	*ft_new_token(t_lex_type type, int *i)
{
	t_lextoken	*node;

	if (!type)
		return (NULL);
	node = (t_lextoken *)malloc(sizeof(t_lextoken));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = NULL;
	node->next = NULL;
	if (i != NULL)
		(*i)++;
	return (node);
}

/* Returns new `TOK_HEREDOC` (`<<`), `TOK_REDIR_IN` (`<`),
`TOK_APPEND` (`>>`) or `TOK_REDIR_OUT` (`>`) token.
Advances `*i` 1 or 2 characters accordingly. */
static t_lextoken	*ft_new_redir_token(t_lex_type type, char next_c, int *i)
{
	t_lextoken	*node;

	node = NULL;
	if (type == LESS)
	{
		if (next_c == LESS)
		{
			node = ft_new_token(TOK_HEREDOC, i);
			(*i)++;
		}
		else
			node = ft_new_token(TOK_REDIR_IN, i);
	}
	else if (type == GREATER)
	{
		if (next_c == GREATER)
		{
			node = ft_new_token(TOK_APPEND, i);
			(*i)++;
		}
		else
			node = ft_new_token(TOK_REDIR_OUT, i);
	}
	return (node);
}

/* Initializes `value` to substring and returns new `TOK_WORD` token*/
static t_lextoken	*ft_new_word_token(char *str, int start, int len)
{
	t_lextoken	*node;

	node = (t_lextoken *)malloc(sizeof(t_lextoken));
	if (!node)
		return (NULL);
	node->type = TOK_WORD;
	node->value = ft_substr(str, start, len);
	node->next = NULL;
	return (node);
}

/* Parses a possibly quoted word from a string starting at position `*i`,
creates a new word token from it, advances `*i` past the parsed word,
and returns the token. */
static t_lextoken	*ft_parse_word(char *str, int *i)
{
	char		quote;
	int			start;
	t_lextoken	*node;

	if (str[*i] == DOUBLE_QUOTE || str[*i] == SINGLE_QUOTE)
	{
		quote = str[*i];
		(*i)++;
		start = *i;
		while (str[*i] && str[*i] != quote)
			(*i)++;
		node = ft_new_word_token(str, start, *i - start);
		if (str[*i] == quote)
			(*i)++;
	}
	else
	{
		start = *i;
		while (str[*i] && !ft_isspace(str[*i]) && !ft_ismetachar(str[*i]))
			(*i)++;
		node = ft_new_word_token(str, start, *i - start);
	}
	return (node);
}

/* Returns a `t_token` list containing tokens that represent the
passed string. List ends with `TOK_EOF` token */
t_lextoken	*lexer(char *str)
{
	int			i;
	t_lextoken	*node;
	t_lextoken	*list;

	i = 0;
	list = NULL;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i] == PIPE)
			node = ft_new_token(TOK_PIPE, &i);
		else if (str[i] == LESS)
			node = ft_new_redir_token(LESS, str[i + 1], &i);
		else if (str[i] == GREATER)
			node = ft_new_redir_token(GREATER, str[i + 1], &i);
		else
			node = ft_parse_word(str, &i);
		ft_lexlist_add(&list, node);
	}
	ft_lexlist_add(&list, ft_new_token(TOK_EOF, NULL));
	return (list);
}
