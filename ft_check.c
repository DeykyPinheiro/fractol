/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demikael <pinheiromikael96@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 22:15:43 by demikael          #+#    #+#             */
/*   Updated: 2021/12/12 00:26:10 by demikael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	ft_verify_true(char c)
{
	if (c == '.')
		return (1);
	if (ft_isdigit(c))
		return (1);
	return (0);
}

int	ft_verify_param(char **argv)
{
	char	*param;
	int		count;
	int		count2;
	int		i;

	count = 1;
	while (++count < 4)
	{
		i = 0;
		count2 = 0;
		param = argv[count];
		if (param[count2] == '-' || param[count2] == '+')
			count2++;
		while (param[count2])
		{
			if (param[count2] == '.')
				i++;
			if (i > 1)
				return (0);
			if (ft_verify_true(param[count2]) == 0)
				return (0);
		count2++;
		}
	}
	return (1);
}
