/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:01:58 by danielji          #+#    #+#             */
/*   Updated: 2025/12/01 13:04:08 by danielji         ###   ########.fr       */
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

// TODO: On line `++data->current_cmd, Enrique commented:
// Be careful if we use this later. In that case, reset to 0 after all
static int	new_cmd(t_cmd **list, t_cmd **last, t_parser_data *data)
{
	t_cmd	*node;

	node = NULL;
	node = ft_new_cmdnode();
	if (!node || !malloc_cmd_and_args(node, data))
		return (0);
	ft_cmdlist_add(list, node);
	*last = node;
	if (data->current_cmd < data->num_cmds)
		++data->current_cmd;
	data->current_word = 0;
	return (1);
}

/* Parse a `t_lextoken` list into a `t_cmd` list
- Count processes and words.
- A process without command is a valid one (e.g. `ls | <infile | echo Hi`)
- Malloc process by process space to store (cmd || arg) in **cmd
- If a pipe is found, change to next process, create a new node and repeat */
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
		if (lst->type == TOK_WORD && lst->word_type == TOK_DELIMITER)
			assign_hdoc(lst, last_node);
		lst = lst->next;
	}
	free(parser_data.words_per_cmd);
	return (cmd_list);
}
