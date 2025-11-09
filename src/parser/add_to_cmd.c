/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:01:58 by danielji          #+#    #+#             */
/*   Updated: 2025/11/05 17:26:48 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_cmd(t_lextoken *lexer, t_cmd *node, t_parser_data *data)
{
	int	i;

	i = data->current_word;
	node->cmd[i] = lexer->value;
	++data->current_word;
}
