/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:52:08 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/10/12 20:54:02 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_expansion_data(t_expansion_data *exp_data)
{
	exp_data->dollar_position = 0;
	exp_data->resize_len = 0;
	exp_data->var_name_len = 0;
	exp_data->third_start = 0;
	if (exp_data->var_name)
		free(exp_data->var_name);
	if (exp_data->expanded)
		free(exp_data->expanded);
	exp_data->expanded = NULL;
}

static char	*resize_expansions(char *old_str, t_expansion_data *ed)
{
	int	expanded_len;
	char	*new_str;
	int	third_src_start;
	int	third_len_size;

	expanded_len = ft_strlen(ed->expanded);
	if (expanded_len != 0)
		ed->resize_len += (expanded_len - 1);
	new_str = (char *)malloc((ed->resize_len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);//Review other mallocs 
			      //to be sure of the protection
	new_str[ed->resize_len] = '\0';
	new_str = ft_memcpy(new_str, old_str, ed->dollar_position);
	if (expanded_len != 0)
		new_str = ft_memcpy((new_str + ed->dollar_position),
				ed->expanded, (expanded_len - 1));
	third_src_start = ed->third_start;//THIS COULD BE A AUX FUNCTION
	third_len_size = ft_strlen(old_str) -
		(ed->dollar_position + ed->var_name_len);
	new_str = ft_memcpy((new_str + (ed->dollar_position + expanded_len)),
			(old_str + ed->third_start), third_len_size);
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
	while (find_expansion_and_get_data(word->value, &exp_data))
	{
		exp_data.expanded = getenv(exp_data.var_name);
		new_value = resize_expansions(word->value, &exp_data); 
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
