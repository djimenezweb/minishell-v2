/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upadte_quote_flag.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 22:45:15 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/10/18 23:11:45 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	found_single_quote(int c)
{
	if (c == SINGLE_QUOTE)
		return (SINGLE_QUOTE);
	return (0);
}

static int	found_double_quote(int c)
{
	if (c == DOUBLE_QUOTE)
		return (DOUBLE_QUOTE);
	return (0);
}

int	update_quote_flag(int quote_flag, int char_found)
{
	if (!quote_flag)
		return (found_single_quote(char_found)
			|| found_double_quote(char_found));
	if (char_found != quote_flag)
		return (quote_flag);
	return (0);
}
