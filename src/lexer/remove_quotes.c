/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:01:15 by danielji          #+#    #+#             */
/*   Updated: 2025/11/04 11:01:15 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Bash Reference Manual: 3.5.9 Quote Removal
After the preceding expansions, all unquoted occurrences of the
characters `\`, `'`, and `"` that did not result from one of the
above expansions are removed.*/
void	remove_quotes(char *str)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == SINGLE_QUOTE || str[i] == DOUBLE_QUOTE))
			quote = str[i++];
		else if (quote && str[i] == quote)
			quote = 0;
		if (quote || (str[i] != SINGLE_QUOTE && str[i] != DOUBLE_QUOTE))
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	while (str[++j])
		str[j] = '\0';
}
