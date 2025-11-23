/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:48:00 by danielji          #+#    #+#             */
/*   Updated: 2025/11/23 14:39:50 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **envp)
{
	int	i;
	int	len;
	char	*write_str;

	i = 0;
	len = 0;
	write_str = NULL;
	while (envp[i] != NULL)
	{
		write_str= ft_strjoin(envp[i++], "\n");
		if (!write_str)
		{
			perror ("echo failed in malloc");
			return (12);
		}
		len = ft_strlen(write_str);
		write(STDOUT_FILENO, write_str, len);
		free(write_str);
	}
//	ft_putendl_fd("env test", STDOUT_FILENO);
	return (0);
}
