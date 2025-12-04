/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_expansion_and_get_data.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:53:52 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/12/01 10:52:06 by danielji         ###   ########.fr       */
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

	index = 0;
	while (str[index] != '\0')
	{
		if (is_quote(str[index]))
			update_quote_flag(exp_data, str[index]);
		if (str[index] == DOLLAR && !ft_isspace(str[index + 1])
			&& exp_data->env_quoted != SINGLE_QUOTE)
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
