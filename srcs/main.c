/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgainza- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 08:48:37 by jgainza-          #+#    #+#             */
/*   Updated: 2021/11/08 13:44:48 by jgainza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_fork_init(t_info *info)
{
	int	i;

	info->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* info->num_philo);
	if (!info->fork)
		return (ft_str_error("Failed to allocate memory\n"));
	i = -1;
	while (++i < info->num_philo)
		if (pthread_mutex_init(&info->fork[i], NULL))
			return (ft_str_error("Unable to perform mutex\n"));
	return (0);
}

static int	ft_info_init(t_info *info, char **argv, int argc)
{
	info->num_philo = ft_atoi(argv[1]);
	if (info->num_philo <= 0)
		return (ft_str_error("Do not test with less than 1 philosopher\n"));
	else if (info->num_philo >= 200)
		return (ft_str_error("Do not test with less than 200 philosophers\n"));
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	if (info->time_die < 60 || info->time_eat < 60 || info->time_sleep < 60)
		return (ft_str_error("Do not test with less than 60ms\n"));
	if (argc == 6)
	{
		info->time_must_eat = ft_atoi(argv[5]);
		if (info->time_must_eat <= 0)
			return (ft_str_error("Each philosopher must eat once\n"));
	}
	else
		info->time_must_eat = -1;
	info->stop = 0;
	info->base_time = 0;
	if (ft_fork_init(info))
		return (1);
	if (pthread_mutex_init(&info->status, NULL))
		return (ft_str_error("Unable to performe mutex\n"));
	return (0);
}

static int	ft_philo_init(t_info *info)
{
	int	i;

	info->philo = (t_philo *)malloc(sizeof(t_philo) * info->num_philo);
	if (!info->philo)
		return (ft_str_error("Failed to allocate memory\n"));
	i = -1;
	while (++i < info->num_philo)
	{
		info->philo[i].n = i;
		info->philo[i].left_fork = i;
		info->philo[i].right_fork = (i + 1) % info->num_philo;
		info->philo[i].meals = 0;
		info->philo[i].start = 0;
		info->philo[i].info = info;
		if (pthread_mutex_init(&info->philo[i].protect, NULL))
			return (ft_str_error("Unable to performe mutex\n"));
	}
	return (0);
}

static void	ft_free_all(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num_philo)
	{
		pthread_mutex_destroy(&info->fork[i]);
		pthread_mutex_destroy(&info->philo[i].protect);
	}
	pthread_mutex_destroy(&info->status);
	free(info->philo);
	free(info->fork);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc < 5 || argc > 6)
		return (ft_str_error("Error, incorrect number of arguments\n"));
	memset(&info, 0, sizeof(t_info));
	if (ft_info_init(&info, argv, argc))
		return (1);
	if (ft_philo_init(&info))
		return (1);
	if (ft_dining(&info))
		return (1);
	ft_free_all(&info);
	return (1);
}
