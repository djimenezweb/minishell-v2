/*	*	add here a header or headers	*	*/

//header file.h here

static void	update_expansion_data(t_expansion_data *exp_data)
{
	exp_data->len_modified[0] = 0;
	exp_data->len_modified[1] = 0;
	exp_data->new_len = 0;
	if (exp_data->var_name)
		free(exp_data->var_name);
	exp_data->var_name = NULL;
	if (exp_data-expanded)
		free(exp_data->expanded);
	exp_data->expanded = NULL;
	exp_data->quote_flag = 0;
}

int	count_new_len(char *str, char **name_to_expand, int dollar_position)
{
	int	i;
	int	new_len;
	int	expansion_flag;

	i = 0;
	new_len = 0;
	expansion_flag = 0;
	while (str[i])
	{
		//CREATE A STRLEN which works looking for $
		//Or maybe obtain the position with a modified strchr
		if (!expansion_flag && word->value[i] == DOLLAR)
		{
			new_len = i;
			expansion_flag = 1;

		}
		++i;
		if (expansion_flag)
			++new_len;
	}
	return (new_len);
}

/*some type*/	expand(t_lextoken **word)//ENRIQUE-10/10/25: 
					//This may work with a TOK_WORD,
					//so it's not needed to change
{
	int	new_len;
	int	dollar_position;
	char	*name_to_expand;
	char	*enviroment_expanded;
	char	*new_value;

	dollar_position = 0;
	while (ft_strchr_and_position(word, DOLLAR, dollar_position))
	{
		new_len = count_new_len(word->value,
			&name_to_expand, dollar_position);
		enviroment_expanded = getenv(name_to_expand);
		new_len += ft_strlen(enviroment_expanded);
		new_value = //function that do three memcopies
		free(word->value);
		word->value = new_value;
	}
}

void	check_token_words(t_lextoken **token_list)
{
	t_lextoken	*current;
	t_lextoken	*new_token;
	char	*new_string;
	t_expansion_data	expansion_data;

	current = *token_list;
	while (current->next)
	{
		update_expansion_data(&expansion_data);
		if (current->type == TOK_WORD)//ENRIQUE-10/10/25: Hey, a word
					      //could have quotes inside,
					      //a change here is needed
			expand(&current);//HOW RETURNS VALUE?
		else if (current->type == TOK_SINGLE_QUOTE)
			current->type = TOK_WORD;
		current = current->next;
	}
}
