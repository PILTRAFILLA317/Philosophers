/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:28:59 by umartin-          #+#    #+#             */
/*   Updated: 2022/12/19 21:42:17 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_dead(t_philo *philo, int time)
{
	int	current;

	(void)time;
	current = get_time();
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->death == 1)
	{
		usleep (500);
		return (1);
	}
	if ((current - philo->last_meal) >= philo->data->time_to_die)
	{
		if (philo->data->death == 1)
		{
			usleep (500);
			pthread_mutex_unlock(&philo->data->death_mutex);
			return (1);
		}
		philo->data->death = 1;
		pthread_mutex_lock(&philo->data->write_mutex);
		printf("\x1B[34m%d\x1B[0m  %d \033[1;37mdied 💀\033[0;m\n", time, philo->num + 1);
		pthread_mutex_unlock(&philo->data->write_mutex);
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (0);
}

int	routine_sleep(t_philo	*philo)
{
	if (philo_dead(philo, time_clock(philo->data->init_time)) == 1)
		return (1);
	ft_write(philo, "is sleeping", time_clock(philo->data->init_time));
	if (precise_usleep(philo->data->time_to_eat, philo) == 1)
		return (1);
	return (0);
}

int	routine_think(t_philo	*philo)
{
	if (philo_dead(philo, time_clock(philo->data->init_time)) == 1)
		return (1);
	ft_write(philo, "is thinking", time_clock(philo->data->init_time));
	return (0);
}

int	routine_eat(t_philo	*philo)
{
	if (philo->data->completed_meals == philo->data->num_of_philo)
		return (philo->data->death = 1, 1);
	while (philo->data->fork[philo->left_fork].lck == 1)
	{
		if (philo_dead(philo, time_clock(philo->data->init_time)) == 1)
			return (1);
		usleep (100);
	}
	pthread_mutex_lock(&philo->data->fork[philo->left_fork].fork_th);
	philo->data->fork[philo->left_fork].lck = 1;
	ft_write(philo, "has taken a fork", time_clock(philo->data->init_time));
	while (philo->data->fork[philo->right_fork].lck == 1)
	{
		if (philo_dead(philo, time_clock(philo->data->init_time)) == 1)
			return (1);
		usleep (100);
	}
	pthread_mutex_lock(&philo->data->fork[philo->right_fork].fork_th);
	philo->data->fork[philo->right_fork].lck = 1;
	ft_write(philo, "has taken a fork", time_clock(philo->data->init_time));
	philo->last_meal = get_time();
	ft_write(philo, "is eating", time_clock(philo->data->init_time));
	if (precise_usleep(philo->data->time_to_eat, philo) == 1)
		return (1);
	if (philo->data->num_of_philo != -1)
		philo->num_ate ++;
	if (philo->num_ate == philo->data->num_meals)
		comp_meals(philo);
	pthread_mutex_unlock(&philo->data->fork[philo->left_fork].fork_th);
	philo->data->fork[philo->left_fork].lck = 0;
	pthread_mutex_unlock(&philo->data->fork[philo->right_fork].fork_th);
	return (philo->data->fork[philo->right_fork].lck = 0, 0);
}

void	*control_de_rutina(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->num % 2 == 0)
		usleep (philo->data->num_of_philo * 100);
	philo->last_meal = get_time();
	while (1)
	{
		if (routine_eat(philo) == 1)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			return (NULL);
		}
		if (routine_sleep(philo) == 1)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			return (NULL);
		}
		if (routine_think(philo) == 1)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			return (NULL);
		}
	}
}
