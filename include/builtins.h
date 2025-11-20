/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 10:53:51 by danielji          #+#    #+#             */
/*   Updated: 2025/11/20 16:49:57 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int	ft_exit(void);
//int	ft_exit(t_shell shell);
int	execute_echo(t_cmd *cmd);

#endif