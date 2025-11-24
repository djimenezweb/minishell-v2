/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:30:37 by danielji          #+#    #+#             */
/*   Updated: 2025/11/24 17:36:15 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

// execution
# define READ_END 0
# define WRITE_END 1

//expander
# define TEMP_DOUBLE_QUOTE 18 
# define TEMP_SINGLE_QUOTE 20 
# define SUB_CHAR 26

//lexer
# define SPACE 32
# define DOUBLE_QUOTE 34
# define DOLLAR 36
# define SINGLE_QUOTE 39
# define SLASH 47
# define LESS 60
# define EQUALS 61
# define GREATER 62
# define BACKSLASH 92
# define PIPE 124
# define TILDE 126

# define DEFAULT_PATH \
"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

#endif
