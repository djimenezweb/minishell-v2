/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:18:33 by danielji          #+#    #+#             */
/*   Updated: 2025/12/01 10:32:11 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_heredoc_signal = 1;

static void	init_shell(t_shell *data, int argc, char **argv, char **envp)
{
	if (argc > 1)
	{
		ft_putendl_fd("Run ./minishell without arguments", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	(void)argv;
	data->line = NULL;
	data->last_status = 0;
	data->lex_list = NULL;
	data->cmd_list = NULL;
	data->envp = NULL;
	data->env_list = set_env_vars(envp);
	if (!data->env_list)
		free_shell(data, EXIT_FAILURE);
}

/* Free all allocated memory relative to the last prompt line */
static void	cleanup_line(t_shell *data)
{
	if (data->line)
		free(data->line);
	data->line = NULL;
	if (data->envp)
		free_strings_array(data->envp);
	data->envp = NULL;
	if (data->lex_list)
		ft_lexlist_clear(&(data->lex_list));
	data->lex_list = NULL;
	if (data->cmd_list)
		ft_cmdlist_clear(&data->cmd_list);
	data->cmd_list = NULL;
}

/* Free all allocated memory, clear history and exit program */
void	free_shell(t_shell *data, int exit_status)
{
	cleanup_line(data);
	rl_clear_history();
	if (data->env_list)
		ft_envlist_clear(&(data->env_list));
	data->env_list = NULL;
	data = NULL;
	exit(exit_status);
}

/* Add line to history, validate quotes and pipes. Exit if EOF (Ctrl+D) */
int	validate_line(t_shell *shell_data)
{
	if (!shell_data->line)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		free_shell(shell_data, EXIT_SUCCESS);
	}
	if (*shell_data->line)
		add_history(shell_data->line);
	if (!pipes_and_quotes_validation(shell_data->line))
		return (0);
	return (1);
}

/* Call lexer, validate syntax and call parser.
Return `0` to restart loop if syntax validation fails or if empty line.
Exit program if list creation fails. */
int	parse_line(t_shell *shell_data)
{
	shell_data->lex_list = lexer(shell_data->line);
	if (!shell_data->lex_list)
		free_shell(shell_data, EXIT_FAILURE);
	if (shell_data->lex_list->type == TOK_EOF)
		return (0);
	if (!syntax_validation(shell_data->lex_list))
		return (0);
	shell_data->cmd_list = parser(shell_data->lex_list);
	if (!shell_data->cmd_list)
		free_shell(shell_data, EXIT_FAILURE);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell_data;

	init_shell(&shell_data, argc, argv, envp);
	while (1)
	{
		cleanup_line(&shell_data);
		g_heredoc_signal = 1;
		parent_signals();
		shell_data.line = readline("$ ");
		if (!validate_line(&shell_data))
			continue ;
		if (!expander(&shell_data.line, shell_data.env_list))
			free_shell(&shell_data, EXIT_FAILURE);
		if (!parse_line(&shell_data))
			continue ;
		execution(&shell_data);
	}
	return (0);
}
