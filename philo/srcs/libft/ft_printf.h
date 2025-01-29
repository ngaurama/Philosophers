/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:37:52 by ngaurama          #+#    #+#             */
/*   Updated: 2025/01/29 00:54:13 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ft_printf_H
# define ft_printf_H

// All includes
# include "libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// flags
typedef struct s_flags
{
	int	letter;
	int	left_justify;
	int	zero_padding;
	int	width;
	int	precision;
	int	hash;
	int	plus;
	int	space;
}		t_flags;

// ft_printf and handlers
int		ft_printf(const char *format, ...);
int		handler(char const *format, va_list args);
int		ft_handle_flags(char const *format, int shift, t_flags *flags);
int		ft_result(char letter, va_list args, t_flags flags);

// ft_printf letter's main functions
int		ft_printf_c(char c, t_flags flags);
int		ft_printf_s(char const *str, t_flags flags);
int		ft_printf_p(unsigned long n, t_flags flags);
int		ft_printf_d_i(int n, t_flags flags);
int		ft_printf_u(unsigned n, t_flags flags);
int		ft_printf_x(unsigned int n, t_flags flags, int big);

// Flag Helper Functions
int		ft_pad(int len, int shift, t_flags flags);
int		ft_precision(char const *format, int shift, t_flags *flags);
int		is_flag(int c);
int		is_letter(int c);
int		ft_conditions(int c);

// Random specific function helpers either for norminette or efficiency
int		ft_printf_s_helper(char const *str, t_flags flags);

// ft_printf_d_i helpers
size_t	ft_itoa_len(long num);
char	*ft_printf_itoa(long num);
char	*ft_num_to_str(long num, char *str, size_t len);
int		ft_printf_int(char *num, int n, t_flags flags);
int		ft_d_i_pad(int n, t_flags *flags);
int		ft_pi(char *num, int n, t_flags flags);

// ft_printf_p helpers
int		ft_add(unsigned long n);
int		ft_ptr(unsigned long n);
int		ft_plen(unsigned long n);

// ft_printf_u helpers
size_t	ft_utoa_len(long num);
char	*ft_u_to_str(unsigned int num, char *str, size_t len);
char	*ft_printf_utoa(unsigned int num);

// ft_printf_x helpers
size_t	ft_hextoa_len(long num);
char	*ft_hex_to_str(unsigned long int num, char *str, size_t len);
char	*ft_hextoa(unsigned long int num, int is_upper);
int		ft_bigger(int bigger);
int		ft_phex_helper(char *num, int n, t_flags flags, int bigger);

// Assign && random
t_flags	ft_assign(void);
int		ft_print_e(const char *str);
void	ft_hyphen(t_flags *flags);

#endif

/*
| Flag        | `%c` | `%s` | `%p` | `%d` | `%i` | `%u` | `%x` | `%X` |
|-------------|------|------|------|------|------|------|------|------|
| **`-`**     | Yes  | Yes  | Yes  | Yes  | Yes  | Yes  | Yes  | Yes  |
| **`0`**     | No   | No   | No   | Yes  | Yes  | Yes  | Yes  | Yes  |
| **`.`**     | No   | Yes  | Yes  | Yes  | Yes  | Yes  | Yes  | Yes  |
| **Width**   | Yes  | Yes  | Yes  | Yes  | Yes  | Yes  | Yes  | Yes  |
| **`#`**     | No   | No   | Yes  | Yes  | Yes  | No   | Yes  | Yes  |
| **`+`**     | No   | No   | No   | Yes  | Yes  | No   | No   | No   |
| **` `**     | No   | No   | No   | Yes  | Yes  | No   | No   | No   |
*/