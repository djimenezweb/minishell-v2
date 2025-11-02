/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:01:58 by danielji          #+#    #+#             */
/*   Updated: 2025/11/02 15:39:32 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	print_cmd_list(t_cmd *list)
{
	//debug
	while (list)
	{
		ft_printf("COMMAND(%s)\n", list->cmd);
		list = list->next;
	}
}

static int	malloc_cmd_and_args(/*Something*/)
{
	//Still working here
}

static int	new_cmd(t_cmd *list, t_cmd *last, t_parser_data *data)
{
	t_cmd		*node;
	
	node = NULL;
	node = ft_new_cmdnode();
	if (!node || malloc_cmd_and_args(/*Somehting*/))
		return (0);
	ft_cmdlist_add(&cmd_list, node);
	if (data->current_cmd < data->num_cmds)
		++data->current_cmd;//ENRIQUE 2/11: Be careful if we use this
				    //later. In that case, reset to 0 after all
	data->current_word = 0;
	return (1);
}

/*static int	add_to_cmd(t_lextoken *current, t_cmd *node,
 * 		t_parser_data *data)*/
static void	add_to_cmd(t_lextoken *current, t_cmd *node,
		t_parser_data *data)
{
	int	i;

	i = data->current_word;
	node->cmd[i] = current->value;
	//node->cmd[i] = ft_strdup(current->value);
	//if (!node->cmd[i])
	//	return (0);
	++data->current_word;
}

/* Parse a `t_lextoken` list into a `t_cmd` list */
t_cmd	*parser(t_shell *data)
{
	t_cmd		*last_node;
	t_cmd		*cmd_list;
	t_lextoken	*current;
	t_parser_data	parser_data;

	last_node = NULL;
	cmd_list = NULL;
	if (!set_words_per_cmd(&parser_data, data->lex_list))
		return (NULL);
	current = data->lex_list;
	while (current)
	{
		if (current->type == TOK_EOF)
			break ;
		else if ((!cmd_list || current->type == TOK_PIPE)
			&& (!new_cmd(cmd_list, last_node, &parser_data)))
			return (ft_cmdlist_clear(&cmd_list), NULL);
		else if (is_cmd_or_arg(current))
		{
			add_to_cmd(current, last_node, &parser_data);
		/*	if(!add_to_cmd(current, last_node, &parser_data))
				return (ft_cmdlist_clear(&cmd_list), NULL);*/
			//Above is antoher option to execute this function.
			//We have to choose one of these, then remove the other
		}
		current = current->next;
	}
	return (cmd_list);//ENRIQUE 2/11: At this point, we should have 
			  //a list for every cmd and args.
			  //But when we try to open fds for redir?
}
