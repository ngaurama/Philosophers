/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:34:26 by ngaurama          #+#    #+#             */
/*   Updated: 2024/11/20 18:21:26 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_s_helper(char const *str, t_flags flags)
{
	int	count;
	int	i;

	count = 0;
	if (flags.precision >= 0)
	{
		count += ft_pad(flags.precision, ft_strlen(str), flags);
		i = 0;
		while (str[i] && i < flags.precision)
			count += write(1, &str[i++], 1);
	}
	else
	{
		i = 0;
		while (str[i] && (size_t)i < ft_strlen(str))
			count += write(1, &str[i++], 1);
	}
	return (count);
}

int	ft_printf_s(char const *str, t_flags flags)
{
	int	count;

	count = 0;
	flags.zero_padding = 0;
	if (str == NULL && flags.precision >= 0 && flags.precision < 6)
	{
		count += ft_pad(flags.width, 0, flags);
		return (count);
	}
	if (!str)
		str = "(null)";
	if (flags.precision >= 0 && (size_t)flags.precision > ft_strlen(str))
		flags.precision = ft_strlen(str);
	if (flags.left_justify)
		count += ft_printf_s_helper(str, flags);
	if (flags.precision >= 0)
		count += ft_pad(flags.width, flags.precision, flags);
	else
		count += ft_pad(flags.width, ft_strlen(str), flags);
	if (!flags.left_justify)
		count += ft_printf_s_helper(str, flags);
	return (count);
}
