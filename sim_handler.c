/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:00:23 by amayuk            #+#    #+#             */
/*   Updated: 2024/11/12 17:29:17 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_is_eating(t_philosopher *philo)
{
	pthread_mutex_lock(philo->right_fork);
	write_msg(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	write_msg(philo, "has taken a fork");
	write_msg(philo, "is eating");
	pthread_mutex_lock(&philo->data->mutex_meal);
	philo->last_meal = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->mutex_meal);
	wait_time(philo, philo->data->time_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_is_sleeping(t_philosopher *philo)
{
	write_msg(philo, "is sleeping");
	wait_time(philo, philo->data->time_sleep);
}

void	philo_is_thinking(t_philosopher *philo)
{
	write_msg(philo, "is thinking");
	return ;
}

int	is_ate(t_philosopher *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->mutex_meal);
	time = get_time();
	if (time - philo->last_meal >= philo->data->time_die)
	{
		pthread_mutex_unlock(&philo->data->mutex_meal);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->mutex_meal);
	return (1);
}
