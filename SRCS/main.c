/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:37:37 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/09 17:16:03 by jdenis           ###   ########.fr       */
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
	checker->data = data;
	checker->ph_tab = &philos;
	if (pthread_create(&checker->th, NULL, &checker_routine, checker) != 0)
			cleaner(data, FAILURE, ERR_CREATE_THREAD);

}

static	void	create_philo(t_data *data, t_philo *philo)
{
	if (pthread_create(&philo->th, NULL, &philos_routine, philo) != 0)
	{
			cleaner(data, FAILURE, ERR_CREATE_THREAD);
	}
}

#include <string.h>

static	void	start(t_data *data)
{
	int	i;
	t_checker	checker;

	i = -1;
	// memset(&checker, 0, sizeof(checker));
	while (i++ < (int)data->nb_philos )
		create_philo(data, &data->ph_tab[i]);		
	create_checker(data, &checker, data->ph_tab);
	detach_threads(data, &checker, data->ph_tab);
}

int main(int argc, char **argv)
{
	t_data data;
	
	if (argc < 5 || argc > 6)
    {
        printf("Usage :\n");
		printf("./philo [nb_of_philosophers (200 max)] [time_to_die]");
		printf(" [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]\n");
		printf("NB : The last one is optional\n");
		exit(EXIT_FAILURE);
    }
	if (init_structs_and_philos(&data, argc, argv) == FAILURE)
		return (FAILURE);
	// printf("data ??? nb_philos : %d\n", data.nb_philos);
	// printf("phtab ? nb_philos : %d\n", data.ph_tab[0]->id);
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

//MALLOC A FREE = tableau de forks
// MUTEX A DETRUIRE