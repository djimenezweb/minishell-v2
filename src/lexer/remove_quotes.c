/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:01:15 by danielji          #+#    #+#             */
/*   Updated: 2025/11/30 17:13:28 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Copy next char to the previous, called here as first. Returns 1 to increase j
static int	copy_next_char(char *first, char *next_char)
{
	*first = *next_char;
	return (1);
}

/* Bash Reference Manual: 3.5.9 Quote Removal
After the preceding expansions, all unquoted occurrences of the
characters `\`, `'`, and '"' that did not result from one of the
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
		if (!quote && (is_quote(str[i]) && str[i + 1] == str[i]))
		{
			i += 2;
			continue ;
		}
		if (!quote && is_quote(str[i]))
			quote = str[i++];
		else if (quote && str[i] == quote)
			quote = 0;
		if (quote || !is_quote(str[i]))
			j += copy_next_char(&str[j], &str[i]);
		++i;
	}
	str[j] = '\0';
	while (str[++j])
		str[j] = '\0';
}
