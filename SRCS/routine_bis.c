/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:01:54 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/11 23:01:48 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../INCLUDES/philosophers_bis.h"

void	write_status(t_data *data, char *str)
{
	pthread_t	thread_id = pthread_self();
	pthread_mutex_lock(&data->write);
	dprintf(2, "TH : %ld | %s %u\n", thread_id, str, data->initialized_th);
	pthread_mutex_unlock(&data->write);
}

static	int	wait_other_threads(t_data *data)
{
	pthread_mutex_lock(&data->stop);
	data->initialized_th += 1;
	pthread_mutex_unlock(&data->stop);
	write_status(data, "has been initialized");
	while (true)
	{
		pthread_mutex_lock(&data->stop);
		write_status(data, "initialized_th =");
		if (data->initialized_th == data->nb_th)
		{
			pthread_mutex_unlock(&data->stop);
			break;
		}
		if (data->stop_flag == true)
		{
			pthread_mutex_unlock(&data->stop);
			return (EXIT_FAILURE);
		}
		usleep(500);
	}
	return (EXIT_SUCCESS);
}

void	*routine_bis(void *ptr)
{
	t_data *data;

	data = (t_data *)ptr;
	if (wait_other_threads(data) == EXIT_FAILURE)
		return (NULL);
	write_status(data, "all threads has been initialized");
	while (1)
	{
		sleep(1);
		break;
	}
	return (data->finished_th++, NULL);
}
