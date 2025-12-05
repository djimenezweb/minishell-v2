/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:04:19 by danielji          #+#    #+#             */
/*   Updated: 2025/12/05 09:33:28 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_cmd
{
	pid_t			pid;
	int				input;
	int				status;
	int				output;
	int				is_heredoc;
	int				is_forkable;
	char			*path;
	char			**cmd;
	char			**delimiters;
	struct s_shell	*shell;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_parser_data
{
	int	*words_per_cmd;
	int	num_cmds;
	int	current_cmd;
	int	current_word;
}	t_parser_data;

t_cmd	*parser(t_lextoken *lst);
void	ft_cmdlist_add(t_cmd **lst, t_cmd *new);
void	ft_cmdnode_free(t_cmd *node);
void	ft_cmdlist_clear(t_cmd **lst);
int		ft_cmdlist_size(t_cmd *lst);
t_cmd	*ft_new_cmdnode(void);
int		set_words_per_cmd(t_parser_data *data, t_lextoken *lex_list);
int		add_to_cmd(t_lextoken *lexer, t_cmd *node, t_parser_data *data);
int		is_cmd_or_arg(t_lextoken *lex_node);
void	assign_fd(t_lextoken *lst, t_cmd *node);
void	assign_hdoc(t_lextoken *lst, t_cmd *last_node);
int		is_infile(t_lextoken *lex_node);
int		is_outfile(t_lextoken *lex_node);
int		open_infile(char *path);
int		open_outfile(char *path, enum e_lex_type type);
char	**append(char **arr, char *str);

#endif
