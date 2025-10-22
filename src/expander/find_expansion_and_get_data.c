/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_expansion_and_get_data.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:53:52 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/10/22 21:12:03 by enrgil-p         ###   ########.fr       */
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
int	find_expansion(char *str, t_expansion_data *exp_data)
{
	int	index;
	int	quote_flag;

	index = 0;
	quote_flag = 0;
	while (str[index] != '\0')
	{
		if (str[index] == SINGLE_QUOTE || str[index] == DOUBLE_QUOTE)
			quote_flag = update_quote_flag(quote_flag, str[index]);
		if (str[index] == DOLLAR && quote_flag != SINGLE_QUOTE)
		{
			exp_data->dollar_position = index;
			exp_data->var_name = get_variable_name(str + index);
			if (!exp_data->var_name)
				exp_data->malloc_fail = 1;
			return (set_resize_data(exp_data, str));
		}
		++index;
	}
	return (0);
}
