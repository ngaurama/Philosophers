/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 09:37:59 by ngaurama          #+#    #+#             */
/*   Updated: 2024/11/08 19:09:56 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// clears a block of memory (setting to zero).
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
