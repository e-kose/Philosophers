/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:32:47 by ekose             #+#    #+#             */
/*   Updated: 2024/03/23 02:36:00 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

unsigned long	ft_get_time(void)
{
	struct timeval time;
	unsigned long	now_msc;
	if(gettimeofday(&time,NULL))
		return (0);
	now_msc = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (now_msc);
}

void	ft_usleep(unsigned long time)
{
	unsigned long	start;

	start = ft_get_time();
	while (1)
		if ((ft_get_time() - start) * 1000 >= (time) *1000)
			return ;
}
int	ft_atoi(const char *str)
{
	int	i;
	int	nb;
	int	sign;

	i = 0;
	nb = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (sign * nb);
}
void	ft_check(t_data *data, char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (argv[++i])
	{
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) != 1)
				ft_error2(data, "Error : invalid argument");
			j++;
		}
		j = 0;
	}
}
