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

// Elle permet de calculer la longuer exprimee en nombre de char
size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

//concatene 2 element,et alloue a l'exterieur de la memoire
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined_str;
	size_t	len1;
	size_t	len2;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	joined_str = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!joined_str)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		joined_str[i] = s1[i];
		i++;
	}
	while (i < len1 + len2)
	{
		joined_str[i] = s2[i - len1];
		i++;
	}
	joined_str[i] = '\0';
	return (joined_str);
}

//recherche la 1er occurence passe dans le 2eme en param
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

//alloue un bloc de mémoire en initialisant tous ces octets à la valeur 0.
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
