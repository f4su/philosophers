/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgainza- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:15:15 by jgainza-          #+#    #+#             */
/*   Updated: 2021/11/08 13:41:20 by jgainza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_meal_check(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->info->num_philo)
		if (philo->info->philo[i].meals < philo->info->time_must_eat)
			return (0);
	philo->info->stop = 1;
	return (1);
}

static void	*ft_philo(void *s)
{
	t_philo	*philo;

	philo = s;
	if (philo->info->num_philo != 1 && philo->n % 2 == 0)
		usleep(1000 * philo->info->time_eat);
	while (!philo->info->stop)
	{
		ft_eating(philo);
		if ((philo->info->time_must_eat != -1 && ft_meal_check(philo))
			|| philo->info->stop || philo->info->time_must_eat == philo->meals)
			break ;
		ft_sleeping(philo);
		if (philo->info->stop)
			break ;
		ft_thinking(philo);
		if (philo->info->stop)
			break ;
	}
	return (NULL);
}

static void	*ft_monitor_life(void *s)
{
	t_philo	*philo;

	philo = s;
	while (!philo->info->stop)
	{
		pthread_mutex_lock(&philo->protect);
		if (ft_get_time() - philo->start >= philo->info->time_die)
		{
			ft_print_status(philo, 5);
			philo->info->stop = 1;
			pthread_mutex_unlock(&philo->protect);
			break ;
		}
		pthread_mutex_unlock(&philo->protect);
		usleep(100);
	}
	return (NULL);
}

int	ft_dining(t_info *info)
{
	int	i;

	info->base_time = ft_get_time();
	i = -1;
	while (++i < info->num_philo)
	{
		info->philo[i].start = ft_get_time();
		if (pthread_create(&info->philo[i].philo_th, NULL, ft_philo,
				&info->philo[i]) || pthread_create(&info->philo[i].monitor,
				NULL, ft_monitor_life, &info->philo[i]))
			return (ft_str_error("Failed to create a thread\n"));
	}
	i = -1;
	while (++i < info->num_philo)
		if (pthread_join(info->philo[i].philo_th, NULL)
			|| pthread_join(info->philo[i].monitor, NULL))
			return (ft_str_error("Failed to join a thread\n"));
	return (0);
}
