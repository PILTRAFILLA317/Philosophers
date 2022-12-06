/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:53:21 by umartin-          #+#    #+#             */
/*   Updated: 2022/12/06 21:31:30 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	*control_de_rutina(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	printf("Rutina controlada ID: %d\n", philo->num);
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
	while (++i < data->num_of_philo)
		if (pthread_join(&data->philo[i].thread, NULL))
			return (error(("\033[0;31mPhilo thread join error\033[0;31m")));
	i = -1;
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
