/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_expansion_and_get_data.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:53:52 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/12/04 21:10:57 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_resize_data(t_expansion_data *exp_data, char *str)
{
	int	old_size;
	int	var_name_len;

	if (!exp_data->malloc_fail)
	{
		old_size = ft_strlen(str);
		var_name_len = ft_strlen(exp_data->var_name) + 1;
		exp_data->resize_len = old_size - var_name_len;
		exp_data->var_name_len = var_name_len;
	}
	return (1);
}

/*Search $ that is not quoted. If finds it, gets data to know the var_name
 * and it's size. word_token_len - var_name = number of chars we'll maintain
 * from old token_word. Later we'll add expanded_var_len to resize*/
int	find_expansion(t_expansion_data *exp_data)
{
	int	i;

	i = 0;
	while (exp_data->iterator[i] != '\0')
	{
		if (is_quote(exp_data->iterator[i]))
			update_quote_flag(exp_data, exp_data->iterator[i]);
		if (exp_data->iterator[i] == DOLLAR
			&& (exp_data->iterator[i + 1]
				&& !ft_isspace(exp_data->iterator[i + 1]))
			&& exp_data->env_quoted != SINGLE_QUOTE)
		{
			exp_data->dollar_position = i;
			exp_data->var_name
				= get_variable_name(exp_data->iterator + i);
			if (!exp_data->var_name)
				exp_data->malloc_fail = 1;
			return (set_resize_data(exp_data, exp_data->iterator));
		}
		++i;
	}
	return (0);
}
