/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:48:00 by danielji          #+#    #+#             */
/*   Updated: 2025/11/25 19:45:50 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **cmd, char **envp)
{
	int		i;
	int		len;
	char	*write_str;

	i = 0;
	len = 0;
	write_str = NULL;
	if (cmd[1])
	{
		ft_putendl_fd("env: expected no arguments", 2);
		return (2);
	}
	while (envp[i] != NULL)
	{
		write_str = ft_strjoin(envp[i++], "\n");
		if (!write_str)
		{
			perror ("echo failed in malloc");
			return (12);
		}
		len = ft_strlen(write_str);
		write(STDOUT_FILENO, write_str, len);
		free(write_str);
	}
	return (0);
}
