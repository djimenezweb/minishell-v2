/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer-word-types.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:58:50 by danielji          #+#    #+#             */
/*   Updated: 2025/10/23 11:58:50 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_word_types(t_lextoken *lst)
{
	while (lst)
	{
		if (lst->type == TOK_EOF)
			break ;
		if (lst->type == TOK_WORD)
		{
			if (!lst->prev)
				lst->word_type = TOK_COMMAND;
			else if (lst->prev->type == TOK_REDIR_OUT || lst->prev->type == TOK_APPEND)
				lst->word_type = TOK_OUTFILE;
			else if (lst->prev->type == TOK_REDIR_IN)
				lst->word_type = TOK_INFILE;
			else if (lst->prev->type == TOK_HEREDOC)
				lst->word_type = TOK_DELIMITER;
			else if (lst->prev->word_type == TOK_COMMAND || lst->prev->word_type == TOK_ARGUMENT)
				lst->word_type = TOK_ARGUMENT;
			else
				lst->word_type = TOK_COMMAND;
		}
		lst = lst->next;
	}
}
