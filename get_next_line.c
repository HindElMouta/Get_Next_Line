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
	else if (!var_static) // Si var_static est NULL (première allocation)
		return (NULL);
	temp = ft_strjoin(var_static, var_temp); // Concatène var_static et var_temp
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
	while (var_static[i] && var_static[i] != '\n') // Trouve l'index du premier '\n'
		i++;
	if (!var_static[i]) // Si il n'y a pas de '\n', le fichier est complètement lu
		return (free(var_static), NULL); // Libère la mémoire et retourne NULL
	line = ft_calloc((ft_strlen(var_static) - i + 2), sizeof(char)); // Alloue de la mémoire pour la ligne restante
	if (!line) // Si l'allocation échoue
		return (free(var_static), NULL); // Libère var_static et retourne NULL
	i++; // Passe le '\n'
	j = 0;
	while (var_static[i]) // Copie les caractères après '\n'
		line[j++] = var_static[i++];
	free(var_static); // Libère var_static après avoir extrait la ligne
	return (line); // Retourne la nouvelle ligne
}

// Fonction qui extrait la première ligne de var_static
char	*ft_line(char *var_static)
{
	char	*line;
	int		i;

	i = 0;
	if (!var_static[i])
		return (NULL);
	while (var_static[i] && var_static[i] != '\n') // Cherche jusqu'à '\n'
		i++;
	line = ft_calloc(sizeof(char), i + 2); // Alloue de la mémoire pour la ligne
	if (!line)
		return (free(line), free(var_static), NULL); // Libère tout et retourne NULL
	i = 0;
	while (var_static[i] && var_static[i] != '\n') // Copie les caractères avant '\n'
	{
		line[i] = var_static[i];
		i++;
	}
	if (var_static[i] && var_static[i] == '\n') // Si '\n' est trouvé
		line[i++] = '\n'; // Ajoute '\n' à la ligne
	return (line); // Retourne la ligne
}

// Fonction qui lit le fichier et remplit var_static avec le contenu lu
char	*read_file(int fd, char *var_static, ssize_t	byte_read)
{
	char	*var_temp;

	if (!var_static) // Si var_static est NULL (première lecture)
	{
		var_static = ft_calloc(1, 1); // Alloue de la mémoire pour une chaîne vide
		if (!var_static) // Si l'allocation échoue
			return (NULL); // Retourne NULL
	}
	var_temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char)); // Alloue de la mémoire pour un buffer
	if (!var_temp) // Si l'allocation échoue
		return (NULL); // Retourne NULL
	while (byte_read > 0) // Tant qu'il y a des données à lire
	{
		byte_read = read(fd, var_temp, BUFFER_SIZE); // Lit les données dans var_temp
		if (byte_read == -1 && !var_static) // Si la lecture échoue
			return (free(var_temp), NULL); // Libère var_temp et retourne NULL
		var_temp[byte_read] = '\0'; // Assure que var_temp est une chaîne valide
		var_static = ft_join_and_free(var_static, var_temp); // Concatène avec var_static
		if (!var_static) // Si la concaténation échoue
			return (free(var_temp), NULL); // Libère var_temp et retourne NULL
		if (ft_strchr(var_temp, '\n')) // Si un '\n' est trouvé, on s'arrête
			break ;
	}
	return (free(var_temp), var_static); // Libère var_temp et retourne var_static
}

// Fonction principale qui retourne la ligne suivante du fichier
char	*get_next_line(int fd)
{
	static char	*var_static;
	char		*line;
	ssize_t		byte_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0) // Vérifie les erreurs d'argument
		return (free(var_static), var_static = NULL, NULL); // Retourne NULL en cas d'erreur
	byte_read = 1; // Initialise byte_read
	var_static = read_file(fd, var_static, byte_read); // Lit le fichier
	if (!var_static || !var_static[0]) // Si plus rien à lire
	{
		free(var_static); // Libère var_static
		var_static = NULL;
		return (NULL); // Retourne NULL
	}
	line = ft_line(var_static); // Extrait la ligne suivante
	if (!line) // Si l'extraction échoue
	{
		free(var_static); // Libère var_static
		var_static = NULL;
		return (NULL); // Retourne NULL
	}
	var_static = ft_next(var_static); // Met à jour var_static pour le prochain appel
	return (line); // Retourne la ligne lue
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