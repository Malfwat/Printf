#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdbool.h>
# include <stdarg.h>

# define FORMAT "cspdiuxX%"
# define FLAG "-+ #0."

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
	wspace,
	pos,
	neg,
	prefix
};

enum	e_format
{
	c,
	s,
	p,
	d,
	i,
	u,
	x,
	X,
	percent
};

enum	e_flag
{
	minus,
	plus,
	space,
	hash,
	zero,
	dot
};

typedef struct	s_modif
{
	char	format;
	int	precision;
	int	width;
	char	filling;
	enum e_signed	prefix;
	bool	dot;
	int	align;
}t_modif;

t_modif	*get_rule(void);
int	*get_nb_printed(void);
int	ft_putchar(char c);
int	ft_putstr(char *str);
int	ft_strlen(char *str);
int	fill(int size, char c);
int	putstr_size(char *str, int size);
int	ui_len(va_list lst, char const type);
int	i_len(va_list lst, char const type);
int	s_len(va_list lst, char const type);
int	get_len(char const type, ...);
int	printf(char *format, ...) __attribute__((format(printf, 1, 2)));


#endif /*LIBFTPRINTF_H*/
