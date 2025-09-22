/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:18:26 by danielji          #+#    #+#             */
/*   Updated: 2025/09/22 10:42:14 by danielji         ###   ########.fr       */
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

# include "libft.h"

// malloc, free
# include <stdlib.h>

// readline
# include <stdio.h>

// readline
# include <readline/readline.h>
# include <readline/history.h>


int		count_substrings(char *str);
void	split_by_metacharacter(char *line);

#endif