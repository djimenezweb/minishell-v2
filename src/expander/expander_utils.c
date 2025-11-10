/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 22:45:15 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/11/10 18:50:32 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_quote_flag(t_expansion_data *expansion, int char_found)
{
	if (!expansion->env_quoted
		&& (char_found == SINGLE_QUOTE || char_found == DOUBLE_QUOTE))
		expansion->env_quoted = char_found;
	else if (expansion->env_quoted == char_found)
		expansion->env_quoted = 0;
}

int	expand_has_some_quote(char *expanded)
{
	if (ft_strchr(expanded, DOUBLE_QUOTE)
		|| ft_strchr(expanded, SINGLE_QUOTE))
		return (1);
	return (0);
}
