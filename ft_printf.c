/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:05:54 by hboutale          #+#    #+#             */
/*   Updated: 2024/11/23 19:01:11 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

int	reset_flag(int op, int flag)
{
	return (op & ~flag);
}

int	collect_flags(int flags, char c)
{
	flags = 0;
	if (c == "0")
		flags = set_flag(flags, FLAG_ZERO);
	else if (c == ' ')
		flags = set_flag(flags, FLAG_SPACE);
	else if (c == '-')
		flags = set_flag(flags, FLAG_MINUS);
	else if (c == '+')
		flags = set_flag(flags, FLAG_PLUS);
	else if (c == '#')
		flags |= FLAG_HASH;
	return (flags);
}

unsigned int	get_width(t_scanner *scnr)
{
	unsigned int	result;

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
			op.flags = collect_flags(op.flags, c);
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
	// c, s ==> width 0 -
	if (op->specifier == 'c' || op->specifier == 's')
		op->flags = reset_flags(4, op->flags, FLAG_HASH, FLAG_PLUS, FLAG_SPACE);
}

int	handle_specifiers(t_scanner *scnr)
{
	t_opts	op;
	char	c;

	op = parse_format_specifier(scnr);
	if (!op.specifier)
		return (0);
	reslove_specifiers_conflict(&op);
	return (1);
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
		if (match(scnr, '%'))
			count = handle_specifiers(scnr);
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