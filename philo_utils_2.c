/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 16:25:45 by ekose             #+#    #+#             */
/*   Updated: 2024/03/24 18:57:36 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_mutex_unlock(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->rght_fork]);
	pthread_mutex_unlock(philo->data->wait);
	pthread_mutex_unlock(&philo->data->forks[philo->lft_fork]);
}

static void	ft_init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->ttl_phl)
	{
		data->philos[i].pos = i + 1;
		data->philos[i].rght_fork = i;
		data->philos[i].lft_fork = (i + 1) % data->ttl_phl;
		data->philos[i].many_eat = data->must_eat_count;
		data->philos[i].data = data;
		i++;
	}
}

int	ft_wait(t_philo *philo, unsigned long time)
{
	unsigned long	now;

	now = ft_get_time();
	while (ft_get_time() - now < time)
	{
		pthread_mutex_lock(philo->data->wait);
		if (ft_get_time() - philo->last_eat >= philo->data->time_to_die && !philo->data->stop)
		{
			philo->data->index_philo_died = philo->pos;
			philo->data->stop = 1;
			philo->data->time_of_death = ft_get_time() - philo->data->start_time;
			ft_mutex_unlock(philo);
			return (0);
		}
		if( philo->data->stop == 1)
		{
			ft_mutex_unlock(philo);
			return (0);
		}
		pthread_mutex_unlock(philo->data->wait);
		usleep(100);
	}
	return (1);
}

void	ft_init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->ttl_phl)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			ft_error_1(data, "Mutex not created\n");
		i++;
	}
	if (pthread_mutex_init(data->wait, NULL) != 0)
		ft_error_1(data, "Mutex not created\n");
	ft_init_philo(data);
}
void	ft_fill(t_data *data, char **argv)
{
	data->philos = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	data->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	data->wait	= malloc(sizeof(pthread_mutex_t));
	data->ttl_phl = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat= ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->must_eat_count = -1;
	if (argv[5] != NULL)
		data->must_eat_count = ft_atoi(argv[5]);
	data->index_philo_died = -1;
	data->time_of_death = 0;
	data->stop = 0;
	ft_init_mutex(data);
}
