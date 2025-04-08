/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 04:45:18 by malfwa            #+#    #+#             */
/*   Updated: 2025/04/08 05:02:33 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

t_modif	*get_rule(void)
{
	static t_modif	rule;

	return (&rule);
}

int	ft_putchar(char c)
{
	if (write(1, &c, 1) < 0)
		return (-1);
	*get_nb_printed() += 1;
	return (1);
}

int	fill(int size, char c)
{
	int	i;

	i = 0;
	while (i++ < size)
		ft_putchar(c);
	return (i);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_putstr("(null)"));
	while (str && str[i])
	{
		if (ft_putchar(str[i]) < 0)
			return (-1);
		i++;
	}
	return (i);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}
