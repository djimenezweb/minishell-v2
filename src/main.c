/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:18:33 by danielji          #+#    #+#             */
/*   Updated: 2025/11/09 23:24:23 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_shell(t_shell *data, char **envp)
{
	data->line = NULL;
	data->lex_list = NULL;
	data->env_list = set_env_vars(envp);//ENRIQUE 1/11: If a malloc error
					    //happens inside, how we stop,
					    //clean and exit?
	data->cmd_list = NULL;
	//To be continued...
}

void	free_shell(t_shell *data)
{
	printf("free_shell\n");//debug
	printf("cmd node to free is %p, cmd is %p, arg 0 == %s\n", data->cmd_list, data->cmd_list->cmd, data->cmd_list->cmd[0]);//debug
	if (data->line)
		free(data->line);
	if (data->lex_list)
		ft_lexlist_clear(&(data->lex_list));
	if (data->env_list)
		ft_envlist_clear(&(data->env_list));
	printf("cmd_list is %p\n", data->cmd_list);//debug
	if (data->cmd_list)
		ft_cmdlist_clear(&data->cmd_list);
	data->line = NULL;
	data->lex_list = NULL;
	data->env_list = NULL;
	data->cmd_list = NULL;
	printf("Free cmd\n");//debug
	data = NULL;
	//ENRIQUE 22/10: May put here an exit? WHat exit status?
	//Any status different to zero is fail status
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
		return (1);//ENRIQUE 7/11: Case of malloc error. Just return 1, or set a message too?
	while (1)
	{
		// Use ft_strdup instead of readline to check memory leaks:
		//shell_data.line = ft_strdup("hola hola");
		shell_data.line = readline("$ ");
		add_history(shell_data.line);
		//char **arr = history_tokenize(shell_data.line);
		//print_array_of_strings(arr);
		if (!quote_validation(shell_data.line) || !expander(&shell_data.line))
		{
			free_shell(&shell_data);
			return (1);
		}
		shell_data.lex_list = lexer(shell_data.line);//If we pass t_shell, we could merge this
													//function in the condition above
		if (!shell_data.lex_list || !syntax_validation(shell_data.lex_list))
		{
			free_shell(&shell_data);
			return (1);
		}//After lexer... We could free the shell_data.line??? ;)
		print_lex_list(shell_data.lex_list);
		shell_data.cmd_list = parser(shell_data.lex_list);
		printf("Cmd_list is %p\n", shell_data.cmd_list);//debug
		//shell_data.cmd_list = parser(shell_data.lex_list);
	/*	if (shell_data.cmd_list)
		{
			free_shell(&shell_data);
			return (1);
		}*/
		printf("After parser\n");//debug
		printf("cmd node is %p, cmd is %p, arg 0 == %s\n", shell_data.cmd_list, shell_data.cmd_list->cmd, shell_data.cmd_list->cmd[0]);//debug
		free_shell(&shell_data);
	}
	return (0);
}
