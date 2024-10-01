/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:37:37 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/01 20:10:56 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/philosophers.h"

void	start(t_data *data, t_philo **philos)
{
	int	i;
	t_checker	checker;

	i = 0;
	while (i <= data->nb_philo)
	{
		if (pthread_create(&philos[i]->th, NULL, &philos_routine, &philos[i]) != 0)
			clean_exit(data, philos, ERR_CREATE_THREAD, EXIT_FAILURE);
		i++;
	}
	checker.data = data;
	checker.ph_tab = philos;
	if (pthread_create(&checker.th, NULL, &checker_routine, &checker) != 0)
		clean_exit(data, philos, ERR_CREATE_THREAD, EXIT_FAILURE);
	if (pthread_mutex_init(&data->write, NULL) != 0)
		clean_exit(data, philos, ERR_INIT_MUTEX, EXIT_FAILURE);	
}

int main(int argc, char **argv)
{
    t_philo	*philos_tab;
	t_data data;
	
	philos_tab = NULL;
	if (argc != 5 || argc != 6)
    {
        printf("Usage :\n./philo [nb_of_philosophers (200 max)] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]\n");
		printf("NB : The last one is optional\n");
		exit(EXIT_FAILURE);
    }
	init_struct_and_philos(&data, &philos_tab, argc, argv);
	if (philos_tab != NULL)
		start(&data, philos_tab);
}
