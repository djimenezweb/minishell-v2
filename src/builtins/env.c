/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:48:00 by danielji          #+#    #+#             */
/*   Updated: 2025/11/29 19:15:32 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **cmd, char **envp, int call_from_export)
{
	int		i;

	i = 0;
	if (cmd[1])
	{
		ft_putendl_fd("env: expected no arguments", 2);
		return (2);
	}
	while (envp[i] != NULL)
	{
		if (envp[i][0] != '?' && *(ft_strchr(envp[i], '=') + 1) != '\0')
			ft_putendl_fd(envp[i], STDOUT_FILENO);
		else if (call_from_export && envp[i][0] != '?')
			ft_putendl_fd(envp[i], STDOUT_FILENO);
		++i;
	}
	return (0);
}
