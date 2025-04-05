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

int	get_len(char const type, ...)
{
	va_list	ap;
	int	len;
	int	base_len;
	long long int	nb;
	char *str;

	va_start(ap, type);
	nb = 0;
	if (type == 's')
	{
		str = va_arg(ap, char *);
		return ((int []){ft_strlen(str), 6}[!str]);
	}
	else
	{
		base_len = 10;
		if (type == 'n')
		{
			nb = va_arg(ap, int);
			if (nb < 0)
				get_rule()->prefix = neg;
		}
		else if (type == 'u')
			nb = (long int)va_arg(ap, unsigned int);
		else
		{
			nb = (long int)va_arg(ap, unsigned int);
			base_len = 16;
			if (type == 'p' && !nb)
				return (va_end(ap), 3);
		}
		if (get_rule()->dot && get_rule()->precision < 0 && !nb)
			return (va_end(ap), 0);
		len = 0;
		if (!nb)
			len = 1;
		while (nb && ++len)
			nb /= base_len;
	}
	va_end(ap);
	len += ((get_rule()->prefix != prefix ) && get_rule()->prefix);
	return (len);
}

#include <stdio.h>

int	ft_printnbr(unsigned long int nb, unsigned int base_len, char *base, int depth)
{
	static int	loop;
	int		size;

	if (++loop && nb >= base_len)
		ft_printnbr(nb / base_len, base_len, base, depth + 1);
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

	if (get_rule()->dot && !nb)
	if (get_rule()->prefix == prefix && nb)
	{
		ft_putchar('0');
		ft_putchar((char []){'x', 'X'}[casee]);
	}
	base = (char *[]){"0123456789abcdef", "0123456789ABCDEF"}[casee];
	return (ft_printnbr(nb, 16, base, 0));
}

int	ft_putnbr(int nb)
{
	if (get_rule()->dot && !nb && get_rule()->precision < 1)
		return (0);
	if (nb < 0)
	{
		if (get_rule()->filling == ' ')
			ft_putchar('-');
		return (ft_printnbr(-1 * (long)nb, 10, "0123456789", 0));
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
	return (ft_printnbr(nb, 10, "0123456789", 0));
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
//	if (rule.dot && rule.precision < 0)
//		rule.precision = 0;
	*get_rule() = rule;
	return (rule);
}


int	mesure_arg(char const *str, va_list lst)
{
	int	len;

	switch (is_in_str(*str, FORMAT) - 1)
	{
		case (c):
			return (1);
		case (s):
			len = get_len('s', va_arg(lst, char *));
			if (get_rule()->precision < len && get_rule()->precision != -1)
				len = get_rule()->precision;
			else if (get_rule()->precision == -1 && !get_rule()->dot)
				get_rule()->precision = len;
			else if (get_rule()->dot && get_rule()->precision < 1)
				len = 0;
			return (len);
		case (p):
			return (get_len('p', va_arg(lst, unsigned long)) + 2);
		case (d):
			len = get_len('n', va_arg(lst, int));
			if (get_rule()->precision > len)
				len = get_rule()->precision;
			return (len);
		case (i):
			len = get_len('n', va_arg(lst, int));
			if (get_rule()->precision > len)
				len = get_rule()->precision;
			return (len);
		case (u):
			len = get_len('u', va_arg(lst, unsigned int));
			if (get_rule()->precision > len)
				len = get_rule()->precision;
			return (len);
		case (x):
			len = get_len('x', va_arg(lst, unsigned int));
			if (get_rule()->precision > len)
				len = get_rule()->precision;
			return (len);
		case (X):
			len = get_len('x', va_arg(lst, unsigned int));
			if (get_rule()->precision > len)
				len = get_rule()->precision;
			return (len);
		case (percent):
			return (1);
	}
	//prendre en compte l'ajout d'espace et de plus pour mesurer la taille .
	return (-1);
}


void	call_func(char *str, va_list lst)
{
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
			ft_printnbr(va_arg(lst, unsigned int), 10, "0123456789", 0);
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
//			if (nb_char)
				call_func(str, lst);
			fill(get_rule()->width - biggest(nb_char, get_rule()->precision + (get_rule()->prefix != prefix && get_rule()->prefix)), ' ');
		}
		else
		{
			if (get_rule()->prefix == neg && get_rule()->filling == '0')
				ft_putchar('-');
			fill(get_rule()->width - nb_char, get_rule()->filling);
//			if (nb_char)
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
