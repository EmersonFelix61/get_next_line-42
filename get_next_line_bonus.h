/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emda-sil <emda-sil@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:44:03 by emda-sil          #+#    #+#             */
/*   Updated: 2026/05/25 10:46:21 by emda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*ft_strchr(const char *s, int c);
char	*ft_strjoin_stash(char *stash, char *buffer);
char	*get_next_line(int fd);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *str);

#endif
