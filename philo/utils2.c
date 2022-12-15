/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:27:13 by umartin-          #+#    #+#             */
/*   Updated: 2022/12/15 20:40:55 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(void)
{
	struct timeval	tm;

	gettimeofday(&tm, NULL);
	return (tm.tv_sec * 1000 + tm.tv_usec / 1000);
}

int	time_clock(int origin)
{
	int	current;

	current = get_time();
	return (current - origin);
}

int	time_diff(struct timeval ti)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (((current.tv_sec * 1000) + (current.tv_usec / 1000))
		- ((ti.tv_sec * 1000) + (ti.tv_usec / 1000)));
}

int	precise_usleep(int time, t_philo *philo)
{
	struct timeval	ti;

	gettimeofday(&ti, NULL);
	while (time > time_diff(ti))
	{
		if (philo_dead(philo, time_clock(philo->data->init_time)))
			return (1);
		usleep(100);
	}
	return (0);
}

int	ft_write(t_philo *philo, char *str, int time)
{
	pthread_mutex_lock(&philo->data->write_mutex);
	printf("\x1B[34m%d\x1B[0m  %d %s\n", time, philo->num + 1, str);
	pthread_mutex_unlock(&philo->data->write_mutex);
	return (0);
}
