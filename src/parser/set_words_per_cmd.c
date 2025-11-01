/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_words_per_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 20:03:04 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/11/01 22:23:40 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"//Include this in minishell.h

static int	count_processes(t_lextoken *lex_list)
{
	int	process_counter;

	process_counter = 1;
	while (lex_list->next)
	{
		if (lex_list->type == TOK_PIPE)
			++process_counter;
		lex_list = lex_list->next;
	}
	return (process_counter);
}

int	set_words_per_cmd(t_parser_data *data, t_lextoken *lex_list)
{
	int	i;

	data->current_cmd = 0;
	data->num_cmds = count_processes(lex_list);
	data->words_per_cmd = ft_calloc(data->num_cmds, sizeof(int));
	if (!(data->words_per_cmd))
		return (0);
	i = 0;
	while (lex_list->next)
	{
		if (lex_list->type == TOK_PIPE)
			++i;
		else if (is_cmd_or_arg(lex_list))
			data->words_per_cmd[i] += 1;
		lex_list = lex_list->next;
	}
	return (1);
}
