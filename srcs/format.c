/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admoufle <admoufle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:16:52 by malfwa            #+#    #+#             */
/*   Updated: 2025/04/29 16:32:48 by admoufle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libftprintf.h"

int	format(char *str, va_list lst)
{
	char	modifiyer[500];

	str += get_modifiyer(modifiyer, str);
	if (!is_in_str(modifiyer[0], FORMAT))
		return (-1);
	analyse_modifiyer(modifiyer);
	get_rule()->format = *str;
	call_func(str, lst);
	return (ft_strlen(modifiyer));
}

int	get_modifiyer(char modifiyer[500], char *format_str)
{
	modifiyer[0] = format_str[0];
	modifiyer[1] = 0;
	return (1);
}
