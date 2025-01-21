/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:53:20 by ngaurama          #+#    #+#             */
/*   Updated: 2024/11/20 18:38:05 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_flag(int c)
{
	if (c == '-' || c == '0' || c == '.' || c == '#' || c == ' '
		|| c == '+')
		return (1);
	return (0);
}

int	is_letter(int c)
{
	if (c == 'c' || c == 's' || c == 'd' || c == 'i' || c == 'u' || c == 'x'
		|| c == 'X' || c == 'p' || c == '%')
		return (1);
	return (0);
}

int	ft_conditions(int c)
{
	return (is_flag(c) || is_letter(c) || ft_isdigit(c));
}

int	ft_precision(char const *format, int shift, t_flags *flags)
{
	shift++;
	flags->precision = 0;
	while (ft_isdigit(format[shift]))
		flags->precision = (flags->precision * 10) + (format[shift++] - '0');
	return (shift);
}

int	ft_pad(int len, int shift, t_flags flags)
{
	int	count;

	count = 0;
	while (len - shift > 0)
	{
		if (flags.zero_padding)
			count += write(1, "0", 1);
		else
		{
			count += write(1, " ", 1);
		}
		len--;
	}
	return (count);
}
