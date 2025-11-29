/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 10:53:51 by danielji          #+#    #+#             */
/*   Updated: 2025/11/29 19:15:51 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

# define CD_NO_HOME "minishell: cd: HOME not set"
# define CD_NO_DIR "minishell: cd: No such file or directory"
# define CD_GETCWD "minishell: cd: getcwd failed"
# define CD_ARGS "minishell: cd: too many arguments"

int	execute_cd(char **cmd, char *new_path,
		t_env_var *env_list, char **envp);
int	execute_echo(t_cmd *cmd);
int	ft_env(char **cmd, char **envp, int call_from_export);
int	ft_exit(t_cmd *cmd);
int	ft_export(char **cmd, t_env_var *env_list, char **envp);
int	ft_pwd(void);
int	ft_unset(t_cmd *cmd);

#endif
