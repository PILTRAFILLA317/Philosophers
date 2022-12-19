/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:06:04 by umartin-          #+#    #+#             */
/*   Updated: 2022/12/19 21:42:50 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	comp_meals(t_philo	*philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->data->completed_meals ++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
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
