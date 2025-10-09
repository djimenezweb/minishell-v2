/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:49:37 by danielji          #+#    #+#             */
/*   Updated: 2025/10/09 17:11:34 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

/* Variable names are made up of uppercase and lowercase letters,
numbers, and `_`. All other characters are considered delimiters.

Bash Reference Manual:
- `name`: A `word` consisting solely of letters, numbers, and underscores, and
beginning with a letter or underscore. Names are used as shell variable and
function names. */
char	*get_variable_name(char *str)
{
	int		i;
	char	*var_name;

	i = 0;
	var_name = NULL;
	if (str[i] != '$')
		return (var_name);
	i++;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	var_name = ft_substr(str, 1, i - 1);
	return (var_name);
}

/* char	*get_variable_name(char *str)
{
	int		i;
	char	*var_name;

	i = 0;
	var_name = NULL;
	if (str[i] != '$')
		return (NULL);
	i++;
	if (str[i] == '{')
	{
		while (str[i] && str[i] != '}')
			i++;
		var_name = ft_substr(str, 2, i - 2);
	}
	else
	{
		while (str[i] && !is_delimiter(str[i]))
			i++;
		var_name = ft_substr(str, 1, i - 1);
	}
	return (var_name);
} */
