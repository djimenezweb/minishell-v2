/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_metacharacter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:51:26 by danielji          #+#    #+#             */
/*   Updated: 2025/09/23 12:47:14 by danielji         ###   ########.fr       */
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

		}
		i++;
	}
}

char	**split_by_metacharacter(char **arr)
{
	int count;

	count = count_substringss(arr);
	
}
