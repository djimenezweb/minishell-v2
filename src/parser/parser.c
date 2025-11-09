/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:01:58 by danielji          #+#    #+#             */
/*   Updated: 2025/11/05 17:51:50 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_list(t_cmd *list)
{
	printf("-- START COMMAND LIST --\n");
	while (list)
	{
		printf("Command: %s\n", list->cmd[0]);
		printf("Path:    %s\n", list->path);
		printf("Input:   %i\n", list->input);
		printf("Output:  %i\n", list->output);
		list = list->next;
	}
	printf("-- END COMMAND LIST --\n");
}

/* For debug purposes only */
/* void	print_cmd_list(t_cmd *list)
{
	int	i;
	int	j;

	i = 0;
	while (list)
	{
		j = 0;
		ft_printf("\tcmd_%d\n", i++);
		while (list->cmd[j])
		{
			ft_printf("arg_%d--->%s\n", j, list->cmd[j]);
			++j;
		}
		list = list->next;
	}
} */

static int	malloc_cmd_and_args(t_cmd *node, t_parser_data *data)
{
	int	i;

	i = data->current_cmd;
	node->cmd = ft_calloc(data->words_per_cmd[i] + 1, sizeof(char *));
	if (!node->cmd)
		return (0);
	return (1);
}

static int	new_cmd(t_cmd **list, t_cmd **last, t_parser_data *data)
{
	t_cmd	*node;

	node = NULL;
	node = ft_new_cmdnode();
	if (!node || !malloc_cmd_and_args(node, data))
		return (0);
	node->path = NULL;
	node->input = STDIN_FILENO;
	node->output = STDOUT_FILENO;
	ft_cmdlist_add(list, node);
	*last = node;
	if (data->current_cmd < data->num_cmds)
		++data->current_cmd;//ENRIQUE 2/11: Be careful if we use this
				    //later. In that case, reset to 0 after all
	data->current_word = 0;
	return (1);
}

/* Parse a `t_lextoken` list into a `t_cmd` list */
//
/*	1) Count process by pipes, and counts how many words fro cmd and args 
 *		have anyone. A process could have no cmd, and could be correct.
 *		See the case: ls | <infile | echo "Hi"
 *	2) Malloc process by process space to store (cmd || arg) in **cmd
 *	3) If we find a pipe, we change to next process, creating a new node
 *	and repeating the process*/
t_cmd	*parser(t_lextoken *lex_list)
{
	t_cmd			*last_node;
	t_cmd			*cmd_list;
	t_lextoken		*current;
	t_parser_data	parser_data;

	last_node = NULL;
	cmd_list = NULL;
	if (!set_words_per_cmd(&parser_data, lex_list))
		return (NULL);
	current = lex_list;
	while (current && current->type != TOK_EOF)
	{
		if ((!cmd_list || current->type == TOK_PIPE)
			&& (!new_cmd(&cmd_list, &last_node, &parser_data)))
			return (ft_cmdlist_clear(&cmd_list),
				free(parser_data.words_per_cmd), NULL);
		if (is_cmd_or_arg(current))
			add_to_cmd(current, last_node, &parser_data);
		if (is_infile(current))
		{
			if (last_node->input != STDIN_FILENO)
				close(last_node->input);
				//Protect in case of error
			last_node->input = open_file(current->value, current->word_type);
		}
		if (is_outfile(current))
		{
			if (last_node->output != STDOUT_FILENO)
				close(last_node->output);
				//Protect in case of error
			last_node->output = open_file(current->value, current->word_type);
		}
		current = current->next;
	}
	free(parser_data.words_per_cmd);
	print_cmd_list(cmd_list); //debug
	return (cmd_list);
}
