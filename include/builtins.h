/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 10:53:51 by danielji          #+#    #+#             */
/*   Updated: 2025/11/27 11:00:43 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int	execute_cd(char **cmd, char *new_path, t_env_var *envp);
int	execute_echo(t_cmd *cmd);
int	ft_env(char **cmd, char **envp);
void	ft_exit(t_shell *data);
int	ft_export(char **cmd, t_env_var *env_list, char **envp);
int	ft_pwd(void);
int	ft_unset(void);

#endif
