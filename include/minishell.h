/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:18:26 by danielji          #+#    #+#             */
/*   Updated: 2025/11/30 18:08:46 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Libft and our headers
# include "../libft/libft.h"
# include "macros.h"
# include "environment.h"
# include "lexer.h"
# include "expander.h"
# include "syntax.h"
# include "parser.h"
# include "execution.h"

// malloc, free
# include <stdlib.h>

// readline, printf
# include <stdio.h>

// readline
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_shell
{
	char		*line;
	t_lextoken	*lex_list;
	t_env_var	*env_list;
	t_cmd		*cmd_list;
}			t_shell;

void	free_shell(t_shell *data, int exit_status);
void	print_lex_list(t_lextoken *list);
void	print_array_of_strings(char **arr);
void	print_cmd_list(t_cmd *list);
void	print_env_list(t_env_var *list);

#endif
