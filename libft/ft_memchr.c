/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:28:30 by malfwa            #+#    #+#             */
/*   Updated: 2022/11/15 16:17:49 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	char			a;
	unsigned char	*str;
	size_t			i;

	a = (char)c;
	str = (unsigned char *)s;
	i = -1;
	while (s && ++i < n)
		if (str[i] == a)
			return (&str[i]);
	return (NULL);
}
