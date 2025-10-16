/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_expansion_and_get_data.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:53:52 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/10/12 20:44:41 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_quote_flag(int quote_flag)
{
	if (!quote_flag)
		return (SINGLE_QUOTE);
	return (0);
}

static void	set_resize_data(t_expansion_data *exp_data, char *str)
{
	int	old_size;
	int	var_name_len;

	old_size = ft_strlen(str);
	var_name_len = ft_strlen(exp_data->var_name);
	exp_data->resize_len = old_size - var_name_len;
	exp_data->var_name_len = var_name_len + 1;//REVIEW THIS
	exp_data->third_start = exp_data->dollar_position + var_name_len + 1;
}

/*Search $ that is not quoted. If finds it, gets data to know the var_name
 * and it's size. word_token_len - var_name = number of chars we'll maintain
 * from old token_word. Later we'll add expanded_var_len to resize*/
int	find_expansion_and_get_data(const char *str, t_expansion_data *exp_data)
{
	int	position;
	int	quote_flag;

	position = 0;
	quote_flag = 0;
	while (str[position] != '\0')
	{
		if (str[position] == SINGLE_QUOTE)
			quote_flag = update_quote_flag(quote_flag);
		if (str[position] == DOLLAR && !quote_flag)
		{
			exp_data->dollar_position = position;
			exp_data->expanded = get_variable_name((char *)&str[position]);
			set_resize_data(exp_data, (char *)str);
			return (1);
		}
		++position;
	}
	return (0);
}
