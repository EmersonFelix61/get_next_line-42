/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emda-sil <emda-sil@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:43:25 by emda-sil          #+#    #+#             */
/*   Updated: 2026/05/25 10:43:42 by emda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	i = 0;
	str = (char *)s;
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			return (&str[i]);
		i++;
	}
	if (str[i] == (unsigned char)c)
		return (&str[i]);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*dup;

	if (!s)
		return (NULL);
	dup = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin_stash(char *stash, char *buffer)
{
	size_t	i;
	size_t	j;
	size_t	len_stash;
	char	*new_stash;

	if (!buffer)
		return (NULL);
	len_stash = 0;
	if (stash)
		len_stash = ft_strlen(stash);
	new_stash = malloc(sizeof(char) * (len_stash + ft_strlen(buffer) + 1));
	if (!new_stash)
		return (free(stash), NULL);
	i = 0;
	while (stash && stash[i])
	{
		new_stash[i] = stash[i];
		i++;
	}
	j = 0;
	while (buffer[j])
		new_stash[i++] = buffer[j++];
	new_stash[i] = '\0';
	return (free(stash), new_stash);
}
