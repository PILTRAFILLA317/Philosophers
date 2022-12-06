/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:50:47 by umartin-          #+#    #+#             */
/*   Updated: 2022/12/06 21:09:23 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_data
{
	int				num_of_philo;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				num_meals;
	int				ate_time;
	int				stop;
	int				init_time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	dead;
	pthread_mutex_t	write_mutex;
	struct s_philo	*philo;
}	t_data;

typedef struct s_philo
{
	int			num;
	int			left_fork;
	int			right_fork;
	int			num_ate;
	pthread_t	thread;
	t_data		*data;
}	t_philo;

//////////////////////UTILS//////////////////////
int	checker(char **av);
int	ft_atoi(const char *str);
int	error(char *buf);

#endif
