/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:25:13 by ngaurama          #+#    #+#             */
/*   Updated: 2025/01/29 00:54:13 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle_flags(char const *format, int shift, t_flags *flags)
{
	while (format[++shift] && ft_conditions(format[shift]))
	{
		if (format[shift] == '-')
			ft_hyphen(flags);
		if (format[shift] == '#')
			flags->hash = 1;
		if (format[shift] == ' ')
			flags->space = 1;
		if (format[shift] == '+')
			flags->plus = 1;
		if (format[shift] == '0' && !flags->left_justify && !flags->width)
			flags->zero_padding = 1;
		if (format[shift] == '.')
			shift = ft_precision(format, shift, flags);
		if (ft_isdigit(format[shift]))
			flags->width = (flags->width * 10) + (format[shift] - '0');
		if (is_letter(format[shift]))
		{
			flags->letter = format[shift];
			break ;
		}
	}
	return (shift);
}

int	fake_flags(int start, int shift, char const *format)
{
	int	count;

	count = 0;
	while (start <= shift)
		count += write(1, &format[start++], 1);
	return (count);
}

int	handler(char const *format, va_list args)
{
	t_flags	flags;
	int		count;
	int		shift;
	int		start;

	count = 0;
	shift = -1;
	while (format[++shift])
	{
		flags = ft_assign();
		if (format[shift] == '%' && format[shift + 1])
		{
			start = shift;
			shift = ft_handle_flags(format, shift, &flags);
			if (format[shift] && flags.letter && is_letter(format[shift]))
				count += ft_result(format[shift], args, flags);
			else
				count += fake_flags(start, shift, format);
		}
		else
			count += write(1, &format[shift], 1);
	}
	return (count);
}
