/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:18:26 by danielji          #+#    #+#             */
/*   Updated: 2025/09/30 11:16:59 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SPACE 32
# define DOUBLE_QUOTE 34
# define DOLLAR 36
# define SINGLE_QUOTE 39
# define LESS 60
# define GREATER 62
# define BACKSLASH 92
# define PIPE 124
# define TILDE 126

// Libft
# include "libft.h"

// malloc, free
# include <stdlib.h>

// readline, printf
# include <stdio.h>

// readline
# include <readline/readline.h>
# include <readline/history.h>

#include <string.h>
#include <ctype.h>

typedef enum e_token_type {
	TOK_WORD,
	TOK_PIPE,
	TOK_APPEND,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_HEREDOC,
	TOK_EOF
} t_token_type;

typedef struct s_token {
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

// lexer
t_token	*lexer(char *str);
int		ft_ismetachar(char c);
int		ft_toklstsize(t_token *lst);
void	ft_toklstadd(t_token **lst, t_token *new);
void	ft_free_node(t_token *node);
void	ft_clear_toklist(t_token **lst);

#endif