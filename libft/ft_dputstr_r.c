/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fdr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:19:31 by danielji          #+#    #+#             */
/*   Updated: 2025/11/24 13:26:40 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Outputs the string `s` to the specified file descriptor. */
ssize_t	ft_dputstr_r(int fd, char *s)
{
	ssize_t	written;

	written = 0;
	if (!s)
		written += write(fd, "(null)", 6);
	if (*s)
		written += write(fd, s, ft_strlen(s));
	return (written);
}
