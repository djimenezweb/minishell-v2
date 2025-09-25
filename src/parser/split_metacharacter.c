/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_metacharacter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:51:26 by danielji          #+#    #+#             */
/*   Updated: 2025/09/25 11:38:03 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

static int	count_substrings(char **arr)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (arr[i])
	{
		count++;
		j = 0;
		while (arr[i][j])
		{
			if (arr[i][j] == PIPE)
				count++;
			if (arr[i][j] == GREATER)
			{
				count++;
				if (arr[i][j + 1] == GREATER)
					j++;
			}
			if (arr[i][j] == LESS)
			{
				count++;
				if (arr[i][j + 1] == LESS)
					j++;
			}
			j++;
		}
		i++;
	}
	return (count);
}

char	**split_by_metacharacter(char **arr)
{
	int count;

	count = count_substrings(arr);
	ft_printf("Substrings: %d\n", count);
	return (arr);
}
