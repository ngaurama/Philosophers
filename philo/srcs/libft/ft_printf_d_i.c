/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_d_i.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:45:00 by ngaurama          #+#    #+#             */
/*   Updated: 2024/11/13 17:41:35 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pi(char *num, int n, t_flags flags)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		if (!flags.zero_padding || flags.precision >= 0)
			count += write(1, "-", 1);
	}
	else if (flags.plus && !flags.zero_padding)
		count += write(1, "+", 1);
	else if (flags.space && !flags.zero_padding && flags.precision == -1)
		count += write(1, " ", 1);
	if (flags.precision >= 0)
	{
		flags.zero_padding = 1;
		count += ft_pad(flags.precision - 1, ft_strlen(num) - 1, flags);
	}
	count += ft_print_e(num);
	return (count);
}

int	ft_d_i_pad(int n, t_flags *flags)
{
	int	count;

	count = 0;
	if (n < 0 && flags->precision == -1)
	{
		count += write(1, "-", 1);
		flags->width--;
	}
	else if (flags->plus)
		count += write(1, "+", 1);
	else if (flags->space)
		count += write(1, " ", 1);
	return (count);
}

int	ft_printf_int(char *num, int n, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.zero_padding)
		count += ft_d_i_pad(n, &flags);
	if (flags.left_justify)
		count += ft_pi(num, n, flags);
	if (flags.precision >= 0 && (size_t)flags.precision < ft_strlen(num))
		flags.precision = ft_strlen(num);
	if (flags.precision >= 0)
	{
		flags.width -= flags.precision;
		if (n < 0 && !flags.left_justify)
			flags.width -= 1;
		count += ft_pad(flags.width, 0, flags);
	}
	else
		count += ft_pad(flags.width - flags.plus - flags.space,
				ft_strlen(num), flags);
	if (!flags.left_justify)
		count += ft_pi(num, n, flags);
	return (count);
}

void	negative_helper(t_flags *flags, long *nb)
{
	*nb *= -1;
	if (!flags->zero_padding && flags->precision == -1 && !flags->left_justify)
		flags->width--;
	if (flags->left_justify)
		flags->width--;
	flags->space = 0;
}

int	ft_printf_d_i(int n, t_flags flags)
{
	char	*num;
	long	nb;
	int		count;

	nb = n;
	count = 0;
	if (flags.precision >= 0 && flags.zero_padding)
		flags.zero_padding = 0;
	if (nb < 0)
		negative_helper(&flags, &nb);
	if (!flags.precision && !n)
	{
		count += ft_pad(flags.width, 0, flags);
		return (count);
	}
	num = ft_printf_itoa(nb);
	if (!num)
		return (0);
	count += ft_printf_int(num, n, flags);
	free(num);
	return (count);
}
