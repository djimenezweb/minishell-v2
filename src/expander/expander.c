/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:52:08 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/10/22 21:13:14 by enrgil-p         ###   ########.fr       */
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
	exp_data->var_name = NULL;
	exp_data->expanded = NULL;
}

static void	reset_expansion_data(t_expansion_data *exp_data)
{
	if (exp_data->var_name)
		free(exp_data->var_name);
	init_expansion_data(exp_data);
}

static void	try_to_expand_current_word(t_lextoken **word, t_shell *data)
{
	t_expansion_data	exp_data;
	char				*new_value;

	init_expansion_data(&exp_data);
	while (find_expansion((*word)->value, &exp_data)
		&& !exp_data.malloc_fail)
	{
		exp_data.expanded = getenv(exp_data.var_name);
		printf("%s\n", exp_data.expanded);//debug
		new_value = resize_expansions((*word)->value, &exp_data);
		if (!new_value)
		{
			reset_expansion_data(&exp_data);
			free_shell(data);//ENRIQUE 22/10: I put this here 
				//expecting free_shell() executes an exit inside
		}
		free((*word)->value);
		(*word)->value = new_value;
		reset_expansion_data(&exp_data);
	}
	if (exp_data.malloc_fail)
		free_shell(data);//ENRIQUE 22/10: I put this here expecting
				 //free_shell() executes an exit inside
}

void	expander(t_shell *data)
{
	t_expansion_data	exp_data;

	init_expansion_data(&exp_data);
	t_lextoken	*current;

	current = data->lex_list;
	while (current)
	{
		if (current->type == TOK_WORD)
		{
			try_to_expand_current_word(&current, data);
			//Could put here another function for remove quotes...
			//But first, be sure to the order of execution
		}
		current = current->next;
	}
	printf("End of expander\n");
}
