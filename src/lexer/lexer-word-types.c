/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer-word-types.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:58:50 by danielji          #+#    #+#             */
/*   Updated: 2025/11/16 16:29:40 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_command_status(int *cmd_status, int pipe_status)
{
	if (*cmd_status == NOT_CMD && pipe_status == NOT_PIPE)
		*cmd_status = CMD_FOUND;
	if (*cmd_status == CMD_FOUND && pipe_status == PIPE_FOUND)
		*cmd_status = NOT_CMD;
}

static void	define_word(t_lextoken *lst, int *cmd_found)
{
	if (!lst->prev)
	{
		lst->word_type = TOK_COMMAND;
		update_command_status(cmd_found, NOT_PIPE);
	}
	else if (lst->prev->type == TOK_REDIR_OUT)
		lst->word_type = TOK_OUTFILE_CREATE;
	else if (lst->prev->type == TOK_APPEND)
		lst->word_type = TOK_OUTFILE_APPEND;
	else if (lst->prev->type == TOK_REDIR_IN)
		lst->word_type = TOK_INFILE;
	else if (lst->prev->type == TOK_HEREDOC)
		lst->word_type = TOK_DELIMITER;
	else if (*cmd_found == CMD_FOUND)
		lst->word_type = TOK_ARGUMENT;
	else if (*cmd_found == NOT_CMD)
	{
		lst->word_type = TOK_COMMAND;
		update_command_status(cmd_found, NOT_PIPE);
	}
}

void	parse_word_types(t_lextoken *lst)
{
	int	cmd_found;

	cmd_found = NOT_CMD;
	while (lst)
	{
		if (lst->type == TOK_EOF)
			break ;
		if (lst->type == TOK_PIPE)
			update_command_status(&cmd_found, PIPE_FOUND);
		if (lst->type == TOK_WORD)
		{
			define_word(lst, &cmd_found);
			if (lst->word_type != TOK_DELIMITER && ft_strchr(lst->value, DOUBLE_QUOTE) != NULL)
				remove_quotes(lst->value);
			quote_chars_in_expanded_vars(&lst->value, RESTORE);
		}
		lst = lst->next;
	}
}
