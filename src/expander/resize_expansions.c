/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:16:07 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/11/12 20:34:12 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Struct to keep in limit of lines and init dst as valgrind asks for
static void	init_joined_vars(t_join *to_init)
{
	to_init->dst = NULL;
	to_init->src = NULL;
	to_init->len = 0;
}

static void	set_len_in_loop_3(t_join *j, t_expansion_data *ed)
{
	if (j->dst[0] == '\0')
		j->len = ft_strlen(j->src) + 1;
	else
		j->len = ed->resize_len - (ed->dollar_position
				+ ed->var_name_len);
}

static void	join_expansion(char *old_str, char **new_str,
		t_expansion_data *ed, int loop_counter)
{
	t_join	joined;

	init_joined_vars(&joined);
	if (loop_counter == 1)
	{
		joined.src = old_str;
		joined.dst = *new_str;
		joined.len = ed->dollar_position;
	}
	if (loop_counter == 2)
	{
		joined.src = ed->expanded;
		joined.dst = (*new_str) + ed->dollar_position;
		joined.len = ed->expanded_len;
	}
	if (loop_counter == 3)
	{
		joined.src = old_str + (ed->dollar_position + ed->var_name_len);
		joined.dst = *new_str + (ed->dollar_position
				+ ed->expanded_len);
		set_len_in_loop_3(&joined, ed);
	}
	printf("src %s, dst %s, len %d\n", joined.src, joined.dst, joined.len);//debug
	if (joined.len != 0)
		ft_memcpy(joined.dst, joined.src, joined.len);
}

char	*resize_expansions(char *old_str, t_expansion_data *ed)
{
	char	*new_str;
	int		loop_counter;

	if (ed->expanded)
		ed->expanded_len = ft_strlen(ed->expanded);
	if (ed->expanded_len != 0)
		ed->resize_len += (ed->expanded_len - 1);
	new_str = ft_calloc((ed->resize_len + 1), sizeof(char));
	if (!new_str)
		return (NULL);
	loop_counter = 1;
	while (loop_counter <= 3)
	{
		join_expansion(old_str, &new_str, ed, loop_counter);
		++loop_counter;
	}
	return (new_str);
}
