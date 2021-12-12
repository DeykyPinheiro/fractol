/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demikael <pinheiromikael96@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:45:49 by demikael          #+#    #+#             */
/*   Updated: 2021/12/11 20:45:51 by demikael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	reverse_point_position(const char *str)
{
	int	i;
	int	c;
	int	r;

	c = '.';
	r = 0;
	i = ft_strlen(str);
	while (str[--i])
	{
		if (str[i] == (unsigned char)c)
			return (r);
		r++;
	}
	return (0);
}

double	ft_atod(const char *nptr)
{
	size_t	i;
	int		number;
	int		signal;
	int		pot;

	number = 0;
	i = 0;
	pot = reverse_point_position(nptr);
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	signal = 1;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			signal = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]) || nptr[i] == '.')
	{
		if (nptr[i] == '.')
			i++;
		number = (nptr[i] - 48) + (number * 10);
		i++;
	}
	return (signal * (number / pow(10, pot)));
}
