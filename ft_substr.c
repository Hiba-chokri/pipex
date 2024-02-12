/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: hichokri <marvin@42.fr>                    +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/02/11 16:11:53 by hichokri          #+#    #+#             */
/*   Updated: 2024/02/11 16:11:58 by hichokri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*substr;
	size_t			str_len;

	if (!s)
		return (ft_strdup(""));
	i = 0;
	str_len = ft_strlen(s);
	if (start > str_len)
		return (ft_strdup(""));
	if (start + len > str_len)
		len = str_len - start;
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	i = start;
	j = 0;
	while (j < len && s[start + j])
		substr[j++] = s[i++];
	substr[j] = '\0';
	return (substr);
}
