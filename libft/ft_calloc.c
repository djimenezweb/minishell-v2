/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:36:44 by danielji          #+#    #+#             */
/*   Updated: 2025/04/21 16:30:31 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Allocates memory for an array of NELEM elements of SIZE bytes each and
returns a pointer to the allocated memory. The memory is set to zero.
If NELEM or SIZE is 0, it returns a unique pointer value that can later be
successfully passed to free(). */

#include "libft.h"

void	*ft_calloc(size_t nelem, size_t size)
{
	void	*arr;

	arr = malloc(nelem * size);
	if (!arr)
		return ((void *)0);
	ft_bzero(arr, nelem * size);
	return (arr);
}
