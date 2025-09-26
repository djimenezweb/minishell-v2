/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:18:26 by danielji          #+#    #+#             */
/*   Updated: 2025/09/26 11:55:29 by danielji         ###   ########.fr       */
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

typedef enum e_token_type {
	TOK_WORD,
	TOK_PIPE,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_REDIR_OUT_APPEND,
	TOK_HEREDOC,
	TOK_EOF
} t_token_type;

typedef struct s_token {
	t_token_type	type;
	char			*value;   // only used for TOK_WORD
	struct s_token	*next;
}					t_token;

/* typedef struct s_token_array {
	t_token		*tokens;
	size_t		count;
}				t_token_array; */

// parser
char	**split_by_space(char *line);
char	**split_by_metacharacter(char **arr);
void	free_array_n(char **arr, int n);

// parser-tok
//void	free_tokens(t_token_array *arr);
t_token	*tokenize(char *str);
t_token	*ft_add_new_token(t_token_type type, char *string, int start, size_t len);
int		ft_lstsize(t_token *lst);
t_token	*ft_lstlast(t_token *lst);
void	ft_lstadd_back(t_token **lst, t_token *new);
void	ft_free_node(t_token *node);
void	ft_clear_list(t_token **lst);

#endif