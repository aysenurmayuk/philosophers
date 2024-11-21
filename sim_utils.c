/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:00:31 by amayuk            #+#    #+#             */
/*   Updated: 2024/11/21 20:19:17 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *str)
{
	int		i;
	long	sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (!str[i])
		return (0);
	while (((str[i] >= 9 && str[i] <= 13) || str[i] == 32) && str[i])
		i++;
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

int	check_arguments(char **av)
{
	int	i;
	int	j;

	i = 1;
	if (ft_atoi(av[1]) > 200)
	{
		printf("Error: invalid argument!\n");
		return (1);
	}
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				printf("Error: invalid argument!\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

size_t	get_time(void)
{
	size_t			time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	wait_time(t_philosopher *philo, size_t time)
{
	size_t	start_time;

	start_time = get_time();
	while (get_time() - start_time < time)
	{
		if (!die_or_life(philo))
			return ;
		usleep(500);
	}
}

void	write_msg(t_philosopher *philo, char *msg)
{
	static int	flag = 0;

	pthread_mutex_lock(&philo->data->mutex_need);
	if (philo[0].eat_done == 1)
	{
		pthread_mutex_unlock(&philo->data->mutex_need);
		return ;
	}
	pthread_mutex_unlock(&philo->data->mutex_need);
	pthread_mutex_lock(&philo->data->mutex_output);
	if (die_or_life(philo))
	{
		printf("%zu %d %s\n", get_time() - philo->start_time, philo->id, msg);
		pthread_mutex_unlock(&philo->data->mutex_output);
		return ;
	}
	else if (!flag)
	{
		printf("%zu %d %s\n", get_time() - philo->start_time, philo->id, msg);
		flag = 1;
	}
	pthread_mutex_unlock(&philo->data->mutex_output);
}
