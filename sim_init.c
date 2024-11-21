/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:00:26 by amayuk            #+#    #+#             */
/*   Updated: 2024/11/12 17:29:20 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_data *data)
{
	pthread_mutex_init(&data->mutex_end, NULL);
	pthread_mutex_init(&data->mutex_output, NULL);
	pthread_mutex_init(&data->mutex_meal, NULL);
	pthread_mutex_init(&data->mutex_need, NULL);
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].eat_count = 0;
		data->philosophers[i].start_time = get_time();
		data->philosophers[i].last_meal = get_time();
		data->philosophers[i].left_fork = &data->forks[i];
		data->philosophers[i].eat_done = 0;
		data->philosophers[i].data = data;
		if (i == 0)
			data->philosophers[i].right_fork = &data->forks[data->philo_count
				- 1];
		else
			data->philosophers[i].right_fork = &data->forks[i - 1];
		i++;
	}
	return (0);
}

int	init_data(t_data *data, char **av)
{
	data->philo_count = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	if (av[5])
		data->required_meals = ft_atoi(av[5]);
	else
		data->required_meals = -1;
	data->end = 0;
	return (0);
}
