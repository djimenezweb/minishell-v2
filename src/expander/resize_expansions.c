/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:16:07 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/10/13 19:16:19 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*resize_expansions(char *old_str, t_expansion_data *ed)
{
	int	expanded_len;
	char	*new_str;
	int	loop_counter;

	expanded_len = ft_strlen(ed->expanded);
	if (expanded_len != 0)
		ed->resize_len += (expanded_len - 1);
	new_str = (char *)malloc((ed->resize_len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);//Review other mallocs 
			      //to be sure of the protection
	new_str[ed->resize_len] = '\0';
	loop_counter = 1;
	while (loop_counter <= 3)
	{
		join_expansion(old_str, new_str, ed, loop_counter);
		++loop_counter;
	}
	new_str = ft_memcpy(new_str, old_str, ed->dollar_position);
	if (expanded_len != 0)
		new_str = ft_memcpy((new_str + ed->dollar_position),
				ed->expanded, (expanded_len - 1));
	third_src_start = ed->third_start;//THIS COULD BE A AUX FUNCTION
	third_len_size = ft_strlen(old_str) -
		(ed->dollar_position + ed->var_name_len);
	new_str = ft_memcpy((new_str + (ed->dollar_position + expanded_len)),
			(old_str + ed->third_start), third_len_size);
}
