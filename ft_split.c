/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichokri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:10:02 by hichokri          #+#    #+#             */
/*   Updated: 2024/02/11 16:10:08 by hichokri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	count_words(char *str, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (str && str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] == c)
			i++;
		if (str[i] != '\0' && str[i] != c)
		{
			count++;
			i++;
		}
		while (str[i] != '\0' && str[i] != c)
			i++;
	}
	return (count);
}

static void	*free_str(char **tab, int c)
{
	int	i;

	i = 0;
	while (i < c)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

char	**ft_split(char *s, char c)
{
	char			**arr;
	unsigned int	i;
	unsigned int	j;
	unsigned int	start;

	i = 0;
	j = 0;
	arr = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (j < count_words(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] != '\0' && s[i] != c)
			i++;
		arr[j] = ft_substr(s, start, i - start);
		if (!arr[j])
			return (free_str(arr, j));
		j++;
	}
	arr[j] = NULL;
	return (arr);
}
