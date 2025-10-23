/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:04:19 by danielji          #+#    #+#             */
/*   Updated: 2025/10/23 10:04:25 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_cmd
{
	//char			**cmd;
	char			*cmd;
	char			*path;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

void	print_cmd_list(t_cmd *list);
t_cmd	*parser(t_lextoken *lex_list);
void	ft_cmdlist_insert(t_cmd *prev, t_cmd *new);
void	ft_cmdlist_add(t_cmd **lst, t_cmd *new);
void	ft_cmdnode_free(t_cmd *node);
void	ft_cmdlist_clear(t_cmd **lst);
t_cmd	*ft_new_cmdnode(void);

#endif
