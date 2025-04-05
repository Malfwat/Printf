#include <unistd.h>
#include "libftprintf.h"

t_modif	*get_rule(void)
{
	static t_modif	rule;

	return (&rule);
}

int	ft_putchar(char	c)
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
