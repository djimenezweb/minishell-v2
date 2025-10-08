/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 10:38:27 by danielji          #+#    #+#             */
/*   Updated: 2025/10/03 11:30:47 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checks if a string is correctly quoted. Finds opening and closing
quotation pairs. Returns `1` if it's valid, `0` if it's not */
int	quote_validation(char *str)
{
	int		i;
	char	quote;
	int		quote_count;

	i = 0;
	quote = 0;
	quote_count = 0;
	while (str[i])
	{
		if (!quote && (str[i] == DOUBLE_QUOTE || str[i] == SINGLE_QUOTE))
		{
			quote = str[i];
			quote_count++;
			i++;
		}
		if (quote && str[i] == quote)
		{
			quote_count++;
			quote = 0;
		}
		i++;
	}
	if (quote_count % 2 == 0)
		return (1);
	return (0);
}
