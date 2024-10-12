/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:37:37 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/12 05:13:37 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/philosophers.h"

static	void	detach_threads(t_data *data, t_checker *checker, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < (int)data->nb_philos)
	{
		if (pthread_detach(philos[i].th) != 0)
			cleaner(data, FAILURE, ERR_DETACH_THREAD);
		i++;
	}
	if (pthread_detach(checker->th) != 0)
		cleaner(data, FAILURE, ERR_DETACH_THREAD);
}

static	void	create_checker(t_data *data, t_checker *checker, t_philo *philos)
{
	checker->th = 0;
	checker->data = data;
	checker->ph_tab = &philos;
	if (pthread_create(&checker->th, NULL, &checker_routine, checker) != 0)
		cleaner(data, FAILURE, ERR_CREATE_THREAD);

}

static	int	create_philo(t_data *data, t_philo *philo)
{
	if (pthread_create(&philo->th, NULL, &philos_routine, philo) != 0)
		return (cleaner(data, FAILURE, ERR_CREATE_THREAD));
	else
		return (SUCCESS);
}

static	void	start(t_data *data, t_checker *checker)
{
	int	i;

	i = 0;
	while (i < (int)data->nb_philos )
	{
		if (create_philo(data, &data->ph_tab[i]) == FAILURE)
		{
			pthread_mutex_lock(&data->stop);
			data->stop_flag = true;
			pthread_mutex_unlock(data->stop);
		}
			
		i++;
	}		
	create_checker(data, checker, data->ph_tab);
}

int main(int argc, char **argv)
{
	t_data data;
	t_philo	philos_tab[200];
	t_checker	checker;
	
	if (argc < 5 || argc > 6)
    {
		msg_err(ERR_BAD_ARGS);
		exit(EXIT_FAILURE);
    }
	if (init_structs_and_philos(&data, philos_tab, argc, argv) == FAILURE)
		return (FAILURE);
	start(&data, &checker);
	detach_threads(&data, &checker, data.ph_tab);
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
	write_debug(&data, "main thread gonna exit");
	return (cleaner(&data, SUCCESS, NULL));
}

//