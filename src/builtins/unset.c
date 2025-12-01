/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:47:30 by danielji          #+#    #+#             */
/*   Updated: 2025/12/01 10:36:00 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_env(t_env_var **list, char *name)
{
	t_env_var	*node;

	node = find_env_var(*list, name);
	if (!node)
		return ;
	ft_env_remove(list, node);
}

/* Remove env nodes from the env list. `$?` env can't be deleted. */
int	ft_unset(t_cmd *cmd)
{
	int	i;

	if (!cmd->cmd[1])
		return (2);
	i = 1;
	while (cmd->cmd[i])
	{
		if (cmd->cmd[i][0] != '?')
			unset_env(&(cmd->shell->env_list), cmd->cmd[i]);
		i++;
	}
	return (0);
}
