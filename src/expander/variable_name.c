/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:49:37 by danielji          #+#    #+#             */
/*   Updated: 2025/10/09 17:11:34 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/* Returns the value of the given variable name, including
the special parameter `$?`, or `NULL` if it doesn't exist.
TO DO: 
- `getenv` should be replaced by a custom function
- `$?` should return the status of the last command,
it currently returns a hardcoded value */
char	*get_variable_value(char *name)
{
	char	*value;

	if (name[0] == '?')
		return ("123");
	value = getenv(name);
	return (value);
}
