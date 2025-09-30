/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser-tok.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:41:33 by danielji          #+#    #+#             */
/*   Updated: 2025/09/30 11:15:08 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ismetachar(char c)
{
	if (c == PIPE || c == LESS || c == GREATER)
		return (1);
	return (0);
}

t_token	*ft_new_basic_token(t_token_type type, int *i)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = NULL;
	node->next = NULL;
	if (i != NULL)
		*i = (*i) + 1;
	return (node);
}

t_token	*ft_new_word_token(char *str, int start, int len)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->type = TOK_WORD;
	node->value = ft_substr(str, start, len);
	node->next = NULL;
	return (node);
}

t_token	*ft_new_unquoted_string(char *str, int *i)
{
	int		start;
	t_token	*node;

	start = *i;
	while (str[*i] && !ft_isspace(str[*i]) && !ft_ismetachar(str[*i]))
		*i = (*i) + 1;
	node = ft_new_word_token(str, start, *i - start);
	return (node);
}

/* Skips starting and closing quotes and returns new word token */
t_token	*ft_new_quoted_string(char *str, int *i)
{
	char	quote;
	int		start;
	t_token	*node;

	quote = str[*i];
	*i = (*i) + 1;
	start = *i;
	while (str[*i] && str[*i] != quote)
		*i = (*i) + 1;
	node = ft_new_word_token(str, start, *i - start);
	if (str[*i] == quote)
		*i = (*i) + 1;
	return (node);
}

t_token	*ft_new_redir_token(t_token_type type, char next_char, int *i)
{
	t_token	*node;

	node = NULL;
	if (type == LESS)
	{
		if (next_char == LESS)
		{
			node = ft_new_basic_token(TOK_HEREDOC, i);
			*i = (*i) + 1;
		}
		else
			node = ft_new_basic_token(TOK_REDIR_IN, i);
	}
	else if (type == GREATER)
	{
		if (next_char == GREATER)
		{
			node = ft_new_basic_token(TOK_APPEND, i);
			*i = (*i) + 1;
		}
		else
			node = ft_new_basic_token(TOK_REDIR_OUT, i);
	}
	return (node);
}

t_token	*tokenize(char *str)
{
	int		i;
	t_token	*node;
	t_token	*list;

	i = 0;
	node = NULL;
	list = NULL;
	while (str[i])
	{
		if (ft_isspace(str[i]))
		{
			i++;
			continue ;
		}
		if (str[i] == PIPE)
			node = ft_new_basic_token(TOK_PIPE, &i);
		else if (str[i] == LESS)
			node = ft_new_redir_token(LESS, str[i + 1], &i);
		else if (str[i] == GREATER)
			node = ft_new_redir_token(GREATER, str[i + 1], &i);
		else if (str[i] == DOUBLE_QUOTE || str[i] == SINGLE_QUOTE)
			node = ft_new_quoted_string(str, &i);
		else
			node = ft_new_unquoted_string(str, &i);
		ft_toklstadd_back(&list, node);
	}
	node = ft_new_basic_token(TOK_EOF, NULL);
	ft_toklstadd_back(&list, node);
	return (list);
}
