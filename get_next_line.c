/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeliew <yeliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 13:07:36 by yeliew            #+#    #+#             */
/*   Updated: 2026/08/17 13:07:39 by yeliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*find_nlsplit(char *s, char *buffer)
{
	int		nl;
	int		i;
	int		j;
	char	*line;

	nl = 0;
	while (s[nl] && s[nl] != '\n')
		nl++;
	if (s[nl] == 0)
		return (0);
	line = malloc(nl + 2);
	if (!line)
		return (0);
	i = 0;
	while (i <= nl)
	{
		line[i] = s[i];
		i++;
	}
	line[i] = 0;
	j = 0;
	nl++;
	while (s[nl])
		buffer[j++] = s[nl++];
	buffer[j] = 0;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*dest;
	int			bytes_read;
	char		*line;

	dest = ft_strdup(buffer);
	if (!dest)
		return (0);
	if (ft_strchr(dest, '\n'))
	{
		line = find_nlsplit(dest, buffer);
		free(dest);
		return (line);
	}
	while (!ft_strchr(dest, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(dest);
			return (0);
		}
		if (bytes_read == 0)
		{
			buffer[0] = 0;
			if (dest[0] == 0)
			{
				free(dest);
				return (0);
			}
			break ;
		}
		buffer[bytes_read] = 0;
		dest = ft_strjoin(dest, buffer);
		if (ft_strchr(dest, '\n'))
		{
			line = find_nlsplit(dest, buffer);
			free(dest);
			return (line);
		}
	}
	return (dest);
}
