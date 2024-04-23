/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:39:01 by ekose             #+#    #+#             */
/*   Updated: 2024/03/22 20:24:21 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error_1(t_data *data, char *s)
{
	free(data->forks);
	free(data->philos);
	// free(data->log);
	free(data->wait);
	free(data);
	printf("%s\n",s);
	exit(0);
}

void	ft_error2(t_data *data, char *s)
{
	printf("\033[31m%s!!!\n", s);
	free(data);
	exit(0);
}

void	ft_free(t_data *data)
{
	free(data->forks);
	free(data->philos);
	// free(data->log);
	free(data->wait);
	free(data);
}
