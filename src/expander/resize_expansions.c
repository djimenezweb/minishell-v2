/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:16:07 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/10/14 20:02:04 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	join_expansion(char *old_str, char **new_str,
		t_expansion_data *ed, int loop_counter)
{
	char	*src;
	char	*dst;
	int		len;

	if (loop_counter == 1)
	{
		src = old_str;
		dst = *new_str;
		len = ed->dollar_position;
	}
	if (loop_counter == 2)
	{
		src = ed->expanded;
		dst = *new_str + ed->dollar_position;
		len = ed->expanded_len;
	}
	if (loop_counter == 3)
	{
		src = old_str + (ed->dollar_position + ed->var_name_len);
		dst = *new_str + (ed->dollar_position + ed->expanded_len);
		len = ed->resize_len - (ed->dollar_position
				+ ed->var_name_len);
	}
	if (len != 0)
		*new_str = ft_memcpy(dest, src, len);
}

char	*resize_expansions(char *old_str, t_expansion_data *ed)
{
	char	*new_str;
	int		loop_counter;

	ed->expanded_len = ft_strlen(ed->expanded);
	if (ed->expanded_len != 0)
		ed->resize_len += (ed->expanded_len - 1);
	new_str = (char *)malloc((ed->resize_len + 1) * sizeof(char));
	if (!new_str)//Above line could be ft_calloc. Needed? Not sure
		return (NULL);//Review other mallocs 
			      //to be sure of the protection
	new_str[ed->resize_len] = '\0';
	loop_counter = 1;
	while (loop_counter <= 3)
	{
		join_expansion(old_str, &new_str, ed, loop_counter);
		++loop_counter;
	}
	return (new_str);
}
