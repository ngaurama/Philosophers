/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_result.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:24:38 by ngaurama          #+#    #+#             */
/*   Updated: 2024/11/12 17:05:19 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_result(char letter, va_list args, t_flags flags)
{
	int	count;

	count = 0;
	if (letter == '%')
		count += ft_printf_c('%', flags);
	else if (letter == 'c')
		count += ft_printf_c(va_arg(args, int), flags);
	else if (letter == 's')
		count += ft_printf_s(va_arg(args, char *), flags);
	else if (letter == 'p')
		count += ft_printf_p((unsigned long)va_arg(args, void *), flags);
	else if (letter == 'd' || letter == 'i')
		count += ft_printf_d_i(va_arg(args, int), flags);
	else if (letter == 'u')
		count += ft_printf_u(va_arg(args, unsigned int), flags);
	else if (letter == 'x')
		count += ft_printf_x(va_arg(args, unsigned int), flags, 0);
	else if (letter == 'X')
		count += ft_printf_x(va_arg(args, unsigned int), flags, 1);
	return (count);
}
