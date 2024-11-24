/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:03:41 by hboutale          #+#    #+#             */
/*   Updated: 2024/11/24 11:17:23 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	max(int n1, int n2)
{
	if (n1 > n2)
		return (n1);
	return (n2);
}
int	min(int n1, int n2)
{
	if (n1 > n2)
		return (n2);
	return (n2);
}