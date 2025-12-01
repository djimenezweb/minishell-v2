/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:47:08 by danielji          #+#    #+#             */
/*   Updated: 2025/12/01 11:00:29 by danielji         ###   ########.fr       */
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
		perror("minishell: getcwd");
		return (1);
	}
	write_str = ft_strjoin(working_directory, "\n");
	if (!write_str)
	{
		ft_dprintf(STDERR_FILENO, "minishell: malloc: %s", strerror(ENOMEM));
		return (1);
	}
	pwd_len = ft_strlen(write_str);
	write(STDOUT_FILENO, write_str, pwd_len);
	free(write_str);
	free(working_directory);
	return (0);
}
