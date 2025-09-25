/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:18:33 by danielji          #+#    #+#             */
/*   Updated: 2025/09/25 10:50:26 by danielji         ###   ########.fr       */
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
	char **arr2;

	rl = readline("MINISHELL 1.0 - $");
	//ft_printf("%s\n", rl);
	arr = split_by_space(rl);
	print_array(arr);
	arr2 = split_by_metacharacter(arr);
	print_array(arr2);
	free(rl);
	free_array(arr);
	ft_printf("=== END ===\n");
	return (0);
}
