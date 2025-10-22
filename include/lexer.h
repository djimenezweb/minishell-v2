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

t_lextoken	*ft_new_lex_token(t_lex_type type);
t_lextoken	*ft_new_operator_token(char c, char next_c, int *i);
t_lextoken	*ft_new_word_token(char *str, int *i);
t_lextoken	*lexer(char *str);
void		ft_lexlist_insert(t_lextoken *prev, t_lextoken *new);
void		ft_lexlist_add(t_lextoken **lst, t_lextoken *new);
void		ft_lexnode_free(t_lextoken *node);
void		ft_lexlist_clear(t_lextoken **lst);
int			is_in_set(char c, char *set);
char		*parse_word(char *str, int *i);

#endif
