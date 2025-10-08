/*	*	add here a header or headers	*	*/

//header file.h here

char	*remove_quotation(char *quote_string)
{
	size_t	new_len;
	char	*new_string;

	new_len = ft_strlen(quote_string) - 2;
	if (!ft_strchr(quote_sring, '$'))
	{
		//new_string = ft_substr(quote_string + 1, stop at new_len);	
		return (new_string);
	}
	else

}

void	find_words_to_expand(t_lextoken **token_list)
{
	t_lextoken	*current;
	t_lextoken	*new_token;
	char	*new_string;

	current = *token_list;
	while (current->next)
	{
		if (current->type == TOK_WORD)
		{
			if (current->value[0] == DOLLAR)
			{
				//EXPAND $ENV_VAR
			}
			if (current->value[0] == DOUBLE QUOTE
				||current->value[0] == QUOTE)
			{
				new_string = remove_quotation(&current->value);
				free(current->value);
				current->value = new_string;
			}
		}
		current = current->next;
	}
}
