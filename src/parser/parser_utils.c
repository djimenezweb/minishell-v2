/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 21:52:06 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/11/04 13:56:39 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_cmd_or_arg(t_lextoken *lex_node)
{
	if (lex_node->type == TOK_WORD && (lex_node->word_type == TOK_COMMAND
			|| lex_node->word_type == TOK_ARGUMENT))
		return (1);
	return (0);
}

int	is_infile(t_lextoken *lex_node)
{
	if (lex_node->type == TOK_WORD && lex_node->word_type == TOK_INFILE)
		return (1);
	return (0);
}

int	is_outfile(t_lextoken *lex_node)
{
	if (lex_node->type == TOK_WORD
		&& (lex_node->word_type == TOK_OUTFILE_CREATE
			|| lex_node->word_type == TOK_OUTFILE_APPEND))
		return (1);
	return (0);
}
