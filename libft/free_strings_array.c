/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_strings_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 12:53:24 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/11/09 23:02:09 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* To debug add to line 23:
ft_printf("Free array to %s\n", array[i]);//debug */
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
