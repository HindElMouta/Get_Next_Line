/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:59:50 by hinel-mo          #+#    #+#             */
/*   Updated: 2024/12/09 08:24:15 by hinel-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//Cette fonction sert a concatene 2 element,la chaine renvoye est alloue a l'exterieur de la memoire de travaille
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined_str;
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1); //calcule de la premire ligne 
	len2 = ft_strlen(s2); //calcule de la 2em ligne 
	joined_str = (char *)malloc((len1 + len2 + 1) * sizeof(char)); // j'alloue de l'espace avc malloc 
	if (!joined_str)
		return (NULL); // si la location echou elle envoi NULL
	i = -1;
	while (i++, i < len1)
		joined_str[i] = s1[i];
	j = -1;
	while (j++, j < len2)
		joined_str[i + j] = s2[j];
	joined_str[i + j] = '\0';
	return (joined_str);
}
	
//Cette fonction recherche la premiere occurence passe dans le 2eme parametre de char specifie en param
char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str != c && *str != 0)
		str++;
	if (*str == c)
		return (str);
	else
		return (NULL);
}

//La fonction bzero () doit placer n octets de valeur zéro dans la zone pointée par s.
void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = '0';
		i ++;
}
	}
		
//Cette fonction alloue un bloc de mémoire en initialisant tous ces octets à la valeur 0.
void	*ft_calloc(size_t nmemb, size_t size)
{
	int		c;
	void	*ptr;
	size_t	size_m;
	size_t	n;
	size_t	i;

	size_m = ((size_t)(-1));
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb && size > size_m / nmemb)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	i = 0;
	n = nmemb * size;
	c = 0;
	while (i < n)
	{
		((unsigned char *)ptr)[i] = (unsigned char)c;
		i++;
	}
	return (ptr);
}

//Elle permet de calculer la longuer exprimee en nombre de char 
size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
