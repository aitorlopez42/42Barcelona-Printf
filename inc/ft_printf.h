/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:56:02 by ailopez-          #+#    #+#             */
/*   Updated: 2022/05/24 00:19:08 by aitorlope        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

typedef	struct{
	int 	with;
	char	fill;
	int		positive;
	int		leftjustify;
	int		gap;
	int		altformat;
	int 	precision;
	char	type;
} t_params;

# include "libft.h"
# include <stdarg.h>
# include <string.h>
# include <stdio.h> 
# include <stdlib.h>
# include <unistd.h>

int		ft_printf(const char *params, ...);
int		ft_print_c (va_list	arg);
int		ft_print_s(va_list arg);
int		ft_print_d(va_list arg);
int		ft_print_u(va_list  arg);
char	*ft_uitoa(unsigned int n);
int		ft_print_x(va_list arg);
int		ft_print_X(va_list arg);
char	*ft_itoa_hex(unsigned long n);
int		ft_print_p(va_list arg);
#endif
