/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:53:21 by umartin-          #+#    #+#             */
/*   Updated: 2022/12/14 21:15:12 by umartin-         ###   ########.fr       */
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

void	philo_dead(t_philo *philo, int time)
{
	int	current;

	current = get_time();
	if ((current - philo->last_meal) > philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->write_mutex);
		printf("\x1B[34m%d\x1B[0m  %d \033[1;37mdied\033[0;m 💀\n",
			time, philo->num + 1);
		exit (0);
	}
}

int	precise_usleep(int time, t_philo *philo)
{
	int	t;

	time = time * 1000;
	t = time % 100;
	time = (time / 100);
	usleep (t);
	while (time > 0)
	{
		philo_dead(philo, time_clock(philo->data->init_time));
		usleep(100);
		time--;
	}
	// printf("time at end: %d\n", time_clock(philo->data->init_time));
	// exit(0);
	return (0);
}

int	ft_write(t_philo *philo, char *str, int time)
{
	pthread_mutex_lock(&philo->data->write_mutex);
	printf("\x1B[34m%d\x1B[0m  %d %s\n", time, philo->num + 1, str);
	pthread_mutex_unlock(&philo->data->write_mutex);
	return (0);
}

int	fork_init(t_data *data)
{
	int	i;

	i = -1;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	if (!data->fork)
		return (error(("\033[0;31mMemory allocation error\033[0;31m")));
	while (++i < data->num_of_philo)
		if (pthread_mutex_init(&data->fork[i], 0) != 0)
			return (error(("\033[0;31mFork mutex init error\033[0;31m")));
	if (pthread_mutex_init(&data->dead, 0) != 0)
		return (error(("\033[0;31mDead mutex init error\033[0;31m")));
	if (pthread_mutex_init(&data->write_mutex, 0) != 0)
		return (error(("\033[0;31mWrite mutex init error\033[0;31m")));
	return (0);
}

int	data_init(t_data *data, int ac, char **av)
{
	if (ft_atoi(av[1]) == -1 || ft_atoi(av[2]) == -1 || ft_atoi(av[3]) == -1
		|| ft_atoi(av[4]) == -1)
		return (error(("\033[0;31mNumber too big\033[0;31m")));
	data->num_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		if (ft_atoi(av[5]) == -1)
			return (error(("\033[0;31mNumber too big\033[0;31m")));
		data->num_meals = ft_atoi(av[5]);
	}
	fork_init(data);
	return (0);
}

void	routine_sleep(t_philo	*philo)
{
	ft_write(philo, "is sleeping", time_clock(philo->data->init_time));
	precise_usleep(philo->data->time_to_sleep, philo);
}

void	routine_think(t_philo	*philo)
{
	ft_write(philo, "is thinking", time_clock(philo->data->init_time));
}

void	routine_eat(t_philo	*philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->left_fork]);
	ft_write(philo, "has taken a fork", time_clock(philo->data->init_time));
	pthread_mutex_lock(&philo->data->fork[philo->right_fork]);
	ft_write(philo, "has taken a fork", time_clock(philo->data->init_time));
	philo->last_meal = get_time();
	ft_write(philo, "is eating", time_clock(philo->data->init_time));
	precise_usleep(philo->data->time_to_eat, philo);
	pthread_mutex_unlock(&philo->data->fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->fork[philo->right_fork]);
}

void	*control_de_rutina(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->num % 2 == 0)
		usleep (100);
	philo->data->init_time = get_time();
	philo->last_meal = get_time();
	while (1)
	{
		routine_eat(philo);
		routine_sleep(philo);
		routine_think(philo);
	}
	return (NULL);
}

void	philo_data(t_data *data, t_philo *philo, int i)
{
	philo->num_ate = 0;
	philo->num = i;
	philo->right_fork = (i + 1) % data->num_of_philo;
	philo->left_fork = i;
	philo->data = data;
}

int	philo_init(t_data *data)
{
	int	i;

	i = -1;
	data->philo = malloc(sizeof(t_philo) * data->num_of_philo);
	if (!data->philo)
		return (error(("\033[0;31mPhilo memory allocation error\033[0;31m")));
	while (++i < data->num_of_philo)
	{
		philo_data(data, &data->philo[i], i);
		if (pthread_create(&data->philo[i].thread,
				NULL, control_de_rutina, &data->philo[i]))
			return (error(("\033[0;31mPhilo thread error\033[0;31m")));
	}
	i = -1;
	while (++i < data->num_of_philo)
		if (pthread_join(data->philo[i].thread, NULL))
			return (error(("\033[0;31mPhilo thread join error\033[0;31m")));
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if ((ac < 5 || ac > 6) || (checker (av)))
		return (error(("\033[0;31mFormato Incorrecto\033[0;31m")));
	memset(&data, 0, sizeof(data));
	if (data_init(&data, ac, av) == -1)
		return (1);
	if (fork_init(&data) == -1)
		return (1);
	if (philo_init(&data) == -1)
		return (1);
	return (0);
}
