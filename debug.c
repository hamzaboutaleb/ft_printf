/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:21:20 by hboutale          #+#    #+#             */
/*   Updated: 2024/11/24 13:03:01 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * unsigned int	width;
	int				flags;
	char			specifier;
 */
/**
 * # define FLAG_MINUS 1 << 0
#define FLAG_PLUS 1 << 1
#define FLAG_SPACE 1 << 2
#define FLAG_ZERO 1 << 3
#define FLAG_HASH 1 << 4

 */
void	debug_flags(t_opts *op)
{
	printf("width: %d\n", op->width);
	printf("specifier: %c\n", op->specifier);
	printf("flags PLUS: %d\nSPACE: %d\nZERO: %d\nHASH: %d\nMINUS: %d\n",
		op->flags & FLAG_PLUS, op->flags & FLAG_SPACE, op->flags & FLAG_ZERO,
		op->flags & FLAG_HASH, op->flags & FLAG_MINUS);
}