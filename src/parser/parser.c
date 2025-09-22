/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:51:26 by danielji          #+#    #+#             */
/*   Updated: 2025/09/22 11:00:39 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

int	count_substrings(char *str)
{
	int	i;
	int	count;
	int	inside_quote;

	i = 0;
	count = 0;
	inside_quote = 0;
	while (str[i])
	{
		if (str[i] == DOUBLE_QUOTE && !inside_quote)		
		{
			if (!inside_quote)
			{
				inside_quote = 1;
				count++;
			}
			else
				inside_quote = 0;
			while (str[i] != DOUBLE_QUOTE)
				i++;
		}			
		if (str[i] == SPACE && !inside_quote)
		{
			count++;
			while (str[i] == SPACE)
				i++;
		}
		i++;
	}
	return (count + 1);
}

// char	**split_by_metacharacter(char *line)
void	split_by_metacharacter(char *line)
{
	char	*str;
	//char	**arr;
	int		count;

	// Trim spaces, new lines and tabs
	str = ft_strtrim(line, " \n\t");
	if (!str)
		return ;
	ft_printf("Trimmed string  = >%s<\n", str);
	count = count_substrings(str);
	ft_printf("Substring count = %d\n", count);
/* 	arr = malloc((count + 1) * sizeof(char *));
	if (!arr)
	{
		free(str);
		return ((void *)0);
	}
	string_to_array(arr, str, c, count);
	free(str);
	return (arr); */
	free(str);
	return ;
}