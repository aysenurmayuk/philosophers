/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:00:14 by amayuk            #+#    #+#             */
/*   Updated: 2024/11/21 20:19:03 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 200

typedef struct s_philosopher
{
	int				id;
	int				eat_count;
	size_t			start_time;
	size_t			last_meal;
	int				eat_done;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	struct s_data	*data;
}					t_philosopher;

typedef struct s_data
{
	int				philo_count;
	int				end;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	int				required_meals;
	t_philosopher	philosophers[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];
	pthread_mutex_t	mutex_output;
	pthread_mutex_t	mutex_end;
	pthread_mutex_t	mutex_meal;
	pthread_mutex_t	mutex_need;
}					t_data;

int					init_mutexes(t_data *data);
int					init_forks(t_data *data);
int					init_philo(t_data *data);
int					init_data(t_data *data, char **av);
long				ft_atoi(const char *str);
size_t				get_time(void);
void				wait_time(t_philosopher *philo, size_t time);
void				philo_is_eating(t_philosopher *philo);
void				philo_is_sleeping(t_philosopher *philo);
void				philo_is_thinking(t_philosopher *philo);
void				write_msg(t_philosopher *philo, char *msg);
void				terminate_simulation(t_data *data);
void				finish_simulation(t_data *data);
int					die_or_life(t_philosopher *philo);
int					is_ate(t_philosopher *philo);
int					check_arguments(char **av);
int					is_dead(t_data *data);
int					is_complated_eat(t_data *data);

#endif
