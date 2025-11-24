/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fdr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:23:30 by danielji          #+#    #+#             */
/*   Updated: 2025/11/24 13:25:47 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Outputs the integer `n` and returns number of characters written */
ssize_t	ft_dputnbr_r(int fd, int n)
{
	char	c;
	ssize_t	written;

	written = 0;
	if (n == -2147483648)
	{
		written += write(fd, "-2147483648", 11);
		return (written);
	}
	if (n < 0)
	{
		written += write(fd, "-", 1);
		n = n * (-1);
	}
	if (n / 10 > 0)
	{
		written += ft_dputnbr_r(fd, n / 10);
	}
	c = (n % 10) + '0';
	written += write(fd, &c, 1);
	return (written);
}
