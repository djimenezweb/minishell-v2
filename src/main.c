/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:18:33 by danielji          #+#    #+#             */
/*   Updated: 2025/09/30 10:25:24 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* FOR TEST PURPOSES ONLY */
static void	print_lex_list(t_token *list)
{
	t_token	*curr;

	curr = list;
	while (curr)
	{
		if (curr->type == TOK_WORD)
			ft_printf("WORD(%s)\n", curr->value);
		else if (curr->type == TOK_PIPE)
			ft_printf("PIPE\n");
		else if (curr->type == TOK_REDIR_IN)
			ft_printf("REDIR_IN\n");
		else if (curr->type == TOK_REDIR_OUT)
			ft_printf("REDIR_OUT\n");
		else if (curr->type == TOK_APPEND)
			ft_printf("APPEND\n");
		else if (curr->type == TOK_HEREDOC)
			ft_printf("HEREDOC\n");
		else if (curr->type == TOK_EOF)
			ft_printf("EOF\n");
		curr = curr->next;
	}
}

// Command example: cat << EOF | grep foo >> out.txt
int	main(void)
{
	char	*line;
	t_token	*token_list;

	line = readline("$ ");
	token_list = lexer(line);
	print_lex_list(token_list);
	free(line);
	ft_clear_toklist(&token_list);
	return (0);
}
