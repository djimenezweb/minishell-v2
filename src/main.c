/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:18:33 by danielji          #+#    #+#             */
/*   Updated: 2025/09/23 12:13:18 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

void	print_array(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		ft_printf(">%s<\n", arr[i]);
		i++;
	}
}

void	free_array(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	char *rl;
	char **arr;

	rl = readline("MINISHELL 1.0 - $");
	ft_printf("%s\n", rl);
	arr = split_by_space(rl);
	print_array(arr);
	free(rl);
	free_array(arr);
	return (0);
}
