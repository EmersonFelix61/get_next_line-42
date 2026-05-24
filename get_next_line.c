/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emda-sil <emda-sil@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 13:30:57 by emda-sil          #+#    #+#             */
/*   Updated: 2026/05/24 16:55:13 by emda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_stash(int fd, char *stash)
{
	char		buffer[BUFFER_SIZE + 1];
	ssize_t		bytes_read;

	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(stash);
			return (NULL);
		}
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			stash = ft_strjoin_stash(stash, buffer);
			if (!stash)
				return (free(stash), NULL);
		}
	}
	return (stash);
}

static char	*get_line(char *stash)
{
	size_t	i;
	size_t	n;
	char	*line;

	if (!stash || !stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n' )
		i++;
	n = i;
	if (stash[i] == '\n')
		n++;
	line = malloc(sizeof(char) * (n + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < n)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*clean_stash(char *stash)
{
	char	*new_stash;
	int		j;
	int		i;

	if (!stash || !stash[0])
		return (free(stash), NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] != '\n')
		return (free(stash), NULL);
	i++;
	if (stash[i] == '\0')
		return (free(stash), NULL);
	j = ft_strlen(&stash[i]);
	new_stash = malloc(sizeof(char) * (j + 1));
	if (!new_stash)
		return (free(stash), NULL);
	j = -1;
	while (stash[i + ++j])
		new_stash[j] = stash[j + i];
	new_stash[j] = '\0';
	return (free(stash), new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = get_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = clean_stash(stash);
	return (line);
}
