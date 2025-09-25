/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:18:26 by danielji          #+#    #+#             */
/*   Updated: 2025/09/25 20:19:25 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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

// readline
# include <stdio.h>

// readline
# include <readline/readline.h>
# include <readline/history.h>

#include <string.h>
#include <ctype.h>

typedef enum {
	TOK_WORD,
	TOK_PIPE,
	TOK_REDIRECT_IN,         // <
	TOK_REDIRECT_OUT,        // >
	TOK_REDIRECT_OUT_APPEND, // >>
	TOK_HEREDOC,             // <<
	TOK_EOF
} TokenType;

typedef struct s_token {
	TokenType	type;
	char		*value;   // only used for TOK_WORD
}				t_token;

typedef struct s_token_array {
	t_token		*tokens;
	size_t		count;
}				t_token_array;

// parser
char	**split_by_space(char *line);
char	**split_by_metacharacter(char **arr);
void	free_array_n(char **arr, int n);

// parser-tok
void			free_tokens(t_token_array *arr);
t_token_array	tokenize(char *input);

#endif