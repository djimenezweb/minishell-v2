/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:52:23 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/10/26 20:25:52 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include 'SOMETHING'//TO DO

//If strncmp returns 0, means word == "exit", so returns true as 1.
//Could be easy to misunderstand
static int	exit_is_called(char *word)
{
	int	len;

	len = ft_strlen(word);
	if (!ft_strncmp(word, "exit", len))
		return (1);
	return (0);
}

//	PURPOSE
/*exit command must be read a word exit, and execute a free of memory
 * and close the execution*/
//
//exit should be the only word passed to the shell, so first check if lex_list
//has just one token 
void	ft_exit(t_shell	*data)
{
	if (!data->ilex_list->next && exit_is_called(data->lex_list->value))	
		free_shell(data);//Enrique 26/10: Here I'am expecting to exit()
	//What must be done in case the whole word is not exit?
	//How we modify status of last execution? MUST EXIST AFTER EXECUTION
}
