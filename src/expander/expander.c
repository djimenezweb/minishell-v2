/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:52:08 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/11/10 13:22:21 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_expansion_data(t_expansion_data *exp_data)
{
	exp_data->dollar_position = 0;
	exp_data->resize_len = 0;
	exp_data->var_name_len = 0;
	exp_data->expanded_len = 0;
	exp_data->malloc_fail = 0;
	exp_data->env_quoted = 0;
	exp_data->var_name = NULL;
	exp_data->expanded = NULL;
}

static void	reset_expansion_data(t_expansion_data *exp_data)
{
	if (exp_data->var_name)
		free(exp_data->var_name);
	init_expansion_data(exp_data);
}

int	expander(char **str, t_env_var *list)
{
	t_expansion_data	exp_data;
	char				*new_str;

	init_expansion_data(&exp_data);
	while (find_expansion(*str, &exp_data) && !exp_data.malloc_fail)
	{
		exp_data.expanded = get_env_value(list, exp_data.var_name);
		new_str = resize_expansions(*str, &exp_data);
		if (!new_str)
		{
			reset_expansion_data(&exp_data);
			return (0);
		}
		free(*str);
		*str = new_str;
		reset_expansion_data(&exp_data);
	}
	if (exp_data.malloc_fail)
		return (0);
	return (1);
}
