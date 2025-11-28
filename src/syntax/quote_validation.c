/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 10:38:27 by danielji          #+#    #+#             */
/*   Updated: 2025/11/28 17:02:44 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_validation_data(int *i, char *pipe,
		char *quote, int *quote_count)
{
	*i = 0;
	*quote = 0;
	*pipe = 0;
	*quote_count = 0;
}

static void	update_quote_count(char *quote, int *quote_count, char found)
{
	if (*quote == 0)
		*quote = found;
	else
		*quote = 0;
	*quote_count += 1;
}

int	is_quote(char possible_quote)
{
	if (possible_quote == SINGLE_QUOTE || possible_quote == DOUBLE_QUOTE)
		return (1);
	return (0);
}

/* Check if a string is correctly quoted. Find opening and closing
quotation pairs. Return `1` if it's valid, `0` if it's not */
int	quote_validation(char *str)
{
	int		i;
	char	pipe;
	char	quote;
	int		quote_count;

	init_validation_data(&i, &pipe, &quote, &quote_count);
	while (str[i])
	{
		if (!quote && !pipe && (str[i] == PIPE))
			pipe = str[i++];
		while (pipe && ft_isspace(str[i]))
			++i;
		if (!quote && pipe && (str[i] == PIPE))
			break ;
		else if (!quote && pipe)
			pipe = 0;
	//if ((!quote && is_quote(str[i])) || (quote && str[i] == quote))
		if (is_quote(str[i]))
			update_quote_count(&quote, &quote_count, str[i]);
		++i;
	}
	if (!pipe && quote_count % 2 == 0)
		return (1);
	return (0);
}
