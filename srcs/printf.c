/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 04:45:13 by malfwa            #+#    #+#             */
/*   Updated: 2025/04/08 05:27:38 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdbool.h>
#include "libftprintf.h"
#include <stdio.h>

void	call_func(char *str, va_list lst)
{
	unsigned int	nb;
	int				tmp;

	tmp = is_in_str(*str, FORMAT) - 1;
	if (tmp == c)
		ft_putchar(va_arg(lst, int));
	else if (tmp == s)
		putstr_size(va_arg(lst, char *), get_rule()->precision);
	else if (tmp == p)
		print_addr(va_arg(lst, unsigned long));
	else if (tmp == d)
		ft_putnbr(va_arg(lst, int));
	else if (tmp == i)
		ft_putnbr(va_arg(lst, int));
	else if (tmp == u)
	{
		nb = va_arg(lst, unsigned int);
		if (!(!nb && get_rule()->dot && get_rule()->precision < 1))
			ft_printnbr(nb, 10, "0123456789");
	}
	else if (tmp == x || tmp == X)
		ft_puthexa(va_arg(lst, unsigned int), \
		(int []){lower, upper}[tmp - x] - 1);
	else if (tmp == percent)
		ft_putchar('%');
}

void	left_align(char *str, va_list lst, int nb_char)
{
	int	tmp;

	call_func(str, lst);
	tmp = get_rule()->width;
	tmp -= biggest(nb_char, get_rule()->precision \
	+ (get_rule()->prefix != prefix && get_rule()->prefix));
	fill(tmp, ' ');
}

void	right_align(char *str, va_list lst, int nb_char)
{
	int	tmp;

	if (get_rule()->prefix == neg && get_rule()->filling == '0')
		ft_putchar('-');
	tmp = get_rule()->width - nb_char;
	if (get_rule()->prefix == prefix)
		tmp -= 2;
	if ((*str == 'i' || *str == 'd') && get_rule()->prefix == neg)
		if (tmp == get_rule()->precision)
			tmp--;
	fill(tmp, get_rule()->filling);
	if (get_rule()->prefix == neg)
		get_rule()->prefix = none;
	call_func(str, lst);
}

int	sc(char *str, va_list lst)
{
	char	modifiyer[500];
	va_list	save;
	int		nb_char;

	str += get_modifiyer(modifiyer, str);
	analyse_modifiyer(modifiyer);
	get_rule()->format = *str;
	va_copy(save, lst);
	nb_char = mesure_arg(str, save);
	if (get_rule()->width > nb_char || (*str == 's' && nb_char < 1))
	{
		if (get_rule()->align == left)
			left_align(str, lst, nb_char);
		else
			right_align(str, lst, nb_char);
	}
	else
		call_func(str, lst);
	return (ft_strlen(modifiyer));
}

int	ft_printf(char *str, ...)
{
	va_list	lst;
	int		i;

	va_start(lst, str);
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '%')
		{
			i++;
			i += sc(&str[i], lst);
		}
		else
			ft_putchar(str[i]);
		i++;
	}
	va_end(lst);
	return (*get_nb_printed());
}
