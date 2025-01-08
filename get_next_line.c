/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:59:50 by hinel-mo          #+#    #+#             */
/*   Updated: 2025/01/07 10:25:37 by hinel-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

char	*ft_join_and_free(char *b_static, char *b_temp)
{
	char	*temp;

	if (!b_temp)
		return (free(b_static), NULL);
	else if (!b_static)
		return (NULL);
	temp = ft_strjoin(b_static, b_temp);
	if (!temp)
		return (free(b_static), NULL);
	free(b_static);
	return (temp);
}

// suprimer la derniere ligne utilisee
char	*ft_next(char *b_static)
{
	int		i;
	int		j;
	char	*line;

	if (!b_static)
		return (NULL);
	i = 0;
	while (b_static[i] && b_static[i] != '\n')
		i++;
	if (!b_static[i])
		return (free(b_static), NULL);
	line = ft_calloc((ft_strlen(b_static) - i + 1), sizeof(char));
	if (!line)
		return (free(b_static), NULL);
	i++;
	j = 0;
	while (b_static[i])
		line[j++] = b_static[i++];
	free(b_static);
	return (line);
}

// prends une ligne afin de la retourner
char	*ft_line(char *b_static)
{
	char	*line;
	int		i;

	i = 0;
	if (!b_static[i])
		return (NULL);
	while (b_static[i] && b_static[i] != '\n')
		i++;
	line = ft_calloc(sizeof(char), i + 2);
	if (!line)
		return (free(line), free(b_static), NULL);
	i = 0;
	while (b_static[i] && b_static[i] != '\n')
	{
		line[i] = b_static[i];
		i++;
	}
	if (b_static[i] && b_static[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*read_file(int fd, char *b_static, ssize_t byte_read)
{
	char	*b_temp;

	if (!b_static)
	{
		b_static = ft_calloc(1, 1);
		if (!b_static)
			return (NULL);
	}
	b_temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!b_temp)
		return (NULL);
	while (byte_read > 0)
	{
		byte_read = read(fd, b_temp, BUFFER_SIZE);
		if (byte_read == -1 && !b_static)
			return (free(b_temp), NULL);
		b_temp[byte_read] = '\0';
		b_static = ft_join_and_free(b_static, b_temp);
		if (!b_static)
			return (free(b_temp), NULL);
		if (ft_strchr(b_temp, '\n'))
			break ;
	}
	return (free(b_temp), b_static);
}

char	*get_next_line(int fd)
{
	static char	*b_static;
	char		*line;
	ssize_t		byte_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(b_static), b_static = NULL, NULL);
	byte_read = 1;
	b_static = read_file(fd, b_static, byte_read);
	if (!b_static || !b_static[0])
		return (free(b_static), b_static = NULL, NULL);
	line = ft_line(b_static);
	if (!line)
		return (free(b_static), b_static = NULL, NULL);
	b_static = ft_next(b_static);
	return (line);
}

/*
#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;

	fd1 = open("tests/test.txt", O_RDONLY);
	fd2 = open("tests/test2.txt", O_RDONLY);
	fd3 = open("tests/test3.txt", O_RDONLY);
	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd2);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd3);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}
*/
