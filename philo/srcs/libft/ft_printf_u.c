/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:24:10 by ngaurama          #+#    #+#             */
/*   Updated: 2025/01/29 00:54:13 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pu2(char *num, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.precision >= 0)
		count += ft_pad(flags.precision - 1, ft_strlen(num) - 1, flags);
	count += ft_print_e(num);
	return (count);
}

int	ft_pu(char *num, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.left_justify)
	{
		if (flags.precision >= 0)
			flags.zero_padding = 1;
		count += ft_pu2(num, flags);
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
		count += ft_pad(flags.width, ft_strlen(num), flags);
	if (!flags.left_justify)
		count += ft_pu2(num, flags);
	return (count);
}

int	ft_printf_u(unsigned n, t_flags flags)
{
	char	*num;
	int		count;

	count = 0;
	if (!flags.precision && !n)
	{
		count += ft_pad(flags.width, 0, flags);
		return (count);
	}
	num = ft_printf_utoa(n);
	if (!num)
		return (0);
	count += ft_pu(num, flags);
	free(num);
	return (count);
}
