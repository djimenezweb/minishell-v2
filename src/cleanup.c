/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:46:57 by danielji          #+#    #+#             */
/*   Updated: 2025/12/01 10:47:30 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Free all allocated memory relative to the last prompt line */
void	cleanup_line(t_shell *data)
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
