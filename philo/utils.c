/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:46:24 by umartin-          #+#    #+#             */
/*   Updated: 2022/12/06 20:01:57 by umartin-         ###   ########.fr       */
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

size_t	ft_strlen(const char *str)
{
	size_t	c;

	c = 0;
	while (str[c] != '\0')
	{
		c++;
	}
	return (c);
}

int	num_checker(char *str)
{
	int	i;

	if (str[0] == '-' || str[0] == '+')
	{
		if (ft_strlen(str) == 1)
			return (1);
		i = 1;
		while (str[i] != '\0')
		{
			if (str[i] < '0' || str[i] > '9')
				return (1);
			i++;
		}
		return (0);
	}
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	checker(char **av)
{
	int	i;

	i = 0;
	while (av[++i] != NULL)
	{
		if (num_checker(av[i]))
			return (1);
	}
	return (0);
}
