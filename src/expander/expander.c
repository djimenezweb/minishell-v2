/*	*	add here a header or headers	*	*/

//header file.h here

int	count_new_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!new_len && word->value[i] == DOLLAR)
		{
			new_len = i;
			while (/*end of $VAR*/)
				++i;
			++i;
			if (new_len)
				++new_len;
		}
	}
}

/*some type*/	find_expansions(t_lextoken **word)
{
	int	new_len;

	while (ft_strchr(word, DOLLAR))
	{
		new_len = count_new_len(word->value);
				//EXPAND $ENV_VAR
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
