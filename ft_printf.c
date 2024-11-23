/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:05:54 by hboutale          #+#    #+#             */
/*   Updated: 2024/11/23 11:34:24 by hboutale         ###   ########.fr       */
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

int	is_specifier(char c)
{
	char	*specifiers;

	specifiers = "cspdiuxX";
	return (includes(specifiers, c));
}

void	init_opts(t_opts *opts)
{
	opts->hash = FALSE;
	opts->minus = FALSE;
	opts->space = FALSE;
	opts->width = FALSE;
	opts->zero = FALSE;
}
int	handle_specifiers(t_scanner *scnr)
{
	t_opts	op;

	init_opts(&op);
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