/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assign.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:21:55 by ngaurama          #+#    #+#             */
/*   Updated: 2025/01/29 00:54:13 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flags	ft_assign(void)
{
	t_flags	flags;

	flags.letter = 0;
	flags.left_justify = 0;
	flags.zero_padding = 0;
	flags.width = 0;
	flags.precision = -1;
	flags.hash = 0;
	flags.plus = 0;
	flags.space = 0;
	return (flags);
}
