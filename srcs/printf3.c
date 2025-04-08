/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 04:45:24 by malfwa            #+#    #+#             */
/*   Updated: 2025/04/08 05:01:04 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

int	*get_nb_printed(void)
{
	static int	nb;

	return (&nb);
}

int	putstr_size(char *str, int size)
{
	int	i;

	if (!str && get_rule()->precision > 5)
		return (ft_putstr(str));
	i = 0;
	while (i < size && str && str[i])
		ft_putchar(str[i++]);
	return (i);
}

int	is_in_str(char c, char *format)
{
	int	i;

	i = 0;
	if (!format)
		return (-1);
	while (format[i])
	{
		if (format[i] == c)
			return (i + 1);
		i++;
	}
	return (0);
}

int	get_val(const char *nptr, int *i)
{
	int	sign;
	int	value;

	value = 0;
	sign = 1;
	while (nptr && (nptr[*i] <= '9' && nptr[*i] >= '0'))
	{
		value = value * 10 + nptr[*i] - 48;
		(*i)++;
	}
	return (sign * value);
}

int	biggest(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
