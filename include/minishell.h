/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:18:26 by danielji          #+#    #+#             */
/*   Updated: 2025/09/25 10:29:44 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef MINISHELL_H
# define MINISHELL_H

# define SPACE 32
# define DOUBLE_QUOTE 34
# define DOLLAR 36
# define SINGLE_QUOTE 39
# define LESS 60
# define GREATER 62
# define BACKSLASH 92
# define PIPE 124
# define TILDE 126

// Libft
# include "libft.h"

// malloc, free
# include <stdlib.h>

// readline
# include <stdio.h>

// readline
# include <readline/readline.h>
# include <readline/history.h>

// parser
char	**split_by_space(char *line);
char	**split_by_metacharacter(char **arr);
void	free_array_n(char **arr, int n);

#endif