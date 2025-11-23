/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:47:08 by danielji          #+#    #+#             */
/*   Updated: 2025/11/23 14:53:15 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	ft_pwd(char **envp)
{
/* Todos los builtins devuelven 0 si han tenido éxito o un número distinto de
0 en caso de error.
Devuelven 2 para indicar uso incorrecto, opciones inválidas o que faltan
argumentos. */
	char	*working_directory;
	char	*write_str;
	int	i;
	int	pwd_len;

	working_directory = NULL;
	i = 0;
	pwd_len = 0;
	while (!working_directory && envp[i] != NULL)
		working_directory = ft_strnstr(envp[i++], "PWD=", 4);
	if (working_directory != NULL)
	{
		working_directory += 4;
		write_str = ft_strjoin(working_directory, "\n");
		if (!write_str)
		{
			perror ("echo failed in malloc");
			return (12);
		}
		pwd_len = ft_strlen(write_str);
		write(STDOUT_FILENO, write_str, pwd_len);
		free(write_str);
	}
//	ft_putendl_fd("pwd test", STDOUT_FILENO);
	return (0);
}
