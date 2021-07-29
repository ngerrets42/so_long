/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keycodes.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/29 11:09:59 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/06/29 11:10:27 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYCODES_H
# define KEYCODES_H

# ifdef __linux__
#  define KEY_ESC 65307
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_Q 113
#  define KEY_E 101
#  define KEY_Z 122
#  define KEY_X 120
#  define KEY_CTRL -1
#  define KEY_SPACE 32
#  define KEY_MB_LEFT 1
#  define KEY_MB_RIGHT 3
# else
#  define KEY_ESC 53
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_Q 12
#  define KEY_E 14
#  define KEY_Z 6
#  define KEY_X 7
#  define KEY_CTRL 256
#  define KEY_SPACE 49
#  define KEY_MB_LEFT 1
#  define KEY_MB_RIGHT 2
# endif

#endif