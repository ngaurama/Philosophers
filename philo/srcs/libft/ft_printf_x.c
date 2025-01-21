/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:33:06 by ngaurama          #+#    #+#             */
/*   Updated: 2024/11/12 17:04:29 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_phex(char *num, int n, int bigger, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.zero_padding && flags.hash && n)
		count += ft_bigger(bigger);
	if (flags.left_justify)
	{
		if (flags.precision >= 0)
			flags.zero_padding = 1;
		count += ft_phex_helper(num, n, flags, bigger);
	}
	if (flags.precision >= 0 && (size_t)flags.precision < ft_strlen(num))
		flags.precision = ft_strlen(num);
	if (flags.precision >= 0)
	{
		flags.width -= flags.precision;
		flags.zero_padding = 0;
		count += ft_pad(flags.width, 0, flags);
		flags.zero_padding = 1;
	}
	else
		count += ft_pad(flags.width, ft_strlen(num) + (flags.hash * 2), flags);
	if (!flags.left_justify)
		count += ft_phex_helper(num, n, flags, bigger);
	return (count);
}

int	ft_printf_x(unsigned int n, t_flags flags, int big)
{
	char	*num;
	int		count;

	count = 0;
	if (!flags.precision && !n)
	{
		count += ft_pad(flags.width, 0, flags);
		return (count);
	}
	num = ft_hextoa(n, big);
	if (!num)
		return (0);
	count += ft_phex(num, n, big, flags);
	free(num);
	return (count);
}
