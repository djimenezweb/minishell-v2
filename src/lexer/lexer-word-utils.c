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

/* Iterate over a string until a delimiter is reached (whitespace, `<`, `>`,
or `|`). Delimiters are not taken into account if they are between single
or double quotes. */
char	*parse_word(char *str, int *i)
{
	char	quote;
	int		start;

	quote = 0;
	start = *i;
	while (str[*i])
	{
		if (!quote && (str[*i] == SINGLE_QUOTE || str[*i] == DOUBLE_QUOTE))
		{
			quote = str[*i];
		}
		else if (quote && (str[*i] == quote))
		{
			quote = 0;
		}
		else if (!quote && (is_in_set(str[*i], "<|>") || ft_isspace(str[*i])))
			break ;
		(*i)++;
	}
	return (ft_substr(str, start, *i - start));
}
