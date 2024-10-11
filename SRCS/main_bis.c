/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:31:10 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/11 22:55:27 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../INCLUDES/philosophers_bis.h"

static	void	detach_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i != (int)data->nb_th)
	{
		if (pthread_detach(data->threads_tab[i]) != 0)
			exit(EXIT_FAILURE);
		i++;
	}
}

void	start(t_data *data)
{
	int	i;

	i = 0;
	while (i != (int)data->nb_th)
	{
		if (pthread_create(&data->threads_tab[i], NULL, &routine_bis, data) != 0)
			exit(EXIT_FAILURE);
		i++;
	}
}

void	init_struct(t_data *data, pthread_t *threads_tab)
{	
	
	data->threads_tab = threads_tab;
	data->threads_tab[0] = 0;
	data->threads_tab[1] = 0;
	data->threads_tab[2] = 0;
	data->stop_flag = false;
	data->nb_th = 3;
	data->initialized_th = 0;
	data->finished_th = 0;
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->stop, NULL);
}

int main(void)
{
	t_data data;
	pthread_t	threads_tab[3];
	
	init_struct(&data, threads_tab);
	start(&data);
	detach_threads(&data);
	while (true)
	{
		pthread_mutex_lock(&data.stop);
		if (data.finished_th == data.initialized_th)
		{
			pthread_mutex_unlock(&data.stop);
			break;
		}
		pthread_mutex_unlock(&data.stop);
		usleep(1000);
	}
	write_status(&data, "main thread gonna exit");
	return (0);
}