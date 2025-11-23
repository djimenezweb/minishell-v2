/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:48:00 by danielji          #+#    #+#             */
/*   Updated: 2025/11/23 02:54:33 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Todos los builtins devuelven 0 si han tenido éxito o un número distinto de
0 en caso de error.
Devuelven 2 para indicar uso incorrecto, opciones inválidas o que faltan
argumentos. */

int	ft_env(char **envp)
{
	int	i;
	int	len;
	char	*write_str;

	i = 0;
	len = 0;
	while (envp[i] != NULL)
	{
		write_str= ft_strjoin(envp[i++], "\n");
		len = ft_strlen(write_str);
		write(STDOUT_FILENO, write_str, len);
	}
//	ft_putendl_fd("env test", STDOUT_FILENO);
	return (0);
}
