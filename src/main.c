/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:18:33 by danielji          #+#    #+#             */
/*   Updated: 2025/09/26 11:54:19 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

int main()
{
	char	*line;
	t_token	*token_list;

	line = readline("$ ");
	token_list = tokenize(line);
	//char *cmd = "cat << EOF | grep foo >> out.txt";
	//t_token_array tokens = tokenize(cmd);

/* 	for (size_t i = 0; i < tokens.count; i++) {
		t_token *t = &tokens.tokens[i];
		switch (t->type) {
			case TOK_WORD: ft_printf("WORD(%s)\n", t->value); break;
			case TOK_PIPE: ft_printf("PIPE\n"); break;
			case TOK_REDIR_IN: ft_printf("REDIR_IN\n"); break;
			case TOK_REDIR_OUT: ft_printf("REDIR_OUT\n"); break;
			case TOK_REDIR_OUT_APPEND: ft_printf("REDIR_OUT_APPEND\n"); break;
			case TOK_HEREDOC: ft_printf("HEREDOC\n"); break;
			case TOK_EOF: ft_printf("EOF\n"); break;
		}
	} */
	free(line);
	ft_clear_list(&token_list);
	//free_tokens(&tokens);
	return (0);
}
