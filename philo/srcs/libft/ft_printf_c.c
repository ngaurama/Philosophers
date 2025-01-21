/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:26:05 by ngaurama          #+#    #+#             */
/*   Updated: 2024/11/13 17:16:44 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_c(char c, t_flags flags)
{
	int	count;

	count = 0;
	flags.zero_padding = 0;
	if (flags.left_justify)
		count += write(1, &c, 1);
	if (flags.letter != '%')
		count += ft_pad(flags.width, 1, flags);
	if (!flags.left_justify)
		count += write(1, &c, 1);
	return (count);
}
