/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:39:38 by pmateo            #+#    #+#             */
/*   Updated: 2024/11/06 18:47:45 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/philosophers.h"

void	write_action(t_data *data, t_philo *ph, char *str)
{
	size_t	time;

	time = get_timestamp() - ph->data->start;
	pthread_mutex_lock(&data->stop);
	if (data->stop_flag == false)
	{
		pthread_mutex_unlock(&data->stop);
		pthread_mutex_lock(&data->write);
		printf("%lu %d %s\n", time, ph->id, str);
		pthread_mutex_unlock(&data->write);
	}
	else
		pthread_mutex_unlock(&data->stop);
}

size_t	get_timestamp(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) == -1)
	{
		printf("\"gettimeofday\" failed !\n");
		return (0);
	}
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}
