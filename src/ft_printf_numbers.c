/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbrs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:36:20 by ailopez-          #+#    #+#             */
/*   Updated: 2022/05/25 19:30:49 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/ft_printf.h"

int ft_is_sign(t_params *params)
{
	return ((params->sign == '+' && params->positive) || \
		params->sign == '-' || params->gap);
}

void ft_sign_print(t_params *params)
{
	if (ft_is_sign(params))
	{
		if (params->gap && params->sign == '+')
			params->sign = ' ';
		ft_putchar_fd(params->sign, 1);
		params->chrprinted += 1;
	}
}

void	ft_print_nbr(char *num, t_params *params)
{
	if (!(params->fill == '0' && params->with > (int)ft_strlen(num) && params->precision < (int)ft_strlen(num)))
		ft_sign_print(params);
	ft_print_fill('0',params->precision - ft_strlen(num));
	ft_putstr_fd(num,1);
	if (params->precision > (int)ft_strlen(num))
		params->chrprinted += params->precision;
	else
		params->chrprinted += (int)ft_strlen(num);
}

void	ft_print_gap_pre(char *num, t_params *params)
{
	int gap;

	if(!params->leftjustify)
	{
		if (params->with > (int)ft_strlen(num))
		{
			gap = params->with - (int)ft_strlen(num) - ft_is_sign(params);
			if (params->precision > (int)ft_strlen(num))
				gap = params->with - params->precision - ft_is_sign(params);
			if(params->fill == '0')
				ft_sign_print(params);
			params->chrprinted += ft_print_fill(params->fill, gap);
		}
	}
	else
	{
		if (params->fill == '0' && params->with > (int)ft_strlen(num) && params->precision < (int)ft_strlen(num))
			ft_sign_print(params);
	}
}

void	ft_print_gap_post(char *num, t_params *params)
{
	if(params->leftjustify && params->with > params->chrprinted)
		params->chrprinted += ft_print_fill(' ', params->with - params->chrprinted);
	else
	{

	}
	num = num + 1;
}


int	ft_print_d(va_list	arg, t_params *params)
{
	char	*num;
	int		value;
	long	valueabs;

	value = va_arg(arg, int);
	valueabs = value;
	if (valueabs < 0)
		valueabs = -valueabs;
	if (value >= 0)
		params->sign = '+';
	else
		params->sign = '-';
	num = ft_uitoa((unsigned int)valueabs);
	ft_print_gap_pre(num, params);
	ft_print_nbr(num, params);
	ft_print_gap_post(num, params);
	free(num);
	return (params->chrprinted);
}

int	ft_print_u(va_list	arg, t_params *params)
{
	char	*num;

	num = ft_uitoa(va_arg(arg, unsigned int));
	params->sign = '+';
	ft_print_gap_pre(num, params);
	ft_print_nbr(num, params);
	ft_print_gap_post(num, params);
	free(num);
	return (params->chrprinted);
}

int	ft_print_x(va_list arg, t_params *params)
{
	char	*num;
	int		valor;	
	int 	len;		
	//int 	numfill;

	valor = va_arg(arg, int);
	num = ft_itoa_hex_4bytes(valor);
	if (valor == 0)
		params->altformat = 0;
	if (params->precision >= 0 && params->precision < (int)ft_strlen(num))
		params->precision = (int)ft_strlen(num);
	len = 0;
	if (params->leftjustify)
	{
		if (params->precision < 0)
			params->precision = 0;
		if(params->altformat)
			len += ft_putstr("0x");
		len += ft_print_fill('0', params->precision - ft_strlen(num));
		len += ft_putstr(num);
		len += ft_print_fill(' ', params->with - len);
	}
	else
	{
		if(params->precision >= 0)
		{
			len += ft_print_fill(' ', params->with - params->precision - 2 * params->altformat);
			if(params->altformat)
				len += ft_putstr("0x");
			len += ft_print_fill('0', params->precision - ft_strlen(num));
			len += ft_putstr(num);	
		}
		else
		{
			len += ft_print_fill(params->fill, params->with - (int)ft_strlen(num) - 2 * params->altformat);
			if(params->altformat)
				len += ft_putstr("0x");
			len += ft_putstr(num);
		}
	}
	free(num);
	return (len);

	/*
	numfill = params->with - ft_strlen(num);
	if (params->altformat && valor != 0)
			numfill = numfill - 2;	
	if (numfill < 0)
		numfill = 0;		
	if (params->leftjustify)
	{
		if(params->altformat && valor != 0)
			ft_putstr_fd("0x", 1);
		ft_putstr_fd(num, 1);
		ft_print_fill(params->fill, numfill);	
	}
	else
	{
		ft_print_fill(params->fill, numfill);
		if(params->altformat && valor != 0)
			ft_putstr_fd("0x", 1);
		ft_putstr_fd(num, 1);
	}
	len = (int)ft_strlen(num) + numfill;
	free(num);
	if(params->altformat && valor != 0)
		return (len + 2);
	return (len);
	*/
}

