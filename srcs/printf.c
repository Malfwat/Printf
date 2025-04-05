#include <stdarg.h>
#include <unistd.h>
#include <stdbool.h>
#include "libftprintf.h"
#include <stdio.h>

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

int	ft_printnbr(unsigned long int nb, unsigned int base_len, char *base)
{
	static int	loop;
	int		size;

	if (++loop && nb >= base_len)
		ft_printnbr(nb / base_len, base_len, base);
	if (loop)
	{
		size = get_rule()->precision - loop;

		fill(size, '0');
		loop = 0;
	}
	ft_putchar(base[nb % base_len]);
	return (0);
}

int	ft_puthexa(long long int nb, enum e_case casee)
{
	char	*base;

	if (get_rule()->dot && !nb && get_rule()->precision < 1)
		return (0);
	if (get_rule()->prefix == prefix && nb)
	{
		ft_putchar('0');
		ft_putchar((char []){'x', 'X'}[casee]);
	}
	base = (char *[]){"0123456789abcdef", "0123456789ABCDEF"}[casee];
	return (ft_printnbr(nb, 16, base));
}

int	ft_putnbr(int nb)
{
	if (get_rule()->dot && !nb && get_rule()->precision < 1)
		return (0);
	if (nb < 0)
	{
		if (get_rule()->filling == ' ' || get_rule()->prefix == neg)
			ft_putchar('-');
		return (ft_printnbr(-1 * (long)nb, 10, "0123456789"));
	}
	switch (get_rule()->prefix)
	{
		case (wspace):
			ft_putchar(' ');
			break ;
		case (pos):
			ft_putchar('+');
		default:
			break;
	}
	return (ft_printnbr(nb, 10, "0123456789"));
}

void	print_addr(unsigned long addr)
{
	if (!addr)
		return ((void)ft_putstr("(nil)"));
	ft_putstr("0x");
	ft_puthexa(addr, lower - 1);
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

int	get_modifiyer(char modifiyer[500], char *format)
{
	int	i;

	i = 0;
	while (!is_in_str(format[i], FORMAT))
	{
		modifiyer[i] = format[i];
		i++;
	}
	modifiyer[i] = 0;
	return (i);
}



static int	get_val(const char *nptr, int *i)
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

t_modif	initialize_t_modif(void)
{
	t_modif	new;

	new.dot = false;
	new.filling = 32;
	new.precision = -1;
	new.width = -1;
	new.prefix = none;
	new.align = 0;
	return (new);
}

void	get_sizes(t_modif *rule, char const *str, int *i)
{
	if (str[*i] >= '0' && str[*i] <= '9')
	{
		if (rule->dot)
			rule->precision = get_val(str, i);
		else
		{
			rule->width = get_val(str, i);
			if (!rule->align)
				rule->align = right;
		}
		(*i)--;
	}
}

t_modif	analyse_modifiyer(char const *str)
{
	t_modif	rule;
	int		i;

	i = 0;
	rule = initialize_t_modif();
	while (str[i])
	{
		switch (is_in_str(str[i], FLAG) - 1)
		{
			case (minus):
				rule.align = left;
				break ;
			case (plus):
				rule.prefix = pos;
				break ;
			case (space):
				rule.prefix = wspace;
				break ;
			case (hash):
				rule.prefix = prefix;
				break ;
			case (zero):
				if (!rule.dot)
					rule.filling = '0';
				else
					get_sizes(&rule, str, &i);
				break ;
			case (dot):
				rule.dot = true;
				rule.filling = ' ';
				break ;
			default:
				get_sizes(&rule, str, &i);
		}
		i++;
	}
	*get_rule() = rule;
	return (rule);
}


int	mesure_arg(char const *str, va_list lst)
{
	switch (is_in_str(*str, FORMAT) - 1)
	{
		case (c):
			return (1);
		case (s):
			return (s_len(lst, 's'));
		case (p):
			return (get_len('p', va_arg(lst, unsigned long)) + 2);
		case (d):
			return (i_len(lst, 'n'));
		case (i):
			return (i_len(lst, 'n'));
		case (u):
			return (ui_len(lst, 'u'));
		case (x):
			return (ui_len(lst, 'x'));
		case (X):
			return (ui_len(lst, 'x'));
		case (percent):
			return (1);
	}
	return (-1);
}


void	call_func(char *str, va_list lst)
{
	unsigned int	nb;

	switch (is_in_str(*str, FORMAT) - 1)
	{
		case (c):
			ft_putchar(va_arg(lst, int));
			break ;
		case (s):
			putstr_size(va_arg(lst, char *), get_rule()->precision);
			break ;
		case (p):
			print_addr(va_arg(lst, unsigned long));
			break ;
		case (d):
			ft_putnbr(va_arg(lst, int));
			break ;
		case (i):
			ft_putnbr(va_arg(lst, int));
			break ;
		case (u):
			nb = va_arg(lst, unsigned int);
			if (!(!nb && get_rule()->dot && get_rule()->precision < 1))
				ft_printnbr(nb, 10, "0123456789");
			break ;
		case (x):
			ft_puthexa(va_arg(lst, unsigned int), lower - 1);
			break ;
		case (X):
			ft_puthexa(va_arg(lst, unsigned int), upper -1);
			break ;
		case (percent):
			ft_putchar('%');
	}
}

int	biggest(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	sc(char *str, va_list lst)
{
	char modifiyer[500];
	va_list	save;
	int	nb_char;
	int	tmp;

	str += get_modifiyer(modifiyer, str);
	analyse_modifiyer(modifiyer);
	get_rule()->format = *str;
	va_copy(save, lst);
	// utiliser la copy pour avoir la taille de l'argument a venir;
	nb_char = mesure_arg(str, save);
	if (get_rule()->width > nb_char || (*str == 's' && nb_char < 1))
	{
		if (get_rule()->align == left)
		{
			call_func(str, lst);
			tmp = get_rule()->width;
			tmp -= biggest(nb_char, get_rule()->precision + (get_rule()->prefix != prefix && get_rule()->prefix));
			fill(tmp, ' ');
		}
		else
		{
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
	}
	else
		call_func(str, lst);
	// ensuite si besoin (width) fill le nb  d'espace necessaire 
	// sinon print et si - remplir
	return (ft_strlen(modifiyer));
}

int	ft_printf(char *str, ...)
{
	va_list	lst;
	int	i;

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
