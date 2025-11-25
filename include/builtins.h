/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 10:53:51 by danielji          #+#    #+#             */
/*   Updated: 2025/11/25 19:40:44 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int	execute_cd(char **cmd, char *new_path, t_env_var *envp);
int	execute_echo(t_cmd *cmd);
int	ft_env(char **cmd, char **envp);
int	ft_exit(void);
int	ft_export(void);
int	ft_pwd(void);
int	ft_unset(void);

#endif
