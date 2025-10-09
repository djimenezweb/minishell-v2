/*	*	add here a header or headers	*	*/

//header file.h here

/*some type*/	find_expansions(t_lextoken **word)
{
	int	i;

	while (ft_strchr(word, DOLLAR))
	{
		i = 0;
		while (word->value[i])
		{
			if (word->value[i] == DOLLAR)
				//EXPAND $ENV_VAR
			++i;
		}
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
		if (current->type == TOK_WORD)
			find_expansions(&current);//HOW RETURNS VALUE?
		else if (current->type == TOK_SINGLE_QUOTE)
			current->type = TOK_WORD;
		current = current->next;
	}
}
