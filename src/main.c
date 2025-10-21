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

static void	init_shell(t_shell *data, char **envp)
{
	data->line = NULL;
	data->lex_list = NULL;
	data->env_list = set_env_vars(envp);
	//To be continued...
}

void	free_shell(t_shell *data)
{
	if (data->line)
		free(data->line);
	if (data->lex_list)
		ft_lexlist_clear(&(data->lex_list));
	if (data->env_list)
		ft_envlist_clear(&(data->env_list));
	data->line = NULL;
	data->lex_list = NULL;
	data->env_list = NULL;
	data = NULL;
}

// Command example: cat << EOF | grep foo >> out.txt
int	main(int argc, char **argv, char **envp)
{
	t_shell		shell_data;

	if (argc > 1)
		return (1);
	(void)argv;
	init_shell(&shell_data, envp);
	if (!shell_data.env_list)
	{
		return (1);
	}
	while (1)
	{
		// Use ft_strdup instead of readline to check memory leaks:
		//shell_data.line = ft_strdup("hola hola");
		shell_data.line = readline("$ ");
		add_history(shell_data.line);
		//char **arr = history_tokenize(shell_data.line);
		//print_array_of_strings(arr);
		if (!quote_validation(shell_data.line))
		{
			free_shell(&shell_data);
			return (1);
		}
		shell_data.lex_list = lexer(shell_data.line);
		if (!shell_data.lex_list)
		{
			free_shell(&shell_data);
			return (1);
		}
		if (!syntax_validation(shell_data.lex_list))
		{
			free_shell(&shell_data);
			return (1);
		}
		//check_token_words(&shell_data.lex_list);
		print_lex_list(shell_data.lex_list);
		free_shell(&shell_data);
	}
	return (0);
}
