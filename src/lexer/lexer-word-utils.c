/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer-word-utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 11:12:08 by danielji          #+#    #+#             */
/*   Updated: 2025/10/09 18:49:23 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Return `1` if character `c` is included in string `set` */
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

/* Initialize `value` to substring and return new `TOK_WORD` token*/
t_lextoken	*ft_new_word_token(char *str, int start, int len)
{
	t_lextoken	*node;

	node = (t_lextoken *)malloc(sizeof(t_lextoken));
	if (!node)
		return (NULL);
	node->type = TOK_WORD;
	node->value = ft_substr(str, start, len);
	if (!node->value)
		return (NULL);
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

/* Parse a quoted word from a string starting at position `*i`,
create a new word token from it, advance `*i` past the parsed word,
and return the token.
A quote indicates the end of a word only if it's adjacent to ` ` (space),
`<`, `|`, or `>`.*/
t_lextoken	*ft_parse_quoted_word(char *str, int *i)
{
	char		c;
	char		quote;
	int			start;
	t_lextoken	*node;

	quote = str[*i];
	start = *i;
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == quote)
		{
			c = str[*i + 1];
			if (!(c && ft_isspace(c) && is_in_set(c, "<|>")))
				break ;
		}
		(*i)++;
	}
	node = ft_new_word_token(str, start, *i - start + 1);
	if (str[*i] == quote)
		(*i)++;
	return (node);
}

/* Parse a word from a string starting at position `*i`, create a new word
token from it, advance `*i` past the parsed word, and return the token.
Return an `EOF` token if the word is made up only of space.*/
t_lextoken	*ft_parse_word(char *str, int *i)
{
	int			start;
	t_lextoken	*node;

	start = *i;
	while (str[*i] && !ft_isspace(str[*i]) && !is_in_set(str[*i], "<|>"))
		(*i)++;
	if (start == *i)
		node = ft_new_operator_token(TOK_EOF, NULL);
	else
		node = ft_new_word_token(str, start, *i - start);
	return (node);
}
