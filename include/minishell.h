/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:18:26 by danielji          #+#    #+#             */
/*   Updated: 2025/10/12 17:25:15 by enrgil-p         ###   ########.fr       */
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

// Libft and our headers
# include "libft.h"
# include "expander.h"

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

// quote_validation
int	quote_validation(char *str);

// lexer
t_lextoken	*lexer(char *str);
//int			ft_ismetachar(char c);
int			is_in_set(char c, char *set);
t_lextoken	*ft_parse_quoted_word(char *str, int *i);
t_lextoken	*ft_parse_word(char *str, int *i);
void		ft_lexlist_add(t_lextoken **lst, t_lextoken *new);
void		ft_lexlist_insert(t_lextoken *prev, t_lextoken *new);
t_lextoken	*ft_new_token(t_lex_type type, int *i);
void		ft_lexnode_free(t_lextoken *node);
void		ft_lexlist_clear(t_lextoken **lst);
char		*get_variable_name(char *str);

#endif
