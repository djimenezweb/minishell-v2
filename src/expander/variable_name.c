/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:49:37 by danielji          #+#    #+#             */
/*   Updated: 2025/10/21 20:05:18 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Variable names are made up of uppercase and lowercase letters,
numbers, and `_`. All other characters are considered delimiters.*/
char	*get_variable_name(char *str)
{
	int		i;
	char	*var_name;

	i = 0;
	var_name = NULL;
	if (str[i] != DOLLAR)
		return (NULL);
	i++;
	if (str[i] == '?')
		return (ft_strdup("?"));
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	var_name = ft_substr(str, 1, i - 1);
	if (!var_name)
		return (NULL);
	return (var_name);
}
