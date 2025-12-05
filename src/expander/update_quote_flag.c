/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 22:45:15 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/11/12 19:38:33 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_quote_flag(t_expansion_data *expansion, int char_found)
{
	if (!expansion->env_quoted && is_quote(char_found))
		expansion->env_quoted = char_found;
	else if (expansion->env_quoted == char_found)
		expansion->env_quoted = 0;
}
