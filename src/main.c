/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:18:33 by danielji          #+#    #+#             */
/*   Updated: 2025/10/21 10:46:12 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
static void	init_shell(t_shell *data, char **envp)
{
	data->line = NULL;
	data->lex_list = NULL;
	data->env_list = set_env_vars(envp);
	//To be continued...
}

// Command example: cat << EOF | grep foo >> out.txt
int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_shell		shell_data;
	t_lextoken	*token_list;

	init_shell(&shell_data, envp);
	while (1)
	{
		line = readline("$ ");
		add_history(line);
		//char **arr = history_tokenize(line);
		//print_array_of_strings(arr);
		if (!quote_validation(line))
		{
			free(line);
			return (1);
		}
		shell.lex_list = lexer(line);
		if (!syntax_validation(token_list))
			return (1);
		check_token_words(&token_list);
		print_lex_list(token_list);
		free(line);
		ft_lexlist_clear(&token_list);
	}	
	return (0);
}
