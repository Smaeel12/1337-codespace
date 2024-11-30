/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 10:11:34 by iboubkri          #+#    #+#             */
/*   Updated: 2024/11/30 10:18:50 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# define OPEN_MAX 1024
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
ssize_t	fill_line_buffer(char *r_buffer, char **l_buffer);
void	reset_read_buffer(char *r_buffer, ssize_t start);
char	*init_buffer(char **ptr, size_t nmemb, size_t size);

#endif