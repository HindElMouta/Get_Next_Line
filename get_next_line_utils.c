/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinel-mo <hinel-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:59:50 by hinel-mo          #+#    #+#             */
/*   Updated: 2025/01/07 10:25:37 by hinel-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//elle concatene 2 element,la char est alloue a l'exterieur de la memoire de travaille
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined_str;
	size_t	len1;
	size_t	len2;
	size_t	i;

	if (!s1 || !s2)
		return (NULL); // Vérifie si l'une des chaînes est NULL
	len1 = ft_strlen(s1); // Longueur de la première chaîne
	len2 = ft_strlen(s2); // Longueur de la deuxième chaîne
	joined_str = (char *)malloc((len1 + len2 + 1) * sizeof(char)); // Alloue de la mémoire pour les deux chaînes plus '\0'
	if (!joined_str)
		return (NULL); // Si l'allocation échoue, retourne NULL
	i = 0;
	while (i < len1) // Copie les caractères de s1 dans joined_str
	{
		joined_str[i] = s1[i];
		i++;
	}
	while (i < len1 + len2) // Copie les caractères de s2 dans joined_str
	{
		joined_str[i] = s2[i - len1];
		i++;
	}
	joined_str[i] = '\0'; // Ajoute le caractère nul de fin de chaîne
	return (joined_str);
}

// Cette fonction recherche la premiere occurence passe dans le 2eme parametre de char specifie en param
char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str != c && *str != 0) // Cherche jusqu'à trouver c ou '\0'
		str++;
	if (*str == c) // Si c est trouvé
		return (str);
	else
		return (NULL); // Sinon retourne NULL
}

// La fonction bzero () doit placer n octets de valeur zéro dans la zone pointée par s.
void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n) // Remplir les n premiers octets de s avec 0
	{
		*(unsigned char *)(s + i) = 0; // Cast et mettre à zéro
		i++;
	}
}

// Cette fonction alloue un bloc de mémoire en initialisant tous ces octets à la valeur 0.
void	*ft_calloc(size_t nmemb, size_t size)
{
	int		c;
	void	*ptr;
	size_t	size_m;
	size_t	n;
	size_t	i;

	size_m = ((size_t)(-1));
	if (nmemb == 0 || size == 0)
		return (malloc(0)); // Si nmemb ou size est 0, alloue 0 octet
	if (nmemb && size > size_m / nmemb)
		return (NULL); // Si multiplication déborde, retourne NULL
	ptr = malloc(nmemb * size); // Alloue la mémoire
	if (!ptr)
		return (NULL); // Si malloc échoue, retourne NULL
	i = 0;
	n = nmemb * size;
	c = 0;
	while (i < n) // Initialise tous les octets à 0
	{
		((unsigned char *)ptr)[i] = (unsigned char)c;
		i++;
	}
	return (ptr);
}

// Elle permet de calculer la longuer exprimee en nombre de char
size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i]) // Parcours la chaîne jusqu'au caractère nul
		i++;
	return (i); // Retourne la longueur de la chaîne
}
