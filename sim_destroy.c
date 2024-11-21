/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:00:20 by amayuk            #+#    #+#             */
/*   Updated: 2024/11/12 17:29:14 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	die_or_life(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->mutex_end);
	pthread_mutex_lock(&philo->data->mutex_need);
	if (philo->data->end == 1 || philo->data->philosophers[0].eat_done == 1)
	{
		pthread_mutex_unlock(&philo->data->mutex_end);
		pthread_mutex_unlock(&philo->data->mutex_need);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->mutex_need);
	pthread_mutex_unlock(&philo->data->mutex_end);
	return (1);
}

int	is_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (!is_ate(&data->philosophers[i]))
		{
			pthread_mutex_lock(&data->mutex_end);
			data->end = 1;
			pthread_mutex_unlock(&data->mutex_end);
			write_msg(data->philosophers, "dead");
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_complated_eat(t_data *data)
{
	int	i;
	int	check;

	check = 0;
	i = 0;
	if (data->required_meals == -1)
		return (1);
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->mutex_meal);
		if (data->required_meals <= data->philosophers[i].eat_count)
			check++;
		pthread_mutex_unlock(&data->mutex_meal);
		i++;
	}
	if (check == data->philo_count)
	{
		pthread_mutex_lock(&data->mutex_need);
		data->philosophers[0].eat_done = 1;
		pthread_mutex_unlock(&data->mutex_need);
		return (0);
	}
	return (1);
}

void	finish_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mutex_end);
	pthread_mutex_destroy(&data->mutex_end);
	pthread_mutex_destroy(&data->mutex_meal);
	pthread_mutex_destroy(&data->mutex_need);
}
