/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:47:08 by danielji          #+#    #+#             */
/*   Updated: 2025/11/24 23:15:18 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*working_directory;
	char	*write_str;
	int		pwd_len;

	working_directory = getcwd(NULL, 0);
	if (!working_directory)
	{
		perror("getcwd failed");
		return (1);
	}
	write_str = ft_strjoin(working_directory, "\n");
	if (!write_str)
	{
		perror ("echo failed in malloc");
		return (12);
	}
	pwd_len = ft_strlen(write_str);
	write(STDOUT_FILENO, write_str, pwd_len);
	free(write_str);
	free(working_directory);
	return (0);
}
