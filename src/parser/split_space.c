/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:51:26 by danielji          #+#    #+#             */
/*   Updated: 2025/09/23 11:05:00 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

static void	free_array(char **arr, int i)
{
	while (i > 0)
	{
		i--;
		free(arr[i]);
	}
	free(arr);
}

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

static void	**string_to_array(char **arr, char const *str, int count)
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
		// TO DO: No contar espacios dentro de comillas
		while (str[start] && str[start] == SPACE && !in_s_quote && !in_d_quote)
			start++;
		end = start + 1;
		while (str[end] && (str[end] != SPACE) && !in_s_quote && !in_d_quote)
			end++;
		arr[i] = ft_substr(str, start, (end - start));
		if (!arr[i])
		{
			free_array(arr, i);
			return (NULL);
		}
		start = end;
		i++;
	}
	arr[i] = (NULL);
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
	ft_printf("Trimmed string  = >%s<\n", str);
	count = count_substrings(str);
	ft_printf("Substring count = %d\n", count);
 	arr = malloc((count + 1) * sizeof(char *));
	if (!arr)
	{
		free(str);
		return (NULL);
	}
	string_to_array(arr, str, count);
	free(str);
	// print array
	int i = 0;
	while (arr[i])
	{
		ft_printf("%s\n", arr[i]);
		i++;
	}
	// end print array
	return (arr);
}
