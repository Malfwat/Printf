/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:08:19 by amouflet          #+#    #+#             */
/*   Updated: 2022/11/15 16:18:15 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	max_int;
	void	*ptr;
	char	*tmp;
	size_t	i;
	size_t	value_asked;

	max_int = ULONG_MAX;
	i = 0;
	value_asked = nmemb * size;
	if (nmemb > max_int / size || size > max_int / nmemb
		|| (value_asked) == 0)
		return (NULL);
	tmp = malloc((value_asked));
	if (tmp == NULL)
		return (NULL);
	while (i < value_asked)
		tmp[i++] = 0;
	ptr = tmp;
	return (ptr);
}
