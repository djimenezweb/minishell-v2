/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:01:58 by danielji          #+#    #+#             */
/*   Updated: 2025/11/10 13:05:39 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_to_cmd(t_lextoken *lexer, t_cmd *node, t_parser_data *data)
{
	int	i;

	i = data->current_word;
	//node->cmd[i] = lexer->value;//<-Option 1. Below, option 2
	node->cmd[i] = ft_strdup(lexer->value);
	if (!node->cmd[i])
		return (0);
	//Enrique 2/11: "Why ft_strdup here?" Because after whole parse and
	//	just before execution, lexer could be free. 
	//	If we do strdup here, this option is possible*/
	++data->current_word;
	return (1);
}
