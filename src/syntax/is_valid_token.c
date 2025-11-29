/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 11:35:29 by danielji          #+#    #+#             */
/*   Updated: 2025/11/29 20:10:58 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* - is last? WRONG!
- is first? OK
- `|<<` OK ???
- `><<` WRONG!
- `>><<` WRONG!
- `<<<` OK ???
- `<<<<` WRONG!
*/
int	is_valid_heredoc(t_lextoken *node)
{
	if (is_tok_last(node))
		return (print_syntax_error("<<"), 0);
	if (node->prev != NULL && (node->prev->type == TOK_REDIR_OUT
			|| node->prev->type == TOK_APPEND
			|| node->prev->type == TOK_HEREDOC))
		return (print_syntax_error("<<"), 0);
	return (1);
}

/* - is last? WRONG!
- is first? OK
- `|<` OK ???
- `><` WRONG!
- `>><` WRONG!
- `<<` WRONG!
- `<<<` WRONG!
*/
int	is_valid_redin(t_lextoken *node)
{
	if (is_tok_last(node))
		return (print_syntax_error("<"), 0);
	if (node->prev != NULL && (node->prev->type == TOK_REDIR_OUT
			|| node->prev->type == TOK_APPEND
			|| node->prev->type == TOK_REDIR_IN
			|| node->prev->type == TOK_HEREDOC))
		return (print_syntax_error("<"), 0);
	return (1);
}

/* - is last? WRONG!
- is first? OK
- `|>>` OK
- `>>>` WRONG!
- `>>>>` WRONG!
- `<>>` WRONG!
- `<<>>` WRONG!
*/
int	is_valid_append(t_lextoken *node)
{
	if (is_tok_last(node))
		return (print_syntax_error(">>"), 0);
	if (node->prev != NULL && (node->prev->type == TOK_REDIR_OUT
			|| node->prev->type == TOK_APPEND
			|| node->prev->type == TOK_REDIR_IN
			|| node->prev->type == TOK_HEREDOC))
		return (print_syntax_error(">>"), 0);
	return (1);
}

/* - is last? WRONG!
- is first? OK
- `|>` OK
- `>>` WRONG!
- `>>>` WRONG!
- `<>` OK ???
- `<<>` WRONG!
*/
int	is_valid_redout(t_lextoken *node)
{
	if (is_tok_last(node))
		return (print_syntax_error(">"), 0);
	if (node->prev != NULL && (node->prev->type == TOK_REDIR_OUT
			|| node->prev->type == TOK_APPEND
			|| node->prev->type == TOK_HEREDOC))
		return (print_syntax_error(">"), 0);
	return (1);
}

/* - is last? WRONG!
- is first? WRONG!
- `||` WRONG!
- `>|` OK
- `>>|` WRONG!
- `<|` WRONG!
- `<<|` WRONG!
*/
int	is_valid_pipe(t_lextoken *node)
{
	if (is_tok_first(node) || is_tok_last(node))
		return (print_syntax_error("|"), 0);
	if (node->prev->type == TOK_APPEND
		|| node->prev->type == TOK_REDIR_IN
		|| node->prev->type == TOK_HEREDOC)
		return (print_syntax_error("|"), 0);
	return (1);
}
