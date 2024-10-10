/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:31:10 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/10 20:08:53 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "INCLUDES/philosophers_bis.c"

static	void	detach_threads(t_data *data)
{
	int	i;

	i = 0;
	(void) checker;
	(void) philos;
	while (i < (int)data->nb_philos)
	{
		// if (pthread_detach(philos[i].th) != 0)
		// 	cleaner(data, FAILURE, ERR_DETACH_THREAD);
		i++;
	}
	// if (pthread_detach(checker->th) != 0)
	// 	cleaner(data, FAILURE, ERR_DETACH_THREAD);
}

void	start(t_data *data)
{
	
}

void	init_struct(t_data *data)
{	
	pthread_t	threads_tab[3];
	
	threads_tab[0] = NULL;
	threads_tab[1] = NULL;
	threads_tab[2] = NULL;
	data->stop_flag = false;
	data->nb_th = 3;
	data->initialized_th = 0;
	data->finished_th = 0;
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->stop, NULL);
}

int main(int argc, char **argv)
{
	t_data data;
	
	init_struct(&data);
	start(&data);
	while (true)
	{
		pthread_mutex_lock(&data.stop);
		if (data.stop_flag == true && data.finished_th == data.initialized_th)
		{
			pthread_mutex_unlock(&data.stop);
			break;
		}
		pthread_mutex_unlock(&data.stop);
		usleep(1000);
	}

	return (cleaner(&data, SUCCESS, NULL));
}