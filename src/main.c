/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:18:33 by danielji          #+#    #+#             */
/*   Updated: 2025/09/22 10:47:18 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	char *rl;

	rl = readline("MINISHELL 1.0 - $");
	ft_printf("Hello world\n");
	ft_printf("%s\n", rl);
	split_by_metacharacter(rl);
	free(rl);
	return (0);
}
