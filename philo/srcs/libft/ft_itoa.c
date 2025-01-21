/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:35:11 by ngaurama          #+#    #+#             */
/*   Updated: 2024/11/12 13:13:51 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	num_size(long n)
{
	size_t	size;

	size = 0;
	if (n < 0)
	{
		size = 1;
		n = n * (-1);
	}
	if (n == 0)
		size = 1;
	else
	{
		while (n)
		{
			n /= 10;
			size++;
		}
	}
	return (size);
}

char	*ft_itoa(int n)
{
	size_t	size;
	char	*str;
	long	num;
	size_t	i;

	num = (long)n;
	i = 0;
	size = num_size(num);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	if (num < 0)
	{
		num = num * (-1);
		str[0] = '-';
		i = 1;
	}
	str[size] = '\0';
	while (size > i)
	{
		str[size - 1] = num % 10 + '0';
		num /= 10;
		size--;
	}
	return (str);
}
