#include <stdarg.h>
#include <unistd.h>
#include <stdbool.h>

#define FORMAT "cspdiuxX%"
#define FLAG "-+#0 "

enum	e_case
{
	empty,
	lower,
	upper
};

enum	e_align
{
	right = 1,
	left
};

enum	e_signed
{
	none,
	sign,
	space,
	minus
};

typedef struct	s_modif
{
	int	precision;
	int	width;
	char	filling;
	int	prefix;
	bool	dot;
	int	sign;
	int	align;
}t_modif;

int	*get_nb_printed(void)
{
	static int	nb;

	return (&nb);
}

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

int	fill(int size)
{
	int	i;

	i = 0;
	while (i++ < size)
		ft_putchar(' ');
	return (i);
}

int	ft_putstr(char *str)
{
	int	i;
	t_modif	rule;

	i = 0;
	if (!str)
		return (ft_putstr("(null)"));
	rule = *get_rule();
	while (str && str[i]/* && i != rule.precision*/)
	{
		if (ft_putchar(str[i]) < 0)
			return (-1);
		i++;
	}
	(void)rule;
	return (i);
}

int	biggest(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}

#include <stdlib.h>
#include <stdio.h>

int	ft_printnbr(unsigned long int nb, unsigned int base_len, char *base, int depth)
{
	static int	loop;
	//int	i;
	t_modif	*rule;

	rule = get_rule();
//	if (!nb && !get_rule()->precision)
//		return (fill(rule->width));
	if (/*++loop &&*/ nb >= base_len)
		ft_printnbr(nb / base_len, base_len, base, depth + 1);
	/*i = 0;
	if (rule->sign && rule->filling == '0')
	{
		if (rule->sign == minus)
			i += ft_putchar((char []){'-', ' '}[rule->sign == space]);
		else
			i += ft_putchar((char []){'+', ' '}[rule->sign == space]);
		rule->sign = none;
	}
	else if (rule->prefix && nb)
	{
		if (rule->prefix == lower)
			i += ft_putstr("0x");
		else if (rule->prefix == upper)
			i += ft_putstr("0X");
		rule->prefix = false;
	}
	if (rule->align == right)
	{
		while (i < rule->width - biggest(rule->precision, loop) - (rule->sign != 0))
			i += ft_putchar(rule->filling);
		rule->align = 0;
	}
	if (rule->sign)
	{
		i += ft_putchar((char []){'+', ' ', '-'}[rule->sign - 1]);
		rule->sign = none;
	}
	while (loop && loop < rule->precision && ++i)
	{
		i += ft_putchar('0');
		loop++;
	}
	i += */ft_putchar(base[nb % base_len]);
	/*
	if (!depth)
	{
		if (rule->align == left)
		{
			while (i <= rule->width - loop )
				i += ft_putchar(' ');
			rule->align = 0;
		}
		loop = 0;
	}*/
	return (i);
}

int	ft_puthexa(long long int nb, enum e_case casee)
{
	char	*base;

	base = (char *[]){"0123456789abcdef", "0123456789ABCDEF"}[casee];
	return (ft_printnbr(nb, 16, base, 0));
}

int	ft_putnbr(int nb)
{
	if (nb < 0)
		return (get_rule()->sign = minus, ft_printnbr(-1 * (long)nb, 10, "0123456789", 0));
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

	i = -1;
	if (!format)
		return (-1);
	while (format[++i])
		if (format[i] == c)
			return (i + 1);
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

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
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

t_modif	analyse_modifiyer(char *str)
{
	int		i;
	t_modif	rule;

	i = 0;
	rule.dot = false;
	rule.filling = 32;
	rule.precision = -1;
	rule.width = -1;
	rule.prefix = -1;
	rule.sign = none;
	rule.align = 0;
	while (str[i])
	{
		if (str[i] == '-')
			rule.align = left;
		else if (str[i] == '+')
			rule.sign = sign;
		else if (str[i] == ' ')
			rule.sign = space;
		else if (str[i] == '#')
			rule.prefix = empty;
		else if (str[i] == '0')
			rule.filling = '0';
		else if (str[i] == '.')
		{
			rule.dot = true;
			rule.filling = ' ';
		}
		else if (str[i] > '0' && str[i] <= '9')
		{
			if (rule.dot)
				rule.precision = get_val(str, &i);
			else
			{
				rule.width = get_val(str, &i);
				if (!rule.align)
					rule.align = right;
			}
			i--;
		}
		i++;
	}
	if (rule.dot && rule.precision < 0)
		rule.precision = 0;
	*get_rule() = rule;
	return (rule);
}

int	sc(char *str, va_list lst)
{
	char modifiyer[500];

	str += get_modifiyer(modifiyer, str);
	analyse_modifiyer(modifiyer);
	if (*str == 's')
		ft_putstr(va_arg(lst, char *));
	else if (*str == 'c')
		ft_putchar(va_arg(lst, int));
	else if (*str == 'i' || *str == 'd')
		ft_putnbr(va_arg(lst, int));
	else if (*str == 'u')
		ft_printnbr(va_arg(lst, unsigned int), 10, "0123456789", 0);
	else if (*str == 'x')
	{
	//	if (!get_rule()->prefix)
	//		get_rule()->prefix = lower;
		ft_puthexa(va_arg(lst, unsigned int), lower - 1);
	}
	else if (*str == 'X')
	{
	//	if (!get_rule()->prefix)
	//		get_rule()->prefix = upper;
		ft_puthexa(va_arg(lst, unsigned int), upper -1);
	}
	else if (*str == '%')
		ft_putchar('%');
	else if (*str == 'p')
		print_addr(va_arg(lst, unsigned long));
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
