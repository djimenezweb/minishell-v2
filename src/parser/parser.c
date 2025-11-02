/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:01:58 by danielji          #+#    #+#             */
/*   Updated: 2025/11/02 19:31:55 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	print_cmd_list(t_cmd *list)
{
	//debug
	int	i;
	int	j;

	i = 0;
	printf("Hello, here starts the problem if I try to access\n");//debug
	printf("Is list null?: %p\n", list);//debug
	while (list)
	{
		j = 0;
		printf("cmd_%d\n", i);//debug
		while (list->cmd[j])
		{
			if (j == 0)
				ft_printf("\n%s\n", list->cmd[j]);//debug
			else
				ft_printf("\t%s\n", list->cmd[j]);//debug
			++j;
		}
		list = list->next;
	}
	//All is debug, and debug is all
}

static int	malloc_cmd_and_args(t_cmd *node, t_parser_data *data)
{
	int	i;

	i = data->current_cmd;
	node->cmd = ft_calloc(data->words_per_cmd[i], sizeof(char *));
	if (!node->cmd)
		return (0);
	return (1);
}

static int	new_cmd(t_cmd *list, t_cmd **last, t_parser_data *data)
{
	t_cmd		*node;
	
	node = NULL;
	node = ft_new_cmdnode();
	if (!node || !malloc_cmd_and_args(node, data))
		return (0);
	ft_cmdlist_add(&list, node);
	*last = node;
	if (data->current_cmd < data->num_cmds)
		++data->current_cmd;//ENRIQUE 2/11: Be careful if we use this
				    //later. In that case, reset to 0 after all
	data->current_word = 0;
	return (1);
}

//static int	add_to_cmd(t_lextoken *lexer, t_cmd *node, t_parser_data *data)
static void	add_to_cmd(t_lextoken *lexer, t_cmd *node, t_parser_data *data)
{
	int	i;

	i = data->current_word;
	node->cmd[i] = lexer->value;//<-Option 1. Below, option 2
/*	node->cmd[i] = ft_strdup(lexer->value);
	if (!node->cmd[i])
		return (0);
	//Enrique 2/11: "Why ft_strdup here?" Because after whole parse and
	//	just before execution, lexer could be free. 
	//	If we do strdup here, this option is possible*/
	printf("add_to_cmd()--->current word stored is: %s\n", node->cmd[i]);//debug
	++data->current_word;/*
	return (1);*/
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
	t_cmd		*last_node;
	t_cmd		*cmd_list;
	t_lextoken	*current;
	t_parser_data	parser_data;

	last_node = NULL;
	cmd_list = NULL;
	if (!set_words_per_cmd(&parser_data, lex_list))
		return (NULL);
	current = lex_list;
	while (current)
	{
		if (current->type == TOK_EOF)
			break ;
		if ((!cmd_list || current->type == TOK_PIPE)
			&& (!new_cmd(cmd_list, &last_node, &parser_data)))
			return (ft_cmdlist_clear(&cmd_list), NULL);
		if (is_cmd_or_arg(current))
		{
			add_to_cmd(current, last_node, &parser_data);
			printf("parser()->word stored is: %s\n", last_node->cmd[parser_data.current_word - 1]);//debug
/*			if (!add_to_cmd(current, last_node, &parser_data))
				return (ft_cmdlist_clear(&cmd_list), NULL);*/
			//"Above is antoher option to execute this function."
			//	For more information, go to add_to_cmd() scope
			//We have to choose one of these, then remove the other
		}
		current = current->next;
	}
	print_cmd_list(cmd_list);
	return (cmd_list);//ENRIQUE 2/11: At this point, we should have 
			  //a list for every cmd and args.
			  //But when we try to open fds for redir?
}
