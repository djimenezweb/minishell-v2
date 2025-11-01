/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 21:52:06 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/11/01 21:59:14 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	is_cmd_or_arg(t_lextoken *lex_node)
{
	if (lex_node->type == TOK_WORD && (lex_node->word_type == TOK_COMMAND
			|| lex_node->word_type == TOK_ARGUMENT))
		return (1);
	return (0);

}
