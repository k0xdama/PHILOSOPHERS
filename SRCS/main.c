/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:37:37 by pmateo            #+#    #+#             */
/*   Updated: 2024/11/06 18:28:01 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/philosophers.h"

static	void	main_thread_waiting(t_data *data)
{
	while (true)
	{
		pthread_mutex_lock(&data->init_th);
		pthread_mutex_lock(&data->finish_th);
		pthread_mutex_lock(&data->stop);
		if (data->stop_flag == true
			&& data->finished_th == data->initialized_th)
		{
			pthread_mutex_unlock(&data->init_th);
			pthread_mutex_unlock(&data->finish_th);
			pthread_mutex_unlock(&data->stop);
			break ;
		}
		pthread_mutex_unlock(&data->init_th);
		pthread_mutex_unlock(&data->finish_th);
		pthread_mutex_unlock(&data->stop);
		usleep(10000);
	}
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		philos_tab[300];
	t_checker	checker;

	if (argc < 5 || argc > 6)
		return (msg_err(ERR_BAD_ARGS), FAILURE);
	if (init_structs_and_philos(&data, philos_tab, argc, argv) == FAILURE)
		return (FAILURE);
	if (start(&data, &checker) == FAILURE)
		data.stop_reason = LAUNCH_ERROR;
	if (detach_threads(&data, &checker, data.ph_tab) == FAILURE)
		data.stop_reason = LAUNCH_ERROR;
	main_thread_waiting(&data);
	if (data.stop_reason == LAUNCH_ERROR)
		return (cleaner(&data, FAILURE, NULL));
	else
		return (cleaner(&data, SUCCESS, NULL));
}
