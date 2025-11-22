/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:47:30 by danielji          #+#    #+#             */
/*   Updated: 2025/11/22 12:49:51 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Todos los builtins devuelven 0 si han tenido éxito o un número distinto de
0 en caso de error.
Devuelven 2 para indicar uso incorrecto, opciones inválidas o que faltan
argumentos. */

int	ft_unset(void)
{
	ft_putendl_fd("unset test", STDOUT_FILENO);
	return (0);
}