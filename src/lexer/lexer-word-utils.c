/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer-word-utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 11:12:08 by danielji          #+#    #+#             */
/*   Updated: 2025/10/06 11:13:39 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns `1` if a character is `|`, `<`, or `>` */
/* int	ft_ismetachar(char c)
{
	if (c == PIPE || c == LESS || c == GREATER)
		return (1);
	return (0);
} */

/* Retuns `1` if character `c` is included in string `set` */
int	is_in_set(char c, char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
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

/* Parses a quoted word from a string starting at position `*i`,
creates a new word token from it, advances `*i` past the parsed word,
and returns the token. */
t_lextoken	*ft_parse_quoted_word(char *str, int *i)
{
	char		quote;
	int			start;
	t_lextoken	*node;

	quote = str[*i];
	start = *i;
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == quote && (is_in_set(str[*i + 1], " <|>")))
			break ;
		(*i)++;
	}
	node = ft_new_word_token(str, start, *i - start + 1);
	if (str[*i] == quote)
		(*i)++;
	return (node);
}

/* Parses a word from a string starting at position `*i`,
creates a new word token from it, advances `*i` past the parsed word,
and returns the token. */
t_lextoken	*ft_parse_word(char *str, int *i)
{
	int			start;
	t_lextoken	*node;

	start = *i;
	while (str[*i] && !ft_isspace(str[*i]) && !is_in_set(str[*i], "<|>"))
		(*i)++;
	node = ft_new_word_token(str, start, *i - start);
	return (node);
}
