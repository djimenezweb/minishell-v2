/*	*	add here a header or headers	*	*/

//header file.h here

static void	update_expansion_data(t_expansion_data *exp_data)
{
	exp_data->dollar_position = 0;
	exp_data->resize_len = 0;
	if (exp_data->var_name)
		free(exp_data->var_name);
	if (exp_data->expanded)
		free(exp_data->expanded);
	exp_data->expanded = NULL;
}

static /*some type*/	manage_expansions_and_quotes(t_lextoken **word) 
					//This may work with a TOK_WORD,
					//so it's not needed to change
//ENRIQUE-12/10/2025: RETURN VALUE must be to be sure if some malloc fails
{
	char	*new_value;
	t_expansion_data	expansion_data;

	dollar_position = 0;
	update_expansion_data(&expansion_data);
	while (find_expansion_and_get_data(word, exp_data))
	{
		exp_data->expanded = getenv(exp_data->var_name);
		new_value = //function that do three memcopies
		free(word->value);
		word->value = new_value;
		update_expansion_data(&expansion_data);
	}
	//AFTER THIS WHILE LOOP, REMOVE QUOTES (only the ones we must remove)
}

void	check_token_words(t_lextoken **token_list)
{
	t_lextoken	*current;//ENRIQUE says: WHY DO WE NEED CURRENT?
	t_lextoken	*new_token;
	char	*new_string;

	current = *token_list;
	while (current->next)
	{
		if (current->type == TOK_WORD)//ENRIQUE-10/10/25: Hey, a word
					      //could have quotes inside,
					      //a change here is needed
			manage_expansions_and_quotes(&current);
		//HOW RETURNS VALUE?
		else if (current->type == TOK_SINGLE_QUOTE)
			current->type = TOK_WORD;
		current = current->next;
	}
}
