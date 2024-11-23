/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 09:55:28 by hboutale          #+#    #+#             */
/*   Updated: 2024/11/23 10:30:45 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_scanner	*create_scanner(const char *s)
{
	t_scanner	*scanner;

	scanner = malloc(sizeof(t_scanner));
	if (!scanner)
		return (NULL);
	scanner->s = s;
	scanner->len = ft_strlen(s);
	scanner->cursor = 0;
	return (scanner);
}

t_bool	match(t_scanner *scn, char c)
{
	if (is_at_end(scn))
		return (FALSE);
	if (peek(scn) != c)
		return (FALSE);
	scn->cursor++;
	return (TRUE);
}

char	advance(t_scanner *scn)
{
	char	c;

	if (is_at_end(scn))
		return ('\0');
	c = peek(scn);
	scn->cursor++;
	return (c);
}

char	peek(t_scanner *scn)
{
	if (is_at_end(scn))
		return ('\0');
	return (scn->s[scn->cursor]);
}

t_bool	is_at_end(t_scanner *scn)
{
	return (scn->cursor >= scn->len);
}