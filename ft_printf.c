/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:05:54 by hboutale          #+#    #+#             */
/*   Updated: 2024/11/24 17:58:19 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *str)
{
	int	count;

	count = 0;
	while (str[count])
	{
		count += ft_putchar(str[count]);
	}
	return (count);
}

int	includes(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

int	is_number(char c)
{
	return (c >= '1' && c <= '9');
}

int	is_flag(char c)
{
	char	*flags;

	flags = "0 -+#";
	return (includes(flags, c));
}

int	is_specifier(char c)
{
	char	*specifiers;

	specifiers = "cspdiuxX";
	return (includes(specifiers, c));
}
void	init_opts(t_opts *opts)
{
	opts->flags = 0;
	opts->width = 0;
	opts->specifier = 0;
}

int	set_flag(int op, int flag)
{
	return (op | flag);
}

t_bool	is_set(int op, int flag)
{
	return (op & flag);
}

int	reset_flag(int op, int flag)
{
	return (op & ~flag);
}

int	reset_flags(int count, ...)
{
	va_list	ap;
	int		flags;
	int		i;

	va_start(ap, count);
	flags = va_arg(ap, int);
	i = 0;
	while (i < count - 1)
	{
		flags = reset_flag(flags, va_arg(ap, int));
		i++;
	}
	return (flags);
}

int	collect_flags(int flags, char c)
{
	if (c == '0')
		flags = set_flag(flags, FLAG_ZERO);
	else if (c == ' ')
		flags = set_flag(flags, FLAG_SPACE);
	else if (c == '-')
		flags = set_flag(flags, FLAG_MINUS);
	else if (c == '+')
		flags = set_flag(flags, FLAG_PLUS);
	else if (c == '#')
		flags = set_flag(flags, FLAG_HASH);
	return (flags);
}

unsigned int	get_width(t_scanner *scnr)
{
	unsigned int	result;

	result = 0;
	scnr->cursor--;
	while (peek(scnr) >= '0' && peek(scnr) <= '9')
	{
		result = result * 10 + peek(scnr) - '0';
		scnr->cursor++;
	}
	return (result);
}

t_opts	parse_format_specifier(t_scanner *scnr)
{
	t_opts	op;
	char	c;

	init_opts(&op);
	while (!is_at_end(scnr))
	{
		c = advance(scnr);
		if (is_flag(c))
		{
			op.flags = collect_flags(op.flags, c);
		}
		else if (is_number(c))
			op.width = get_width(scnr);
		else
		{
			op.specifier = c;
			return (op);
		}
	}
	return (op);
}

void	reslove_specifiers_conflict(t_opts *op)
{
	if (is_set(op->flags, FLAG_MINUS))
		op->flags = reset_flag(op->flags, FLAG_ZERO);
	if (is_set(op->flags, FLAG_PLUS))
		op->flags = reset_flag(op->flags, FLAG_SPACE);
	if (!is_specifier(op->specifier))
	{
		op->flags = reset_flags(4, op->flags, FLAG_PLUS, FLAG_SPACE, FLAG_HASH);
		return ;
	}
	if (op->specifier == 'c' || op->specifier == 's' || op->specifier == 'u')
		op->flags = reset_flags(4, op->flags, FLAG_HASH, FLAG_PLUS, FLAG_SPACE);
	if (op->specifier != 'x' && op->specifier != 'X')
		op->flags = reset_flags(2, op->flags, FLAG_HASH);
}

int	print_char_n_time(char c, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		ft_putchar(c);
		i++;
	}
	return (n);
}

int	handle_c(t_opts *op, char c)
{
	char	char_fill;
	int		diff;
	int		count;

	char_fill = ' ';
	count = 0;
	if (is_set(op->flags, FLAG_ZERO))
		char_fill = '0';
	diff = max(op->width - 1, 0);
	if (diff == 0)
		return (ft_putchar(c));
	if (!is_set(op->flags, FLAG_MINUS))
	{
		count += print_char_n_time(char_fill, diff);
		count += ft_putchar(c);
	}
	else
	{
		count += ft_putchar(c);
		count += print_char_n_time(char_fill, diff);
	}
	return (count);
}

int	handle_s(t_opts *op, char *s)
{
	char	char_fill;
	int		diff;
	int		count;

	char_fill = ' ';
	count = 0;
	if (is_set(op->flags, FLAG_ZERO))
		char_fill = '0';
	diff = max(op->width - (int)ft_strlen(s), 0);
	if (diff == 0)
		return (ft_putstr(s));
	if (!is_set(op->flags, FLAG_MINUS))
	{
		count += print_char_n_time(char_fill, diff);
		count += ft_putstr(s);
	}
	else
	{
		count += ft_putstr(s);
		count += print_char_n_time(char_fill, diff);
	}
	return (count);
}

char	*ultohexa(unsigned long int num)
{
	char				*result;
	unsigned long int	temp;
	int					len;
	int					digit;

	if (num == 0)
		return (ft_strdup("0"));
	temp = num;
	len = 0;
	while (temp > 0)
	{
		temp >>= 4;
		len++;
	}
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	result[len] = '\0';
	while (num > 0)
	{
		digit = num & 0xF;
		result[--len] = digit < 10 ? digit + '0' : digit - 10 + 'a';
		num >>= 4;
	}
	return (result);
}

int	handle_p(t_opts *op, size_t ptr)
{
	char	*num;
	char	char_fill;
	int		diff;
	int		count;

	num = ultohexa(ptr); // wihtout 0x
	char_fill = ' ';
	count = 0;
	if (is_set(op->flags, FLAG_ZERO))
		char_fill = '0';
	diff = max(op->width - ((int)ft_strlen(num) + 2), 0); // 2 for 0x
	if (diff == 0)
		count = (ft_putstr("0x") + ft_putstr(num));
	else if (!is_set(op->flags, FLAG_MINUS))
	{
		count += print_char_n_time(char_fill, diff);
		count += ft_putstr("0x") + ft_putstr(num);
	}
	else
	{
		count += ft_putstr("0x") + ft_putstr(num);
		count += print_char_n_time(char_fill, diff);
	}
	free(num);
	return (count);
}
int	ft_putsign(t_opts *op, int num)
{
	if (num < 0)
		return (ft_putchar('-'));
	if (is_set(op->flags, FLAG_PLUS))
		return (ft_putchar('+'));
	if (is_set(op->flags, FLAG_SPACE))
		return (ft_putchar(' '));
	return (0);
}
int	handle_number(t_opts *op, int n)
{
	char	*num;
	char	char_fill;
	int		diff;
	int		count;
	int		sign;

	num = itoa(n);
	char_fill = ' ';
	count = 0;
	sign = 0;
	if (n < 0 || is_set(op->flags, FLAG_PLUS) || is_set(op->flags, FLAG_SPACE))
		sign = 1;
	if (is_set(op->flags, FLAG_ZERO))
		char_fill = '0';
	diff = max(op->width - ((int)ft_strlen(num) + sign), 0); // 2 for 0x
	if (diff == 0)
		count = (ft_putstr(num));
	else if (!is_set(op->flags, FLAG_MINUS))
	{
		count += ft_putsign(op, n) + print_char_n_time(char_fill, diff);
		count += ft_putstr(num);
	}
	else
	{
		count += ft_putsign(op, n) + ft_putstr(num);
		count += print_char_n_time(char_fill, diff);
	}
	free(num);
	return (count);
}

char	*uint_to_str(unsigned int num)
{
	char			*result;
	unsigned int	temp;
	int				length;
	int				i;

	// Handle special case of 0
	if (num == 0)
	{
		result = (char *)malloc(2);
		if (result == NULL)
			return (NULL);
		result[0] = '0';
		result[1] = '\0';
		return (result);
	}
	// Count digits
	temp = num;
	length = 0;
	while (temp > 0)
	{
		length++;
		temp /= 10;
	}
	// Allocate memory for string (length + 1 for null terminator)
	result = (char *)malloc(length + 1);
	if (result == NULL)
		return (NULL);
	// Add null terminator
	result[length] = '\0';
	// Convert digits from right to left
	i = length - 1;
	while (num > 0)
	{
		result[i] = '0' + (num % 10);
		num /= 10;
		i--;
	}
	return (result);
}

int	handle_u(t_opts *op, unsigned int n)
{
	char	char_fill;
	int		diff;
	int		count;
	char	*num;

	char_fill = ' ';
	count = 0;
	num = uint_to_str(n);
	 if (is_set(op->flags, FLAG_ZERO)) char_fill = '0';
	diff = max(op->width - (int)ft_strlen(num), 0);
	if (diff == 0)
		return (ft_putstr(num));
	if (!is_set(op->flags, FLAG_MINUS))
	{
		count += print_char_n_time(char_fill, diff);
		count += ft_putstr(num);
	}
	else
	{
		count += ft_putstr(num);
		count += print_char_n_time(char_fill, diff);
	}
	return (count);
}

int	execute_specifer(t_opts *op, va_list *ap)
{
	int		count;
	char	specifier;

	specifier = op->specifier;
	if (specifier == 'c')
		return (handle_c(op, va_arg(*ap, int)));
	if (specifier == 's')
		return (handle_s(op, va_arg(*ap, char *)));
	if (specifier == 'p')
		return (handle_p(op, (size_t)va_arg(*ap, void *)));
	if (specifier == 'd' || specifier == 'i')
		return (handle_number(op, va_arg(*ap, int)));
	if (specifier == 'u')
		return (handle_u(op, va_arg(*ap, unsigned int)));
	return (0);
}

int	handle_specifiers(t_scanner *scnr, va_list *ap)
{
	t_opts	op;
	char	c;

	op = parse_format_specifier(scnr);
	if (!op.specifier)
		return (0);
	reslove_specifiers_conflict(&op);
	return (execute_specifer(&op, ap));
}
int	process_format(t_scanner *scnr, va_list *ap)
{
	int		bytes_written;
	int		count;
	char	c;

	bytes_written = 0;
	while (!is_at_end(scnr))
	{
		c = advance(scnr);
		if (c == '%')
		{
			count = handle_specifiers(scnr, ap);
		}
		else
			count = ft_putchar(c);
		if (count == -1)
			return (-1);
		bytes_written += count;
	}
	return (bytes_written);
}

int	ft_printf(const char *format, ...)
{
	va_list ap;
	t_scanner *scnr;
	int bytes_written;

	va_start(ap, format);

	scnr = create_scanner(format);
	if (!scnr)
		return (-1);

	bytes_written = process_format(scnr, &ap);
	free(scnr);
	return (bytes_written);
}