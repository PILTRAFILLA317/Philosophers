/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:50:47 by umartin-          #+#    #+#             */
/*   Updated: 2022/12/15 20:39:33 by umartin-         ###   ########.fr       */
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

# define RED	"\033[0;31m"
# define GREEN	"\033[0;32m"
# define YELLOW	"\033[0;33m"
# define BLUE 	"\033[0;34m"
# define PURPLE	"\033[0;35m"
# define CYAN	"\033[0;36m"
# define BOLD	"\033[0;1m"
# define CLOSE	"\033[0;0m"
# define BHRED	"\e[1;91m"
# define BHGRN	"\e[1;92m"
# define BHBLK "\e[1;90m"
# define BHYEL "\e[1;93m"
# define BHBLU "\e[1;94m"
# define BHMAG "\e[1;95m"
# define BHCYN "\e[1;96m"
# define BHWHT "\e[1;97m"

typedef struct s_data
{
	int				num_of_philo;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				num_meals;
	int				death;
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
	int			last_meal;
	int			num_ate;
	pthread_t	thread;
	t_data		*data;
}	t_philo;

//////////////////////UTILS//////////////////////
int		checker(char **av);
int		ft_atoi(const char *str);
int		error(char *buf);
void	*control_de_rutina(void *data);
int		ft_write(t_philo *philo, char *str, int time);
int		precise_usleep(int time, t_philo *philo);
int		time_diff(struct timeval ti);
int		time_clock(int origin);
int		get_time(void);
int		philo_dead(t_philo *philo, int time);

#endif
