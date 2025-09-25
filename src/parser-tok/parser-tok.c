/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser-tok.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:41:33 by danielji          #+#    #+#             */
/*   Updated: 2025/09/25 20:38:26 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

int	ft_isspace(char c)
{
	if ((c == SPACE) || (c >= 9 && c <= 12))
		return (1);
	return (0);
}

void	free_tokens(t_token_array *arr)
{
	size_t	i;

	i = 0;
	while (i < arr->count)
	{
		free(arr->tokens[i].value);
		i++;
	}
	free(arr->tokens);
	arr->tokens = NULL;
	arr->count = 0;
}

static void	add_token(t_token_array *arr, TokenType type, char *start, size_t len)
{
	size_t	i;
	t_token	*new_tokens;
	t_token	*t;
	
	// allocate new array, 1 bigger
	new_tokens = malloc((arr->count + 1) * sizeof(t_token));
	if (!new_tokens) {
		// to do: handle error
		exit(1);
	}

	// copy old tokens (if any)
	i = 0;
	while (i < arr->count)
	{
		new_tokens[i] = arr->tokens[i];
		i++;
	}

	// free old array
	free(arr->tokens);

	// assign new array
	arr->tokens = new_tokens;

	// add the new token
	t = &arr->tokens[arr->count++];
	t->type = type;
	if (type == TOK_WORD)
		t->value = ft_substr(start, 0, len);
	//t->value = strndup(start, len);
	else
		t->value = NULL;	
}

t_token_array	tokenize(char *input)
{
	char			*p;
	char			quote;
	char			*start;
	t_token_array	arr = {0};
	
	p = input;
	while (*p)
	{
		if (ft_isspace(*p))
		{
			p++;
			continue;
		}
		if (*p == PIPE)
		{
			add_token(&arr, TOK_PIPE, NULL, 0);
			p++;
		}
		else if (*p == LESS)
		{
			if (*(p+1) == LESS)
			{
				add_token(&arr, TOK_HEREDOC, NULL, 0);
				p += 2;
			}
			else
			{
				add_token(&arr, TOK_REDIRECT_IN, NULL, 0);
				p++;
			}
		}
		else if (*p == GREATER)
		{
			if (*(p+1) == GREATER)
			{
				add_token(&arr, TOK_REDIRECT_OUT_APPEND, NULL, 0);
				p += 2;
			}
			else
			{
				add_token(&arr, TOK_REDIRECT_OUT, NULL, 0);
				p++;
			}
		}
		else if (*p == DOUBLE_QUOTE || *p == SINGLE_QUOTE)
		{
			// quoted string
			quote = *p++;
			start = p;
			while (*p && *p != quote)
				p++;
			add_token(&arr, TOK_WORD, start, p - start);
			if (*p == quote)
				p++; // skip closing quote
		}
		else
		{
			// plain word
			start = p;
			while (*p && !ft_isspace(*p) && *p != PIPE && *p != LESS && *p != GREATER)
			{
				p++;
			}
			add_token(&arr, TOK_WORD, start, p - start);
		}
	}
	add_token(&arr, TOK_EOF, NULL, 0);
	return (arr);
}