int	ft_print_xx(va_list arg, t_params *params)
{
	char	*num;
	int		valor;	
	int 	len;		
	int		i;
	//int 	numfill;

	valor = va_arg(arg, int);
	num = ft_itoa_hex_4bytes(valor);
	i = 0;
	while (*(num + i))
	{
		*(num + i) = ft_toupper(*(num + i));
		i++;
	}	
	if (valor == 0)
		params->altformat = 0;
	if (params->precision >= 0 && params->precision < (int)ft_strlen(num))
		params->precision = (int)ft_strlen(num);
	len = 0;
	if (params->leftjustify)
	{
		if (params->precision < 0)
			params->precision = 0;
		if(params->altformat)
			len += ft_putstr("0X");
		len += ft_print_fill('0', params->precision - ft_strlen(num));
		len += ft_putstr(num);
		len += ft_print_fill(' ', params->with - len);
	}
	else
	{
		if(params->precision >= 0)
		{
			len += ft_print_fill(' ', params->with - params->precision - 2 * params->altformat);
			if(params->altformat)
				len += ft_putstr("0X");
			len += ft_print_fill('0', params->precision - ft_strlen(num));
			len += ft_putstr(num);	
		}
		else
		{
			len += ft_print_fill(params->fill, params->with - (int)ft_strlen(num) - 2 * params->altformat);
			if(params->altformat)
				len += ft_putstr("0X");
			len += ft_putstr(num);
		}
	}
	free(num);
	return (len);


/*
	valor = va_arg(arg, int);
	num = ft_itoa_hex_4bytes(valor);
	numfill = params->with - ft_strlen(num);
	if (params->altformat && valor != 0)
			numfill = numfill - 2;	
	if (numfill < 0)
		numfill = 0;	
	i = 0;
	while (*(num + i))
	{
		*(num + i) = ft_toupper(*(num + i));
		i++;
	}
	if (params->leftjustify)
	{
		if(params->altformat && valor != 0)
			ft_putstr_fd("0X", 1);
		ft_putstr_fd(num, 1);
		ft_print_fill(params->fill, numfill);	
	}
	else
	{
		ft_print_fill(params->fill, numfill);		
		if(params->altformat && valor != 0)
			ft_putstr_fd("0X", 1);
		ft_putstr_fd(num, 1);
	}
	len = (int)ft_strlen(num) + numfill;
	free(num);
	if(params->altformat && valor != 0)
		return (len + 2);
	return (len);
	*/
}

int	ft_print_p(va_list arg, t_params *params)
{
	char	*num;
	char	*ptr;
	int 	len;

	ptr = va_arg(arg, char *);
	num = ft_itoa_hex((unsigned long)ptr);
	if (params->leftjustify)
	{
		ft_putstr_fd("0x", 1);
		ft_putstr_fd(num, 1);
		ft_print_fill(' ', params->with - ft_strlen(num) - 2);	
	}
	else
	{
		ft_print_fill(' ', params->with - ft_strlen(num) - 2);		
		ft_putstr_fd("0x", 1);
		ft_putstr_fd(num, 1);
	}
	len = (int)ft_strlen(num) + 2;
	free(num);
	if (params->with > len)
		return (params->with);
	return (len);
}
