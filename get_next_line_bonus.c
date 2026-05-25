/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emda-sil <emda-sil@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:38:26 by emda-sil          #+#    #+#             */
/*   Updated: 2026/05/25 10:43:50 by emda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_stash(int fd, char *stash)
{
	char		*buffer;
	ssize_t		bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free(stash), NULL);
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(stash), free(buffer), NULL);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			stash = ft_strjoin_stash(stash, buffer);
			if (!stash)
			{
				free(buffer);
				return (NULL);
			}
		}
	}
	return (free(buffer), stash);
}

static char	*get_line(char *stash)
{
	size_t	i;
	size_t	n;
	char	*line;

	if (!stash || !stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
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
	char	*new_line;

	if (!stash)
		return (NULL);
	new_line = ft_strchr(stash, '\n');
	if (!new_line || !new_line[1])
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_strdup(new_line + 1);
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = get_line(stash[fd]);
	if (!line)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	stash[fd] = clean_stash(stash[fd]);
	return (line);
}
