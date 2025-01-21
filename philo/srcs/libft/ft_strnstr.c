/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:38:49 by ngaurama          #+#    #+#             */
/*   Updated: 2024/11/12 15:32:56 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	i;

	needle_len = ft_strlen(needle);
	if (!*needle)
		return ((char *)haystack);
	i = 0;
	while (i <= len)
	{
		if (i + needle_len > len && haystack)
			break ;
		if (!ft_memcmp(&haystack[i], needle, needle_len))
			return ((char *)&haystack[i]);
		if (haystack[i] == '\0')
			break ;
		i++;
	}
	return (NULL);
}
