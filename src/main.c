/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:18:33 by danielji          #+#    #+#             */
/*   Updated: 2025/12/05 14:17:29 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_heredoc_signal = NO_SIGNAL;

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

static int	ft_is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (!str[i])
		return (1);
	return (0);
}

/* Add line to history, validate quotes and pipes. Exit if EOF (Ctrl+D) */
static int	validate_line(t_shell *shell_data)
{
	if (!shell_data->line)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		free_shell(shell_data, EXIT_SUCCESS);
	}
	if (ft_is_empty(shell_data->line))
		return (0);
	add_history(shell_data->line);
	if (!pipes_and_quotes_validation(shell_data->line))
	{
		set_last_exit_status(shell_data->env_list, 2);
		return (0);
	}
	return (1);
}

/* Call lexer, validate syntax and call parser.
Return `0` to restart loop if syntax validation fails or if empty line.
Exit program if list creation fails. */
static int	parse_line(t_shell *shell_data)
{
	shell_data->lex_list = lexer(shell_data->line);
	if (!shell_data->lex_list)
		free_shell(shell_data, EXIT_FAILURE);
	if (shell_data->lex_list->type == TOK_EOF)
		return (0);
	if (!syntax_validation(shell_data->lex_list))
	{
		set_last_exit_status(shell_data->env_list, 2);
		return (0);
	}
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
		g_heredoc_signal = NO_SIGNAL;
		parent_signals();
		shell_data.line = readline("shed$ ");
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
