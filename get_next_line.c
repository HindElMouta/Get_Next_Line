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
char	*ft_join_and_free(char *b_static, char *b_temp)
{
	char	*temp;

	if (!b_temp) // Si b_temp est NULL, une erreur s'est produite, on libère b_static et retourne NULL
		return (free(b_static), NULL);
	else if (!b_static)
		return (NULL); // Si b_static est NULL, il n'y a rien à joindre, on retourne NULL
	temp = ft_strjoin(b_static, b_temp); // On concatène b_static et b_temp dans temp
	if (!temp)
		return (free(b_static), NULL); // Si la concaténation échoue (pas assez de mémoire), on libère b_static et retourne NULL
	free(b_static); // Libère la mémoire de b_static car son contenu est maintenant dans temp
	return (temp); // Retourne la nouvelle chaîne concaténée
}

// Fonction qui supprime la première ligne de b_static et retourne le reste
char	*ft_next(char *b_static)
{
	int		i;
	int		j;
	char	*line;

	if (!b_static) // Si b_static est NULL, il n'y a rien à traiter, on retourne NULL
		return (NULL);
	i = 0;
	while (b_static[i] && b_static[i] != '\n') // Trouve l'indice du caractère '\n' ou la fin de la chaîne
		i++;
	if (!b_static[i]) // Si il n'y a pas de '\n' dans b_static, on libère et retourne NULL
		return (free(b_static), NULL);
	line = ft_calloc((ft_strlen(b_static) - i + 1), sizeof(char)); // On alloue de la mémoire pour la nouvelle ligne contenant le reste de b_static après '\n'
	if (!line) // Si l'allocation échoue, on libère b_static et retourne NULL
		return (free(b_static), NULL);
	i++; // Incrémente i pour passer le caractère '\n'
	j = 0;
	while (b_static[i]) // Copie le reste de b_static dans line
		line[j++] = b_static[i++];
	free(b_static); // Libère la mémoire de b_static car on a extrait son contenu
	return (line); // Retourne la chaîne contenant le reste de b_static
}

// Fonction qui extrait la première ligne de b_static
char	*ft_line(char *b_static)
{
	char	*line;
	int		i;

	i = 0;
	if (!b_static[i]) // Si b_static est vide, il n'y a rien à extraire, on retourne NULL
		return (NULL);
	while (b_static[i] && b_static[i] != '\n') // Recherche le caractère '\n' dans b_static pour déterminer la fin de la ligne
		i++;
	line = ft_calloc(sizeof(char), i + 2); // Alloue de la mémoire pour la ligne extraite (en incluant le '\n' si présent)
	if (!line) // Si l'allocation échoue, on libère la mémoire et retourne NULL
		return (free(line), free(b_static), NULL);
	i = 0;
	while (b_static[i] && b_static[i] != '\n') // Copie le contenu de b_static dans line jusqu'à '\n'
	{
		line[i] = b_static[i];
		i++;
	}
	if (b_static[i] && b_static[i] == '\n') // Si un '\n' est trouvé, on le copie dans line
		line[i++] = '\n';
	return (line); // Retourne la ligne extraite
}

// Fonction qui lit le fichier et remplit b_static avec le contenu lu
char	*read_file(int fd, char *b_static, ssize_t byte_read)
{
	char	*b_temp;

	if (!b_static) // Si b_static est NULL, on l'initialise à une chaîne vide
	{
		b_static = ft_calloc(1, 1);
		if (!b_static)
			return (NULL);
	}
	b_temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char)); // Alloue un tampon temporaire pour lire les données du fichier
	if (!b_temp)
		return (NULL);
	while (byte_read > 0) // Lit le fichier et ajoute son contenu dans b_static
	{
		byte_read = read(fd, b_temp, BUFFER_SIZE); // Lit jusqu'à BUFFER_SIZE octets du fichier
		if (byte_read == -1 && !b_static) // Si une erreur survient lors de la lecture, on libère b_temp et retourne NULL
			return (free(b_temp), NULL);
		b_temp[byte_read] = '\0'; // Assure que la chaîne temporaire se termine par un caractère nul
		b_static = ft_join_and_free(b_static, b_temp); // Concatène le contenu de b_temp dans b_static
		if (!b_static) // Si la concaténation échoue, on libère b_temp et retourne NULL
			return (free(b_temp), NULL);
		if (ft_strchr(b_temp, '\n')) // Si b_temp contient un '\n', on arrête la lecture
			break ;
	}
	return (free(b_temp), b_static); // Libère b_temp et retourne b_static mis à jour
}

// Fonction principale qui retourne la ligne suivante du fichier
char	*get_next_line(int fd)
{
	char					*line;
	static char			*b_static;
	ssize_t	byte_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0) // Vérifie si le descripteur de fichier est valide et si la lecture est possible
		return (free(b_static), b_static = NULL, NULL);
	byte_read = 1;
	b_static = read_file(fd, b_static, byte_read); // Appelle read_file pour remplir b_static avec le contenu du fichier
	if (!b_static || !b_static[0]) // Si b_static est vide ou NULL, cela signifie qu'il n'y a plus de contenu à lire
		return (free(b_static), b_static = NULL, NULL);
	line = ft_line(b_static); // Extrait la première ligne de b_static
	if (!line) // Si l'extraction échoue, on libère la mémoire et retourne NULL
		return (free(b_static), b_static = NULL, NULL);
	b_static = ft_next(b_static); // Met à jour b_static pour supprimer la ligne déjà lue
	return (line); // Retourne la ligne extraite
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

    i = 1;
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
*/