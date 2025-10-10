/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_and_position.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:53:52 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/10/10 20:03:35 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Works like a strchr, bnut also gives us, by reference,
 * where is the char we are looking for*/
char	*ft_strchr_and_position(const char *str, int c, int *position)
{
	*position = 0;
	while (str* != '\0')
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
		*position++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	return ((void *)0);
}
