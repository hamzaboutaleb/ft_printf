/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:03:41 by hboutale          #+#    #+#             */
/*   Updated: 2024/11/22 13:31:08 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	max(size_t n1, size_t n2)
{
	if (n1 > n2)
		return (n1);
	return (n2);
}
size_t	min(size_t n1, size_t n2)
{
	if (n1 > n2)
		return (n2);
	return (n2);
}