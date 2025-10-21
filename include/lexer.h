/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:26:17 by danielji          #+#    #+#             */
/*   Updated: 2025/10/21 11:28:25 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

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
	struct s_lextoken	*prev;
}						t_lextoken;

t_lextoken	*lexer(char *str);
t_lextoken	*ft_new_operator_token(t_lex_type type, int *i);
t_lextoken	*ft_new_redir_token(t_lex_type type, char next_c, int *i);
t_lextoken	*ft_new_word_token(char *str, int start, int len);
t_lextoken	*ft_parse_quoted_word(char *str, int *i);
t_lextoken	*ft_parse_word(char *str, int *i);
int			is_in_set(char c, char *set);
void		ft_lexlist_insert(t_lextoken *prev, t_lextoken *new);
void		ft_lexlist_add(t_lextoken **lst, t_lextoken *new);
void		ft_lexnode_free(t_lextoken *node);
void		ft_lexlist_clear(t_lextoken **lst);

#endif
