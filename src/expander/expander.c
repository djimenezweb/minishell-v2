/*	*	add here a header or headers	*	*/

//header file.h here

int	count_new_len(char *str, int *dollar_position)
{
	int	i;
	int	new_len;
	int	expansion_flag;

	i = 0;
	new_len = 0;
	expansion_flag = 0;
	while (str[i])
	{
		if (!expansion_flag && word->value[i] == DOLLAR)
		{
			new_len = i;
			*dollar_position = i;
			expansion_flag = 1;
			while (/*end of $VAR*/)
				++i;
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
	char	*enviroment_expanded;
	char	*new_value;

	dollar_position = 0;
	while (ft_strchr(word, DOLLAR))
	{
		new_len = count_new_len(word->value, &dollar_position);
		//What string we put to getenv? Buddy... Make a struct,
		//and get in count_new_len the whole name of env
		enviroment_expanded = getenv();
		/*struct->env_len*/ = ft_strlen(enviroment_expanded);
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

	current = *token_list;
	while (current->next)
	{
		if (current->type == TOK_WORD)//ENRIQUE-10/10/25: Hey, a word
					      //could have quotes inside,
					      //a change here is needed
			expand(&current);//HOW RETURNS VALUE?
		else if (current->type == TOK_SINGLE_QUOTE)
			current->type = TOK_WORD;
		current = current->next;
	}
}
