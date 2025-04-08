/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:26:35 by amouflet          #+#    #+#             */
/*   Updated: 2022/11/10 13:12:44 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static int	find_len(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

static char	*put_at_end(char *str, unsigned int digit)
{
	char	*res;
	int		i;

	i = -1;
	if (digit > 9)
		str = put_at_end(str, digit / 10);
	if (str == NULL)
		return (NULL);
	res = malloc(sizeof(char) * (find_len(str) + 2));
	if (res == NULL)
		return (NULL);
	while (str && str[++i])
		res[i] = str[i];
	res[i] = (digit % 10) + 48;
	res[i + 1] = 0;
	free(str);
	return (res);
}

char	*ft_itoa(int n)
{
	char	*str;

	str = malloc(sizeof(*str) * 2);
	if (str == NULL)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	else
		str[0] = 0;
	str[1] = 0;
	if (n < 0)
		return (put_at_end(str, -n));
	return (put_at_end(str, n));
}
