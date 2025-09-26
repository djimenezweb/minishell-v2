/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:18:33 by danielji          #+#    #+#             */
/*   Updated: 2025/09/26 13:34:15 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

// Command example: cat << EOF | grep foo >> out.txt
int main()
{
	char	*line;
	t_token	*token_list;

	line = readline("$ ");
	token_list = tokenize(line);

	// PRINT LIST START
	t_token	*current = token_list;
	while (current->next)
	{
		switch (current->type) {
			case TOK_WORD: ft_printf("WORD(%s)\n", current->value); break;
			case TOK_PIPE: ft_printf("PIPE\n"); break;
			case TOK_REDIR_IN: ft_printf("REDIR_IN\n"); break;
			case TOK_REDIR_OUT: ft_printf("REDIR_OUT\n"); break;
			case TOK_APPEND: ft_printf("APPEND\n"); break;
			case TOK_HEREDOC: ft_printf("HEREDOC\n"); break;
			case TOK_EOF: ft_printf("EOF\n"); break;
		}
		current = current->next;
	}
	// PRINT LIST END

	free(line);
	ft_clear_toklist(&token_list);
	return (0);
}
