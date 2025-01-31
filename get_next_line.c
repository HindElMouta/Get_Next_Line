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

	if (!var_temp) // Vérifie si var_temp est NULL avant de faire quoi que ce soit
		return (free(var_static), NULL);
	if (!var_static) // Si var_static est NULL, on l'initialise à une chaîne vide pour éviter des erreurs
	{
		var_static = ft_calloc(1, 1);
		if (!var_static)
			return (free(var_temp), NULL);
	}
	temp = ft_strjoin(var_static, var_temp);
	free(var_static);
	if (!temp)
		return (free(var_temp), NULL); // Libère var_temp en cas d'échec d'allocation
	return (temp);
}

// Fonction qui supprime la première ligne de var_static et retourne le reste
char	*ft_next(char *var_static)
{
	int		i;
	int		j;
	char	*line;

	if (!var_static) // Si var_static est NULL, il n'y a rien à traiter, on retourne NULL
		return (NULL);
	i = 0;
	while (var_static[i] && var_static[i] != '\n') // Trouve l'indice du caractère '\n' ou la fin de la chaîne
		i++;
	if (!var_static[i]) // Si il n'y a pas de '\n' dans var_static, on libère et retourne NULL
		return (free(var_static), NULL);
	line = ft_calloc((ft_strlen(var_static) - i + 2), sizeof(char)); // On alloue de la mémoire pour la nouvelle ligne contenant le reste de var_static après '\n'
	if (!line) // Si l'allocation échoue, on libère var_static et retourne NULL
		return (free(var_static), NULL);
	i++; // Incrémente i pour passer le caractère '\n'
	j = 0;
	while (var_static[i]) // Copie le reste de var_static dans line
		line[j++] = var_static[i++];
	free(var_static); // Libère la mémoire de var_static car on a extrait son contenu
	return (line); // Retourne la chaîne contenant le reste de var_static
}

// Fonction qui extrait la première ligne de var_static
char	*ft_line(char *var_static)
{
	char	*line;
	int		i;

	i = 0;
	if (!var_static[i]) // Si var_static est vide, il n'y a rien à extraire, on retourne NULL
		return (NULL);
	while (var_static[i] && var_static[i] != '\n') // Recherche le caractère '\n' dans var_static pour déterminer la fin de la ligne
		i++;
	line = ft_calloc(sizeof(char), i + 2); // Alloue de la mémoire pour la ligne extraite (en incluant le '\n' si présent)
	if (!line) // Si l'allocation échoue, on libère la mémoire et retourne NULL
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
char	*read_file(int fd, char *var_static)
{
	char	*var_temp;
	ssize_t	byte_read;

	if (!var_static)
	{
		var_static = ft_calloc(1, 1);
		if (!var_static)
			return (NULL);
	}
	var_temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!var_temp)
		return (NULL);
	byte_read = read(fd, var_temp, BUFFER_SIZE);
	while (byte_read > 0)
	{
		var_temp[byte_read] = '\0';
		var_static = ft_join_and_free(var_static, var_temp);
		if (ft_strchr(var_temp, '\n')) // Arrêt si un '\n' est trouvé
			break;
		byte_read = read(fd, var_temp, BUFFER_SIZE); // Mise à jour de byte_read
	}
	free(var_temp);
	if (byte_read == -1) // Gestion d'erreur après la boucle
		return (free(var_static), NULL);
	return (var_static);
}

// Fonction principale qui retourne la ligne suivante du fichier
char    *get_next_line(int fd)
{
    char            *line;
    static char     *var_static;

    if (fd < 0 || BUFFER_SIZE <= 0)
    {
        free(var_static);
        var_static = NULL;
        return (NULL);
    }
    var_static = read_file(fd, var_static);
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
