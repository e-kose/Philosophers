/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:52:38 by ekose             #+#    #+#             */
/*   Updated: 2024/03/24 18:57:48 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_multi_philo(t_philo *philo)
{
	while(philo->many_eat)
	{
		pthread_mutex_lock(&philo->data->forks[philo->lft_fork]);
		printf("%ld %d has taken a fork\n",ft_get_time() - philo->data->start_time, philo->pos);
		pthread_mutex_lock(&philo->data->forks[philo->rght_fork]);
		printf("%ld %d has taken a fork\n",ft_get_time() - philo->data->start_time, philo->pos);
		printf("%ld %d is eating\n",ft_get_time() - philo->data->start_time, philo->pos);
		if (ft_wait(philo, philo->data->time_to_eat) == 0)
			break ;
		philo->last_eat = ft_get_time();
		pthread_mutex_unlock(&philo->data->forks[philo->rght_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->lft_fork]);
		printf("%ld %d is sleeping\n",ft_get_time() - philo->data->start_time, philo->pos);
		if (ft_wait(philo, philo->data->time_to_sleep) == 0)
			break ;
		printf("%ld %d is thinking\n",ft_get_time() - philo->data->start_time, philo->pos);
		philo->many_eat--;
	}
}

void	*ft_simulation(void *arg)
{
	t_philo *philo;

	philo = (t_philo*)arg;
	if(philo->data->ttl_phl == 1)
	{
		printf("%ld %d has taken a fork\n",ft_get_time()- philo->data->start_time, philo->pos);
		usleep((philo->data->time_to_die * 1000));
		philo->data->index_philo_died = philo->pos;
		philo->data->time_of_death = ft_get_time() - philo->data->start_time;
		philo->data->stop = 1;
		return (0);
	}
	if(philo->pos % 2 != 0)
		usleep(100);
	ft_multi_philo(philo);
	return (0);
}

void	*ft_creat(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = ft_get_time();
	while (i < data->ttl_phl)
	{
		data->philos[i].last_eat = ft_get_time();
		if (pthread_create(&data->philos[i].td, NULL, ft_simulation, &data->philos[i]) != 0)
			ft_error_1(data,"Not creat pthread\n");
		i++;
	}
	i = 0;
	while (i < data->ttl_phl)
	{
		if (pthread_join(data->philos[i].td, NULL))
			ft_error_1(data,"Not pthread join\n");
		i++;
	}
	if (data->stop == 1)
		printf("%ld %d died\n",data->time_of_death, data->index_philo_died);
	return (0);
}

int main(int ac, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if(!(ac >= 5 && ac <= 6))
		ft_error2(data, "Number of arguments incorrect!!!");
	ft_check(data, argv);
	ft_fill(data, argv);
	ft_creat(data);
	ft_free(data);
	return (0);
}
