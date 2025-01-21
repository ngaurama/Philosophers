/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:04:18 by ngaurama          #+#    #+#             */
/*   Updated: 2024/11/13 17:17:04 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_add(unsigned long n)
{
	int		count;
	char	c;

	count = 0;
	if (n >= 16)
		count += ft_add(n / 16);
	if (n % 16 < 10)
	{
		c = (n % 16) + '0';
		write(1, &c, 1);
		count++;
	}
	else
	{
		c = ((n % 16) - 10) + 'a';
		write(1, &c, 1);
		count++;
	}
	return (count);
}

int	ft_ptr(unsigned long n)
{
	int	count;

	count = 0;
	if (!n)
		return (count += ft_print_e("(nil)"));
	count += ft_print_e("0x");
	count += ft_add(n);
	return (count);
}

int	ft_plen(unsigned long n)
{
	int	len;

	len = 0;
	if (!n)
		return (0);
	while (n >= 1)
	{
		len++;
		n /= 16;
	}
	return (len);
}

int	ft_printf_p(unsigned long n, t_flags flags)
{
	int	count;

	count = 0;
	if (!n)
		flags.width -= 5;
	else
		flags.width -= 2;
	if (flags.left_justify)
		count += ft_ptr(n);
	count += ft_pad(flags.width, ft_plen(n), flags);
	if (!flags.left_justify)
		count += ft_ptr(n);
	return (count);
}
