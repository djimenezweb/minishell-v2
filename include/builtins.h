/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 10:53:51 by danielji          #+#    #+#             */
/*   Updated: 2025/11/22 12:53:03 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int	ft_cd(void);
int	execute_echo(t_cmd *cmd);
int	ft_env(void);
int	ft_exit(void);
int	ft_export(void);
int	ft_pwd(void);
int	ft_unset(void);

#endif
