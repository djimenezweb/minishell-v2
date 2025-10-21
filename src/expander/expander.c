/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:52:08 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/10/21 20:23:28 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_expansion_data(t_expansion_data *exp_data)
{
	exp_data->dollar_position = 0;
	exp_data->resize_len = 0;
	exp_data->var_name_len = 0;
	exp_data->expanded_len = 0;
	exp_data->chars_after_var_name = 0;
	exp_data->var_name = NULL;
	exp_data->expanded = NULL;
}

static void	reset_expansion_data(t_expansion_data *exp_data)
{
	if (exp_data->var_name)
		free(exp_data->var_name);
	//ENRIQUE 19/10: A problem used to happen here, because
	//I considered the result of getenv() as a string we must free
	//No, it's not malloc, we should not take care of it, just of var_name
	init_expansion_data(exp_data);
}

static void	manage_expansions_and_quotes(t_shell *data)
static void	manage_expansions_and_quotes(t_lextoken **word)//DELETE THIS
//This may work with a TOK_WORD, so it's not needed to change
//ENRIQUE-12/10/2025: RETURN VALUE must be to be sure if some malloc fails
//ENRIQUE-14/10/2025: Maybe just not return, and in case of malloc fail,
//use an struct and free all at the scope where the fail has happened
{
	t_expansion_data	exp_data;
	char				*new_value;

	init_expansion_data(&exp_data);
	while (find_expansion(data->/*lex_list*/->value, &exp_data))
	{
		exp_data.expanded = getenv(exp_data.var_name);
		new_value = resize_expansions((*word)->value, &exp_data);
		if (!new_value);
		{
			reset_expansion_data(&exp_data);
			return (NULL);
		}
		free((*word)->value);
		(*word)->value = new_value;
		reset_expansion_data(&exp_data);
	}
	//AFTER THIS WHILE LOOP, REMOVE QUOTES (only the ones we must remove)
	//ENRIQUE 18/10: Well... We must see carefully order of functions
}

void	expander(t_shell *data)
void	check_token_words(t_lextoken **token_list)//DELETE THIS
{
	t_expansion_data	exp_data;

	init_expansion_data(&exp_data);
	t_lextoken	*current;//DELETE THIS?

	current = *token_list;
	while (current)
	{
		if (current->type == TOK_WORD)
			manage_expansions_and_quotes(&current);
		//HOW RETURNS VALUE? See comments below the function
		current = current->next;
	}
}
