/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser-tok.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:41:33 by danielji          #+#    #+#             */
/*   Updated: 2025/09/29 12:34:28 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

/* Allocates memory and returns a new node.
The `content` variable is initialized with the given parameter `content`.
The variable `next` is initialized to `NULL`. */
t_token	*ft_new_token(t_token_type type, char *string, int start, size_t len)
{
	t_token	*node;

	ft_printf("New Token - type: %d - str: %s\n", type, string);
	node = (t_token *)malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->type = type;
	if (type == TOK_WORD)
		node->value = ft_substr(string, start, len);
	else
		node->value = ft_strdup("prueba");
	node->next = NULL;
	return (node);
}

t_token	*tokenize(char *str)
{
	int		i;
	char	quote;
	int		start;
	t_token	*node;
	t_token	*list;

	i = 0;
	list = NULL;
	ft_printf("Tokenizing string: %s\n", str);
	while (str[i])
	{
		ft_printf("str[i]: %c\n", str[i]);
		if (ft_isspace(str[i]))
		{
			i++;
			continue ;
		}
		if (str[i] == PIPE)
		{
			node = ft_new_token(TOK_PIPE, NULL, 0, 0);
			ft_toklstadd_back(&list, node);
			i++;
		}
		else if (str[i] == LESS)
		{
			if (str[i + 1] == LESS)
			{
				node = ft_new_token(TOK_HEREDOC, NULL, 0, 0);
				ft_toklstadd_back(&list, node);
				i += 2;
			}
			else
			{
				node = ft_new_token(TOK_REDIR_IN, NULL, 0, 0);
				ft_toklstadd_back(&list, node);
				i++;
			}
		}
		else if (str[i] == GREATER)
		{
			if (str[i + 1] == GREATER)
			{
				node = ft_new_token(TOK_APPEND, NULL, 0, 0);
				ft_toklstadd_back(&list, node);
				i += 2;
			}
			else
			{
				node = ft_new_token(TOK_REDIR_OUT, NULL, 0, 0);
				ft_toklstadd_back(&list, node);
				i++;
			}
		}
		else if (str[i] == DOUBLE_QUOTE || str[i] == SINGLE_QUOTE)
		{
			// quoted string
			quote = str[i];
			i++;
			start = i;
			while (str[i] && str[i] != quote)
				i++;
			node = ft_new_token(TOK_WORD, str, start, i - start);
			ft_toklstadd_back(&list, node);
			if (str[i] == quote)
				i++; // skip closing quote
		}
		else
		{
			// plain word
			start = i;
			while (str[i] && !ft_isspace(str[i]) && str[i] != PIPE && str[i] != LESS && str[i] != GREATER)
			{
				i++;
			}
			node = ft_new_token(TOK_WORD, str, start, i - start);
			ft_toklstadd_back(&list, node);
		}
	}
	node = ft_new_token(TOK_EOF, NULL, 0, 0);
	ft_toklstadd_back(&list, node);
	return (list);
}
