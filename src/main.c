/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:18:33 by danielji          #+#    #+#             */
/*   Updated: 2025/10/09 18:49:52 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

/*BELOW FOR TEST PURPOSES ONLY */
static void	print_lex_list(t_lextoken *list)
{
	t_lextoken	*curr;

	curr = list;
	while (curr)
	{
		if (curr->type == TOK_WORD)
			ft_printf("WORD(%s)\n", curr->value);
		if (curr->type == TOK_SINGLE_QUOTE)
			ft_printf("SQUOTED_WORD(%s)\n", curr->value);
		else if (curr->type == TOK_PIPE)
			ft_printf("PIPE\n");
		else if (curr->type == TOK_REDIR_IN)
			ft_printf("REDIR_IN\n");
		else if (curr->type == TOK_REDIR_OUT)
			ft_printf("REDIR_OUT\n");
		else if (curr->type == TOK_APPEND)
			ft_printf("APPEND\n");
		else if (curr->type == TOK_HEREDOC)
			ft_printf("HEREDOC\n");
		else if (curr->type == TOK_EOF)
			ft_printf("EOF\n");
		curr = curr->next;
	}
}

void	print_array_of_strings(char **arr)
{
	int i = 0;
	while (1)
	{
		if (arr[i] == NULL)
		{
			printf("%d) >NULL<\n", i);
			break ;
		}
		printf("%d) >%s<\n", i, arr[i]);
		i++;
	}
}

/*ABOVE FOR TEST PURPOSES ONLY */

// Command example: cat << EOF | grep foo >> out.txt
int	main(void)
{
	char		*line;
	t_lextoken	*token_list;
	//char		**arr;

	while (1)
	{
		line = readline("$ ");
		add_history(line);
		//arr = history_tokenize(line);
		//print_array_of_strings(arr);
		if (!quote_validation(line))
		{
			free(line);
			return (1);
		}
		//printf("VARIABLE NAME = >%s<\n", get_variable_name(line));
		token_list = lexer(line);
		print_lex_list(token_list);
		free(line);
		ft_lexlist_clear(&token_list);
	}
	return (0);
}
