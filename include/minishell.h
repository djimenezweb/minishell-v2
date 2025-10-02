/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:18:26 by danielji          #+#    #+#             */
/*   Updated: 2025/10/02 10:30:55 by danielji         ###   ########.fr       */
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

//#include <string.h>
//#include <ctype.h>

typedef enum e_lex_type
{
	TOK_WORD,
	TOK_PIPE,
	TOK_APPEND,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_HEREDOC,
	TOK_EOF
}	t_lex_type;

typedef struct s_lextoken
{
	t_lex_type			type;
	char				*value;
	struct s_lextoken	*next;
}						t_lextoken;

// lexer
t_lextoken	*lexer(char *str);
int			ft_ismetachar(char c);
void		ft_lexlist_add(t_lextoken **lst, t_lextoken *new);
void		ft_lexnode_free(t_lextoken *node);
void		ft_lexlist_clear(t_lextoken **lst);

#endif