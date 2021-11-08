/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgainza- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 09:34:44 by jgainza-          #+#    #+#             */
/*   Updated: 2021/11/06 21:23:06 by jgainza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_str_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

long long	ft_atoi(const char *s)
{
	long long	num;
	long long	sign;

	while ((*s >= 9 && *s <= 13) || *s == 32)
		s++;
	sign = 1;
	if (*s == '+')
		s++;
	else if (*s == '-')
	{
		sign *= -1;
		s++;
	}
	num = 0;
	while (*s - '0' >= 0 && *s - '0' <= 9)
	{
		num *= 10;
		num += *s - '0';
		s++;
	}
	return (num * sign);
}

int	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_print_status(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->info->status);
	if (philo->info->stop)
	{
		pthread_mutex_unlock(&philo->info->status);
		return ;
	}
	printf("%d\t", ft_get_time() - philo->info->base_time);
	printf("Philo %d ", philo->n + 1);
	if (status == 1)
		printf("has taken a fork\n");
	else if (status == 2)
		printf("is eating [%d]\n", philo->meals + 1);
	else if (status == 3)
		printf("is sleeping\n");
	else if (status == 4)
		printf("is thinking\n");
	else if (status == 5)
		printf("died\n");
	pthread_mutex_unlock(&philo->info->status);
}
