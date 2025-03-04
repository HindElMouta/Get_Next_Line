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

// Fonction qui concatène deux chaînes de caractères et libère la première
char	*ft_join_and_free(char *var_static, char *var_temp)
{
	char	*temp;

	if (!var_temp)
		return (free(var_static), NULL);
	else if (!var_static)
		return (NULL);
	temp = ft_strjoin(var_static, var_temp);
	if (!temp)
		return (free(var_static), NULL);
	return (free(var_static), temp);
}

// Fonction qui supprime la première ligne de var_static et retourne le reste
char	*ft_next(char *var_static)
{
	int		i;
	int		j;
	char	*line;

	if (!var_static)
		return (NULL);
	i = 0;
	while (var_static[i] && var_static[i] != '\n')
		i++;
	if (!var_static[i])
		return (free(var_static), NULL);
	line = ft_calloc((ft_strlen(var_static) - i + 2), sizeof(char));
	if (!line)
		return (free(var_static), NULL);
	i++;
	j = 0;
	while (var_static[i])
		line[j++] = var_static[i++];
	free(var_static);
	return (line);
}

// Fonction qui extrait la première ligne de var_static
char	*ft_line(char *var_static)
{
	char	*line;
	int		i;

	i = 0;
	if (!var_static[i])
		return (NULL);
	while (var_static[i] && var_static[i] != '\n')
		i++;
	line = ft_calloc(sizeof(char), i + 2);
	if (!line)
		return (free(line), free(var_static), NULL);
	i = 0;
	while (var_static[i] && var_static[i] != '\n')
	{
		line[i] = var_static[i];
		i++;
	}
	if (var_static[i] && var_static[i] == '\n')
		line[i++] = '\n';
	return (line);
}

// Fonction qui lit le fichier et remplit var_static avec le contenu lu
char	*read_file(int fd, char *var_static, ssize_t	byte_read)
{
	char	*var_temp;

	if (!var_static)
	{
		var_static = ft_calloc(1, 1);
		if (!var_static)
			return (NULL);
	}
	var_temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!var_temp)
		return (NULL);
	while (byte_read > 0)
	{
		byte_read = read(fd, var_temp, BUFFER_SIZE);
		if (byte_read == -1 && !var_static)
			return (free(var_temp), NULL);
		var_temp[byte_read] = '\0';
		var_static = ft_join_and_free(var_static, var_temp);
		if (!var_static)
			return (free(var_temp), NULL);
		if (ft_strchr(var_temp, '\n'))
			break ;
	}
	return (free(var_temp), var_static);
}

// Fonction principale qui retourne la ligne suivante du fichier
char	*get_next_line(int fd)
{
	static char	*var_static;
	char		*line;
	ssize_t		byte_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(var_static), var_static = NULL, NULL);
	byte_read = 1;
	var_static = read_file(fd, var_static, byte_read);
	if (!var_static || !var_static[0])
	{
		free(var_static);
		var_static = NULL;
		return (NULL);
	}
	line = ft_line(var_static);
	if (!line)
	{
		free(var_static);
		var_static = NULL;
		return (NULL);
	}
	var_static = ft_next(var_static);
	return (line);
}
/*
#include <stdio.h>
#include <fcntl.h>
int main(void)
{
    char *line;
    int i;
    int fd1;
    int fd2;
    int fd3;

    // Ouvre trois fichiers en lecture
    fd1 = open("tests/test.txt", O_RDONLY);
    fd2 = open("tests/test2.txt", O_RDONLY);
    fd3 = open("tests/test3.txt", O_RDONLY);

    if (fd1 < 0 || fd2 < 0 || fd3 < 0) {
        perror("Erreur d'ouverture de fichier");
        return (1);
    }

    i = 0;
    while (i < 3)
    {
        // Lire et afficher la ligne de fd1
        line = get_next_line(fd1);
        if (line)
        {
            printf("line [%02d]: %s", i, line);
            free(line);
        }
        else
            printf("line [%02d]: (NULL)\n", i);

        // Lire et afficher la ligne de fd2
        line = get_next_line(fd2);
        if (line)
        {
            printf("line [%02d]: %s", i, line);
            free(line);
        }
        else
            printf("line [%02d]: (NULL)\n", i);

        // Lire et afficher la ligne de fd3
        line = get_next_line(fd3);
        if (line)
        {
            printf("line [%02d]: %s", i, line);
            free(line);
        }
        else
            printf("line [%02d]: (NULL)\n", i);

        i++;
    }

    // Fermer les fichiers
    close(fd1);
    close(fd2);
    close(fd3);

	// Après la boucle while et avant return(0);
	while ((line = get_next_line(fd1)) != NULL)
		free(line);
	while ((line = get_next_line(fd2)) != NULL)
		free(line);
	while ((line = get_next_line(fd3)) != NULL)
		free(line);

    return (0);
}*/