/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_strings_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 12:53:24 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/12/01 13:01:20 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_strings_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i++]);
	}
	free(array);
	array = NULL;
}
