/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:52:08 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/12/04 21:10:37 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_expansion_data(t_expansion_data *exp_data, char *str)
{
	exp_data->iterator = str;
	exp_data->dollar_position = 0;
	exp_data->resize_len = 0;
	exp_data->var_name_len = 0;
	exp_data->expanded_len = 0;
	exp_data->malloc_fail = 0;
	exp_data->env_quoted = 0;
	exp_data->var_name = NULL;
	exp_data->expanded = NULL;
}

static void	reset_expansion_data(t_expansion_data *exp_data, char *str)
{
	if (exp_data->var_name)
		free(exp_data->var_name);
	init_expansion_data(exp_data, str);
}

void	quote_chars_in_expanded_vars(char **str, t_protect_chars_status status)
{
	char	*ptr;

	if (!*str)
		return ;
	if (status == PROTECT)
	{
		ptr = *str;
		while (ptr)
			swap_char_value(&ptr, DOUBLE_QUOTE, TEMP_DOUBLE_QUOTE);
		ptr = *str;
		while (ptr)
			swap_char_value(&ptr, SINGLE_QUOTE, TEMP_SINGLE_QUOTE);
	}
	if (status == RESTORE)
	{
		ptr = *str;
		while (ptr)
			swap_char_value(&ptr, TEMP_DOUBLE_QUOTE, DOUBLE_QUOTE);
		ptr = *str;
		while (ptr)
			swap_char_value(&ptr, TEMP_SINGLE_QUOTE, SINGLE_QUOTE);
	}
}

int	expander(char **str, t_env_var *list)
{
	t_expansion_data	exp_data;
	char				*new_str;

	init_expansion_data(&exp_data, *str);
	protect_heredoc_delimiter(str, PROTECT, exp_data);
	while (find_expansion(&exp_data) && !exp_data.malloc_fail)
	{
		exp_data.expanded = get_env_value(list, exp_data.var_name);
		quote_chars_in_expanded_vars(&exp_data.expanded, PROTECT);
		new_str = resize_expansions(*str, &exp_data);
		if (!new_str)
		{
			reset_expansion_data(&exp_data, NULL);
			return (0);
		}
		free(*str);
		*str = new_str;
		reset_expansion_data(&exp_data,
			*str + exp_data.dollar_position);
	}
	if (exp_data.malloc_fail)
		return (0);
	protect_heredoc_delimiter(str, RESTORE, exp_data);
	return (1);
}
