/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:52:08 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/10/18 21:28:43 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_expansion_data(t_expansion_data *exp_data)
{
	exp_data->dollar_position = 0;
	exp_data->resize_len = 0;
	exp_data->var_name_len = 0;
	exp_data->expanded_len = 0;
	if (exp_data->var_name)
		free(exp_data->var_name);
	if (exp_data->expanded)
		free(exp_data->expanded);
	exp_data->expanded = NULL;
}

static void	manage_expansions_and_quotes(t_lextoken **word) 
					//This may work with a TOK_WORD,
					//so it's not needed to change
//ENRIQUE-12/10/2025: RETURN VALUE must be to be sure if some malloc fails
//ENRIQUE-14/10/2025: Maybe just not return, and in case of malloc fail,
//use an struct and free all at the scope where the fail has happened
{
	char	*new_value;
	t_expansion_data	exp_data;

	update_expansion_data(&exp_data);
	while (find_expansion_and_get_data(word->value, &exp_data))
	{
		exp_data.expanded = getenv(exp_data.var_name);
		new_value = resize_expansions(word->value, &exp_data); 
		free(word->value);
		word->value = new_value;
		update_expansion_data(&exp_data);
	}
	//AFTER THIS WHILE LOOP, REMOVE QUOTES (only the ones we must remove)
}

void	check_token_words(t_lextoken **token_list)
{
	t_lextoken	*current;//ENRIQUE says: WHY DO WE NEED CURRENT?

	current = *token_list;
	while (current)
	{
		if (current->type == TOK_WORD)
			manage_expansions_and_quotes(&current);
		//HOW RETURNS VALUE?
		current = current->next;
	}
}
