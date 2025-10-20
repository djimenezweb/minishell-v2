/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upadte_quote_flag.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 22:45:15 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/10/19 20:23:05 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_quote_flag(int quote_flag, int char_found)
{
	if (!quote_flag && (char_found == SINGLE_QUOTE
			|| char_found == DOUBLE_QUOTE))
		return (char_found);
	if (char_found != quote_flag)
		return (quote_flag);
	return (0);
}
