/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:01:58 by danielji          #+#    #+#             */
/*   Updated: 2025/11/10 13:06:25 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	node->pid = -1;
	ft_cmdlist_add(list, node);
	*last = node;
	if (data->current_cmd < data->num_cmds)
		++data->current_cmd;//ENRIQUE 2/11: Be careful if we use this
				    //later. In that case, reset to 0 after all
	data->current_word = 0;
	return (1);
}

/* Parse a `t_lextoken` list into a `t_cmd` list
1) Count process by pipes, and counts how many words from `cmd` and `args`
   have anyone. A process could have no cmd, and could be correct.
   See the case: ls | <infile | echo "Hi"
2) Malloc process by process space to store (cmd || arg) in **cmd
3) If we find a pipe, we change to next process, creating a new node
   and repeating the process

"Above is antoher option to execute this function."
For more information, go to add_to_cmd() scope
We have to choose one of these, then remove the other */
t_cmd	*parser(t_lextoken *lst)
{
	t_cmd			*last_node;
	t_cmd			*cmd_list;
	t_parser_data	parser_data;

	last_node = NULL;
	cmd_list = NULL;
	if (!set_words_per_cmd(&parser_data, lst))
		return (NULL);
	while (lst && lst->type != TOK_EOF)
	{
		if ((!cmd_list || lst->type == TOK_PIPE)
			&& (!new_cmd(&cmd_list, &last_node, &parser_data)))
			return (ft_cmdlist_clear(&cmd_list),
				free(parser_data.words_per_cmd), NULL);
		if (is_cmd_or_arg(lst) && !add_to_cmd(lst, last_node, &parser_data))
			return (ft_cmdlist_clear(&cmd_list),
				free(parser_data.words_per_cmd), NULL);
		if (is_infile(lst) || is_outfile(lst))
			assign_fd(lst, last_node);
		lst = lst->next;
	}
	free(parser_data.words_per_cmd);
	//! print_cmd_list(cmd_list); //debug
	return (cmd_list);
}
