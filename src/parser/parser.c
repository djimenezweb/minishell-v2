/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:01:58 by danielji          #+#    #+#             */
/*   Updated: 2025/11/01 21:57:38 by enrgil-p         ###   ########.fr       */
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
	int		*words_per_cmd;
//	int		i;

	node = NULL;
	cmd_list = NULL;
	words_per_cmd = NULL;
	if (!set_words_per_cmd(&words_per_cmd, data->lex_list))
		//MALLOC ERROR
	current = data->lex_list;
/*	while (current)
	{
		if (current->type == TOK_EOF)
			break ;
		if (current->type == TOK_WORD)
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
