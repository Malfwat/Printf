/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:46:01 by amouflet          #+#    #+#             */
/*   Updated: 2022/11/08 20:23:21 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static int	ft_is_in_set(char const *set, char c)
{
	unsigned int	i;

	i = -1;
	while (set && set[++i])
		if (c == set[i])
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	unsigned int	x;
	char			*str;

	x = 0;
	i = -1;
	while (s1 && s1[++i])
		if (ft_is_in_set(set, s1[i]) == 0)
			x++;
	str = malloc(sizeof(char) * (x + 1));
	if (str == NULL)
		return (NULL);
	str[x] = 0;
	x = 0;
	i = -1;
	while (s1 && s1[++i])
	{
		if (ft_is_in_set(set, s1[i]) == 0)
		{
			str[x] = s1[i];
			x++;
		}
	}
	return (str);
}
