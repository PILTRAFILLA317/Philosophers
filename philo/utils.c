/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:46:24 by umartin-          #+#    #+#             */
/*   Updated: 2022/12/19 16:09:55 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(char *buf)
{
	printf("%s\n", buf);
	return (1);
}

int	ft_atoi(const char *str)
{
	int			c;
	int			s;
	long int	res;

	c = 0;
	s = 1;
	res = 0;
	while ((str[c] >= '\t' && str[c] <= '\r') || str[c] == ' ')
		c++;
	if (str[c] == '+' || str[c] == '-')
	{
		if (str[c] == '-')
			s *= -1;
		c++;
	}
	while (str[c] >= '0' && str[c] <= '9')
	{
		res = (str[c] - '0') + (res * 10);
		if (res * s < -2147483648)
			return (0);
		if (res * s > 2147483647)
			return (-1);
		c++;
	}
	return (res * s);
}
