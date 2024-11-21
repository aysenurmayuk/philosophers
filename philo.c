/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:00:17 by amayuk            #+#    #+#             */
/*   Updated: 2024/11/21 20:19:38 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	terminate_simulation(t_data *data)
{
	while (1)
	{
		if (!is_dead(data) || !is_complated_eat(data))
			break ;
	}
}

int	philo_handler_helper(t_data *data, int i)
{
	if (data->philo_count == 1)
	{
		if (pthread_detach(data->philosophers[i].thread))
		{
			printf("Error: pthread_detach failed.\n");
			return (1);
		}
	}
	else
	{
		if (pthread_join(data->philosophers[i].thread, NULL))
		{
			printf("Error: pthread_join failed.\n");
			return (1);
		}
	}
	return (0);
}

void	*philo_handler(void *av)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)av;
	if (philo[0].data->philo_count == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		write_msg(philo, "has taken a fork");
		pthread_mutex_unlock(philo->right_fork);
		philo->data->end = 1;
		die_or_life(philo);
		return (av);
	}
	if (philo->id % 2 == 0)
		wait_time(philo, 1);
	while (die_or_life(philo))
	{
		philo_is_eating(philo);
		philo_is_sleeping(philo);
		philo_is_thinking(philo);
	}
	return (NULL);
}

int	begin_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philosophers[i].thread, NULL, philo_handler,
				(void *)&data->philosophers[i]))
			return (1);
		i++;
	}
	terminate_simulation(data);
	i = -1;
	while (++i < data->philo_count)
		if (philo_handler_helper(data, i))
			break ;
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
	{
		printf("Error: Invalid number of arguments.\n");
		return (1);
	}
	check_arguments(av);
	if (init_data(&data, av) || init_philo(&data) || init_forks(&data)
		|| init_mutexes(&data))
	{
		printf("Error: initialize failed!\n");
		return (1);
	}
	begin_simulation(&data);
	finish_simulation(&data);
}
