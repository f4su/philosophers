/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgainza- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:00:08 by jgainza-          #+#    #+#             */
/*   Updated: 2021/11/06 21:23:50 by jgainza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_eating(t_philo *philo)
{
	if (philo->info->num_philo == 1)
	{
		pthread_mutex_lock(&philo->info->fork[philo->right_fork]);
		ft_print_status(philo, 1);
		while (!philo->info->stop)
			usleep(1000);
		pthread_mutex_unlock(&philo->info->fork[philo->right_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->info->fork[philo->right_fork]);
		ft_print_status(philo, 1);
		pthread_mutex_lock(&philo->info->fork[philo->left_fork]);
		ft_print_status(philo, 1);
		pthread_mutex_lock(&philo->protect);
		ft_print_status(philo, 2);
		philo->start = ft_get_time();
		pthread_mutex_unlock(&philo->protect);
		while (ft_get_time() - philo->start <= philo->info->time_eat
			&& !philo->info->stop)
			usleep(1000);
		philo->meals++;
		pthread_mutex_unlock(&philo->info->fork[philo->right_fork]);
		pthread_mutex_unlock(&philo->info->fork[philo->left_fork]);
	}
}

void	ft_sleeping(t_philo *philo)
{
	int	sleep;

	sleep = ft_get_time();
	ft_print_status(philo, 3);
	while (ft_get_time() - sleep <= philo->info->time_sleep
		&& !philo->info->stop)
		usleep(1000);
}

void	ft_thinking(t_philo *philo)
{
	ft_print_status(philo, 4);
}
