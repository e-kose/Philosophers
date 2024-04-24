/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:53:40 by ekose             #+#    #+#             */
/*   Updated: 2024/04/24 17:07:44 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

# define RED "\033[31m"
# define YELLOW "\033[32m"

typedef struct s_data	t_data;

typedef struct s_philo
{
	time_t		last_eat;
	int			pos;
	int			lft_fork;
	int			rght_fork;
	int			many_eat;
	pthread_t	td;
	t_data		*data;
}	t_philo;

typedef struct s_data
{
	t_philo			*philos;
	int				ttl_phl;
	int				must_eat_count;
	int				index_philo_died;
	int				stop;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	time_t			time_of_death;
	time_t			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*wait;
}	t_data;

void			ft_error_1(t_data *data, char *s);
void			ft_error2(t_data *data, char *s);
void			ft_free(t_data *data);
void			ft_check(t_data *data, char **argv);
void			ft_usleep(unsigned long time);
void			ft_fill(t_data *data, char **argv);
void			ft_init_mutex(t_data *data);
int				ft_atoi(const char *str);
unsigned long	ft_get_time(void);
int				ft_wait(t_philo *philo, unsigned long time, char work);
#endif
