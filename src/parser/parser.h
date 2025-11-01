/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:04:19 by danielji          #+#    #+#             */
/*   Updated: 2025/11/01 22:18:28 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_cmd
{
	char			**cmd;
	char			*path;
	struct s_cmd	*next;
	struct s_cmd	*prev;//ENRIQUE 1/11: Do we still need this?
}	t_cmd;

typedef struct s_parser_data
{
	int	*words_per_cmd;
	int	num_cmds;
	int	current_cmd;
}	t_parser_data;

void	print_cmd_list(t_cmd *list);
t_cmd	*parser(t_shell *data);
void	ft_cmdlist_insert(t_cmd *prev, t_cmd *new);
void	ft_cmdlist_add(t_cmd **lst, t_cmd *new);
void	ft_cmdnode_free(t_cmd *node);
void	ft_cmdlist_clear(t_cmd **lst);
t_cmd	*ft_new_cmdnode(void);
int		set_words_per_cmd(t_parser_data *data, t_lextoken *lex_list);
int		is_cmd_or_arg(t_lextoken *lex_node);

#endif
