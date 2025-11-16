/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:34:13 by danielji          #+#    #+#             */
/*   Updated: 2025/11/10 12:15:46 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Return an array of strings from a list of environment variables */
char	**get_envp(t_env_var *env_lst)
{
	int		i;
	int		size;
	char	*temp;
	char	**arr;

	i = 0;
	size = ft_envlist_size(env_lst);
	arr = malloc(sizeof(char *) * (size + 1));
	if (!arr)
		return (NULL);
	while (env_lst && i < size)
	{
		temp = ft_strjoin(env_lst->name, "=");
		if (env_lst->value)
			arr[i] = ft_strjoin(temp, env_lst->value);
		else
			arr[i] = ft_strjoin(temp, "");
		free(temp);
		env_lst = env_lst->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
