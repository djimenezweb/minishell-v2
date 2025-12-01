/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:51:03 by danielji          #+#    #+#             */
/*   Updated: 2025/12/01 19:22:02 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_syntax_error(char *str)
{
	ft_dprintf(STDERR_FILENO, "minishell: syntax error near `%s`\n", str);
}

/* Return `1` if list passes syntax validation, return `0` if it doesn't. */
int	syntax_validation(t_lextoken *node)
{
	while (node)
	{
		if (node->type == TOK_PIPE && !is_valid_pipe(node))
			return (0);
		if (node->type == TOK_REDIR_OUT && !is_valid_redout(node))
			return (0);
		if (node->type == TOK_APPEND && !is_valid_append(node))
			return (0);
		if (node->type == TOK_REDIR_IN && !is_valid_redin(node))
			return (0);
		if (node->type == TOK_HEREDOC && !is_valid_heredoc(node))
			return (0);
		node = node->next;
	}
	return (1);
}
