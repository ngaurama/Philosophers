/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:36:00 by ngaurama          #+#    #+#             */
/*   Updated: 2024/11/20 18:38:33 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_e(const char *str)
{
	int	count;

	count = 0;
	if (!str)
	{
		return (count += write(1, "(null)", 6));
	}
	count = 0;
	while (str[count])
		count++;
	write(1, str, count);
	return (count);
}

void	ft_hyphen(t_flags *flags)
{
	flags->left_justify = 1;
	flags->zero_padding = 0;
}
