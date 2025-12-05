/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:26:17 by danielji          #+#    #+#             */
/*   Updated: 2025/12/05 09:29:58 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define PIPE_FOUND 1
# define NOT_PIPE 0
# define CMD_FOUND 1
# define NOT_CMD 0

typedef enum e_lex_type
{
	TOK_NULL,
	TOK_WORD,
	TOK_PIPE,
	TOK_APPEND,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_HEREDOC,
	TOK_COMMAND,
	TOK_ARGUMENT,
	TOK_INFILE,
	TOK_OUTFILE_APPEND,
	TOK_OUTFILE_CREATE,
	TOK_DELIMITER,
	TOK_EOF
}	t_lex_type;

typedef struct s_lextoken
{
	t_lex_type			type;
	t_lex_type			word_type;
	char				*value;
	struct s_lextoken	*next;
	struct s_lextoken	*prev;
}						t_lextoken;

t_lextoken	*ft_new_lex_token(t_lex_type type);
t_lextoken	*ft_new_operator_token(char c, char next_c, int *i);
t_lextoken	*ft_new_word_token(char *str, int *i);
void		skip_spaces(char *str, int *i);
t_lextoken	*lexer(char *str);
void		ft_lexlist_add(t_lextoken **lst, t_lextoken *new);
void		ft_lexnode_free(t_lextoken *node);
void		ft_lexlist_clear(t_lextoken **lst);
int			is_in_set(char c, char *set);
char		*parse_word(char *str, int *i);
void		parse_word_types(t_lextoken *lst);
void		remove_quotes(char *str);

#endif
