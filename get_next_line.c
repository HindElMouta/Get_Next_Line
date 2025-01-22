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
char	*ft_join_and_free(char *variable_static, char *variable_temp)
{
	char	*temp;

	if (!variable_temp) // Si variable_temp est NULL, une erreur s'est produite, on libère variable_static et retourne NULL
		return (free(variable_static), NULL);
	else if (!variable_static)
		return (NULL); // Si variable_static est NULL, il n'y a rien à joindre, on retourne NULL
	temp = ft_strjoin(variable_static, variable_temp); // On concatène variable_static et variable_temp dans temp
	if (!temp)
		return (free(variable_static), NULL); // Si la concaténation échoue (pas assez de mémoire), on libère variable_static et retourne NULL
	free(variable_static); // Libère la mémoire de variable_static car son contenu est maintenant dans temp
	return (temp); // Retourne la nouvelle chaîne concaténée
}

// Fonction qui supprime la première ligne de variable_static et retourne le reste
char	*ft_next(char *variable_static)
{
	int		i;
	int		j;
	char	*line;

	if (!variable_static) // Si variable_static est NULL, il n'y a rien à traiter, on retourne NULL
		return (NULL);
	i = 0;
	while (variable_static[i] && variable_static[i] != '\n') // Trouve l'indice du caractère '\n' ou la fin de la chaîne
		i++;
	if (!variable_static[i]) // Si il n'y a pas de '\n' dans variable_static, on libère et retourne NULL
		return (free(variable_static), NULL);
	line = ft_calloc((ft_strlen(variable_static) - i + 1), sizeof(char)); // On alloue de la mémoire pour la nouvelle ligne contenant le reste de variable_static après '\n'
	if (!line) // Si l'allocation échoue, on libère variable_static et retourne NULL
		return (free(variable_static), NULL);
	i++; // Incrémente i pour passer le caractère '\n'
	j = 0;
	while (variable_static[i]) // Copie le reste de variable_static dans line
		line[j++] = variable_static[i++];
	free(variable_static); // Libère la mémoire de variable_static car on a extrait son contenu
	return (line); // Retourne la chaîne contenant le reste de variable_static
}

// Fonction qui extrait la première ligne de variable_static
char	*ft_line(char *variable_static)
{
	char	*line;
	int		i;

	i = 0;
	if (!variable_static[i]) // Si variable_static est vide, il n'y a rien à extraire, on retourne NULL
		return (NULL);
	while (variable_static[i] && variable_static[i] != '\n') // Recherche le caractère '\n' dans variable_static pour déterminer la fin de la ligne
		i++;
	line = ft_calloc(sizeof(char), i + 2); // Alloue de la mémoire pour la ligne extraite (en incluant le '\n' si présent)
	if (!line) // Si l'allocation échoue, on libère la mémoire et retourne NULL
		return (free(line), free(variable_static), NULL);
	i = 0;
	while (variable_static[i] && variable_static[i] != '\n') // Copie le contenu de variable_static dans line jusqu'à '\n'
	{
		line[i] = variable_static[i];
		i++;
	}
	if (variable_static[i] && variable_static[i] == '\n') // Si un '\n' est trouvé, on le copie dans line
		line[i++] = '\n';
	return (line); // Retourne la ligne extraite
}

// Fonction qui lit le fichier et remplit variable_static avec le contenu lu
char	*read_file(int fd, char *variable_static, ssize_t byte_read)
{
	char	*variable_temp;

	if (!variable_static) // Si variable_static est NULL, on l'initialise à une chaîne vide
	{
		variable_static = ft_calloc(1, 1);
		if (!variable_static)
			return (NULL);
	}
	variable_temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char)); // Alloue un tampon temporaire pour lire les données du fichier
	if (!variable_temp)
		return (NULL);
	while (byte_read > 0) // Lit le fichier et ajoute son contenu dans variable_static
	{
		byte_read = read(fd, variable_temp, BUFFER_SIZE); // Lit jusqu'à BUFFER_SIZE octets du fichier
		if (byte_read == -1 && !variable_static) // Si une erreur survient lors de la lecture, on libère variable_temp et retourne NULL
			return (free(variable_temp), NULL);
		variable_temp[byte_read] = '\0'; // Assure que la chaîne temporaire se termine par un caractère nul
		variable_static = ft_join_and_free(variable_static, variable_temp); // Concatène le contenu de variable_temp dans variable_static
		if (!variable_static) // Si la concaténation échoue, on libère variable_temp et retourne NULL
			return (free(variable_temp), NULL);
		if (ft_strchr(variable_temp, '\n')) // Si variable_temp contient un '\n', on arrête la lecture
			break ;
	}
	return (free(variable_temp), variable_static); // Libère variable_temp et retourne variable_static mis à jour
}

// Fonction principale qui retourne la ligne suivante du fichier
char	*get_next_line(int fd)
{
	char			*line;
	static char		*variable_static;
	ssize_t			byte_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0) // Vérifie si le descripteur de fichier est valide et si la lecture est possible
		return (free(variable_static), variable_static = NULL, NULL);
	byte_read = 1;
	variable_static = read_file(fd, variable_static, byte_read); // Appelle read_file pour remplir variable_static avec le contenu du fichier
	if (!variable_static || !variable_static[0]) // Si variable_static est vide ou NULL, cela signifie qu'il n'y a plus de contenu à lire
		return (free(variable_static), variable_static = NULL, NULL);
	line = ft_line(variable_static); // Extrait la première ligne de variable_static
	if (!line) // Si l'extraction échoue, on libère la mémoire et retourne NULL
		return (free(variable_static), variable_static = NULL, NULL);
	variable_static = ft_next(variable_static); // Met à jour variable_static pour supprimer la ligne déjà lue
	return (line); // Retourne la ligne extraite
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
    while (i < 7)
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
