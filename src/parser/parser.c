/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:01:58 by danielji          #+#    #+#             */
/*   Updated: 2025/11/01 22:21:15 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	print_cmd_list(t_cmd *list)
{
	while (list)
	{
		ft_printf("COMMAND(%s)\n", list->cmd);
		list = list->next;
	}
}

/* Parse a `t_lextoken` list into a `t_cmd` list */
t_cmd	*parser(t_shell *data)
{
	t_cmd		*node;
	t_cmd		*cmd_list;
	t_lextoken	*current;
	t_parser_data	parser_data;

	node = NULL;
	cmd_list = NULL;
	if (!set_words_per_cmd(&parser_data, data->lex_list))
		//MALLOC ERROR
	current = data->lex_list;
	//"ENRIQUE is working here"
	//Purpose: malloc all the cmd groups 
	//	and later strdup every word or argument 
	//	inside the cmds arrays of strings 
	/*while (current)
	{
		if (current->type == TOK_EOF)
			break ;
		if (is_cmd_or_arg(current))
		{
			node = ft_new_cmdnode();
			if (!node)
				return (ft_cmdlist_clear(&cmd_list), NULL);
			node->cmd = current->value;
			ft_cmdlist_add(&cmd_list, node);
		}
		current = current->next;
	}*/
	return (cmd_list);
}
