/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_token_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:05:00 by danielji          #+#    #+#             */
/*   Updated: 2025/11/27 18:07:13 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_tok_last(t_lextoken *node)
{
	if (node->next == NULL || node->next->type == TOK_EOF)
		return (1);
	return (0);
}

int	is_tok_first(t_lextoken *node)
{
	if (node->prev == NULL)
		return (1);
	return (0);
}
