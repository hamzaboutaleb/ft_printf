/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:03:41 by hboutale          #+#    #+#             */
/*   Updated: 2024/11/24 16:01:44 by hboutale         ###   ########.fr       */
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

char	*itoa(int num)
{
	int		is_negative;
	int		temp;
	int		len;
	char	*str;

	if (num < 0)
		num = -num;
	temp = num;
	len = 0;
	do
	{
		len++;
		temp /= 10;
	} while (temp);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (num == 0)
		str[--len] = '0';
	else
	{
		while (num)
		{
			str[--len] = num % 10 + '0';
			num /= 10;
		}
	}
	return (str);
}
