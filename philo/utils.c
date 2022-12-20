/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:46:24 by umartin-          #+#    #+#             */
/*   Updated: 2022/12/20 16:09:11 by umartin-         ###   ########.fr       */
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

int	philo_dead(t_philo *philo, int time)
{
	int	current;

	(void)time;
	current = get_time();
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->death == 1)
	{
		usleep (500);
		pthread_mutex_unlock(&philo->data->fork[philo->left_fork].fork_th);
		pthread_mutex_unlock(&philo->data->fork[philo->right_fork].fork_th);
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	if ((current - philo->last_meal) >= philo->data->time_to_die)
	{
		philo->data->death = 1;
		pthread_mutex_unlock(&philo->data->fork[philo->left_fork].fork_th);
		pthread_mutex_unlock(&philo->data->fork[philo->right_fork].fork_th);
		printf("\x1B[34m%d\x1B[0m  %d \033[1;37mdied 💀\033[0;m\n",
			time, philo->num + 1);
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (0);
}

void	control_de_rutina_utils(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->death_mutex);
	pthread_mutex_unlock(&philo->data->write_mutex);
}
