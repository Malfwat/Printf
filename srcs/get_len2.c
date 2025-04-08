/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_len2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 02:23:14 by malfwa            #+#    #+#             */
/*   Updated: 2025/04/08 04:41:02 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	get_number(va_list ap)
{
	int	nb;

	nb = va_arg(ap, int);
	if (nb < 0)
		get_rule()->prefix = neg;
	return (nb);
}

int	arg_size(long long int nb, int base_len, char const type)
{
	int	len;

	len = (!nb);
	if (type == 'p')
		len = p_size(nb, base_len);
	else
		while (nb && ++len)
			nb /= base_len;
	return (len);
}
