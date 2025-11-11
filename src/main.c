/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:18:33 by danielji          #+#    #+#             */
/*   Updated: 2025/11/10 13:18:20 by danielji         ###   ########.fr       */
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

/* Free all allocated memory relative to the last prompt line */
static void	cleanup_line(t_shell *data)
{
	if (data->line)
		free(data->line);
	data->line = NULL;
	if (data->lex_list)
		ft_lexlist_clear(&(data->lex_list));
	data->lex_list = NULL;
	if (data->cmd_list)
		ft_cmdlist_clear(&data->cmd_list);
	data->cmd_list = NULL;
}

void	free_shell(t_shell *data)
{
	//printf("free_shell\n");//debug
	//printf("cmd node to free is %p, cmd is %p, arg 0 == %s\n", data->cmd_list, data->cmd_list->cmd, data->cmd_list->cmd[0]);//debug
	if (data->line)
		free(data->line);
	data->line = NULL;
	if (data->lex_list)
		ft_lexlist_clear(&(data->lex_list));
	data->lex_list = NULL;
	if (data->env_list)
		ft_envlist_clear(&(data->env_list));
	data->env_list = NULL;
	//printf("cmd_list is %p\n", data->cmd_list);//debug
	//printf("Free cmd\n");//debug
	if (data->cmd_list)
		ft_cmdlist_clear(&data->cmd_list);
	data->cmd_list = NULL;
	data = NULL;
	//ENRIQUE 22/10: May put here an exit? WHat exit status?
	//Any status different to zero is fail status
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell_data;

	if (argc > 1)
		return (1);
	(void)argv;
	init_shell(&shell_data, envp);
	if (!shell_data.env_list)
		return (1);//ENRIQUE 7/11: Case of malloc error. Just return 1, or set a message too?
	while (1)
	{
		shell_data.line = readline("$ ");
		add_history(shell_data.line);
		// Type `q` to exit (DEBUG ONLY)
		if (shell_data.line[0] == 'q' && shell_data.line[1] == '\0')	// debug
			return (rl_clear_history(), free_shell(&shell_data), 0);	// debug
		if (!quote_validation(shell_data.line) || !expander(&shell_data.line, shell_data.env_list))
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
		print_lex_list(shell_data.lex_list); // debug
		shell_data.cmd_list = parser(shell_data.lex_list);
		//printf("Cmd_list is %p\n", shell_data.cmd_list);//debug
		//shell_data.cmd_list = parser(shell_data.lex_list);
	/*	if (shell_data.cmd_list)
		{
			free_shell(&shell_data);
			return (1);
		}*/
		//printf("After parser\n");//debug
		//printf("cmd node is %p, cmd is %p, arg 0 == %s\n", shell_data.cmd_list, shell_data.cmd_list->cmd, shell_data.cmd_list->cmd[0]);//debug
		execution(&shell_data);
		cleanup_line(&shell_data);
		//free_shell(&shell_data);
	}
	return (0);
}
