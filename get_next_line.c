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
	else if (!var_static) // l'initialise à une chaîne vide
		return (NULL);
	temp = ft_strjoin(var_static, var_temp); //je concatele les 2 variable
	if (!temp)
		return (free(var_static), NULL); // Libère buffer en cas d'échec d'allocation
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
	while (var_static[i] && var_static[i] != '\n') // Trouve l'indice du caractère '\n' 
		i++;
	if (!var_static[i]) // Si il n'y a pas de '\n' dans var_static, on libère et retourne NULL
		return (free(var_static), NULL);
	line = ft_calloc((ft_strlen(var_static) - i + 2), sizeof(char)); // On alloue de la mémoire pour la new
	if (!line)
		return (free(var_static), NULL);
	i++; // Incrémente i pour passer le caractère '\n'
	j = 0;
	while (var_static[i]) // Copie le reste de var_static dans line
		line[j++] = var_static[i++];
	free(var_static); // Libère la mémoire car on a extrait son contenu
	return (line); // Retourne le reste de var_static
}

// Fonction qui extrait la première ligne de var_static
char	*ft_line(char *var_static)
{
	char	*line;
	int		i;

	i = 0;
	if (!var_static[i]) 
		return (NULL);
	while (var_static[i] && var_static[i] != '\n') // Recherche le caractère '\n' dans var_static
		i++;
	line = ft_calloc(sizeof(char), i + 2); // Alloue de la mémoire pour la ligne extraite (en incluant le '\n' si présent)
	if (!line)
		return (free(line), free(var_static), NULL);
	i = 0;
	while (var_static[i] && var_static[i] != '\n') // Copie le contenu de var_static dans line jusqu'à '\n'
	{
		line[i] = var_static[i];
		i++;
	}
	if (var_static[i] && var_static[i] == '\n') // Si un '\n' est trouvé, on le copie dans line
		line[i++] = '\n';
	return (line); // Retourne la ligne extraite
}

// Fonction qui lit le fichier et remplit var_static avec le contenu lu
char	*read_file(int fd, char *var_static, ssize_t	byte_read)
{
	char	*var_temp;
	
	if (!var_static) // Si var_static est NULL, on l'initialise à une chaîne vide
	{
		var_static = ft_calloc(1, 1); // Alloue un seul octet initialisé à '\0'
		if (!var_static)
			return (NULL);
	}
	var_temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char)); // Allocation de mémoire pour le buffer temporaire +1 pour le '\0'
	if (!var_temp)
		return (NULL);
	while (byte_read > 0)// Boucle tant qu'on lit des données (byte_read > 0)
	{
		byte_read = read(fd, var_temp, BUFFER_SIZE);// Première lecture dans var_temp avant d'entrer dans la boucle
		if (byte_read == -1 && !var_static)
			return (free(var_temp), NULL);
		var_temp[byte_read] = '\0'; // Ajoute un caractère de fin de chaîne
		var_static = ft_join_and_free(var_static, var_temp); // Concatène et libère var_static
		if (!var_static)
			return (free(var_temp), NULL);
		if (ft_strchr(var_temp, '\n')) // Vérifie si un saut de ligne est présent dans le buffer
			break ; // On arrête la lecture dès qu'on trouve un '\n'
	}
	return (free(var_temp), var_static);// Retourne le contenu lu dans var_static
}


// Fonction principale qui retourne la ligne suivante du fichier
char    *get_next_line(int fd)
{
	static char	*var_static;
	char		*line;
	ssize_t		byte_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(var_static), var_static = NULL, NULL);
	byte_read = 1;
	var_static = read_file(fd, var_static, byte_read);
	if (!var_static || !var_static[0])
		return (free(var_static), var_static = NULL, NULL);
	line = ft_line(var_static);
	if (!line)
		return (free(var_static), var_static = NULL, NULL);
	var_static = ft_next(var_static);
	return (line);
}

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

    i = 0;
    while (i < 3)
    {
        // Lit une ligne de chaque fichier et l'affiche
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

    // Ferme les fichiers
    close(fd1);
    close(fd2);
    close(fd3);

    return (0);
}