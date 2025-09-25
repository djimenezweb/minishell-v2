/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:51:26 by danielji          #+#    #+#             */
/*   Updated: 2025/09/25 10:41:31 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

static int	count_substrings(char *str)
{
	int	i;
	int	count;
	int	in_s_quote;
	int	in_d_quote;

	i = 0;
	count = 0;
	in_s_quote = 0;
	in_d_quote = 0;
	while (str[i])
	{
		// Skip spaces (only when not inside quotes)
		while (str[i] && str[i] == SPACE && !in_s_quote && !in_d_quote)
			i++;
		if (str[i])
		{
			count++;
			// Walk through this substring
			while (str[i])
			{
				if (str[i] == SINGLE_QUOTE && !in_d_quote)
					in_s_quote = !in_s_quote;  // toggle
				else if (str[i] == DOUBLE_QUOTE && !in_s_quote)
					in_d_quote = !in_d_quote;  // toggle
				else if (str[i] == SPACE && !in_s_quote && !in_d_quote)
					break; // end of substring
				i++;
			}
		}
	}
	return (count);
}

static void	**string_to_array(char **arr, char *str, int count)
{
	int	i;
	int	start;
	int	end;
	int	in_s_quote;
	int	in_d_quote;

	i = 0;
	start = 0;
	end = 0;
	in_s_quote = 0;
	in_d_quote = 0;
	while (count--)
	{
		// Skip leading spaces (only outside quotes)
		while (str[start] == SPACE)
			start++;
		end = start;
		while (str[end])
		{
			if (str[end] == SINGLE_QUOTE && !in_d_quote)
				in_s_quote = !in_s_quote; // toggle
			else if (str[end] == DOUBLE_QUOTE && !in_s_quote)
				in_d_quote = !in_d_quote; // toggle;
			else if (str[end] == SPACE && !in_s_quote && !in_d_quote)
				break; // real delimiter
			end++;
		}
		arr[i] = ft_substr(str, start, (end - start));
		if (!arr[i])
		{
			free_array_n(arr, i);
			return (NULL);
		}
		start = end;
		i++;
	}
	arr[i] = (NULL);
	return (NULL);
}

char	**split_by_space(char *line)
{
	char	*str;
	char	**arr;
	int		count;

	// Trim spaces, new lines and tabs
	str = ft_strtrim(line, " \n\t");
	if (!str)
		return (NULL);
	//ft_printf("Trimmed string  = >%s<\n", str);
	count = count_substrings(str);
	//ft_printf("Substring count = %d\n", count);
 	arr = malloc((count + 1) * sizeof(char *));
	if (!arr)
	{
		free(str);
		return (NULL);
	}
	string_to_array(arr, str, count);
	free(str);
	return (arr);
}
