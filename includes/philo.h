/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgainza- <jgainza-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 20:23:36 by jgainza-          #+#    #+#             */
/*   Updated: 2021/11/08 13:45:13 by jgainza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;
typedef struct s_info	t_info;

struct s_philo
{
	t_info			*info;
	int				n;
	int				left_fork;
	int				right_fork;
	int				meals;
	int				start;
	pthread_t		philo_th;
	pthread_t		monitor;
	pthread_mutex_t	protect;
};

struct s_info
{
	t_philo			*philo;
	int				num_philo;
	int				time_eat;
	int				time_die;
	int				time_sleep;
	int				time_must_eat;
	int				stop;
	int				base_time;
	pthread_mutex_t	status;
	pthread_mutex_t	*fork;
};

int			ft_str_error(char *str);
long long	ft_atoi(const char *s);
int			ft_get_time(void);
void		ft_print_status(t_philo *philo, int status);

void		ft_eating(t_philo *philo);
void		ft_sleeping(t_philo *philo);
void		ft_thinking(t_philo *philo);

int			ft_dining(t_info *info);

#endif
