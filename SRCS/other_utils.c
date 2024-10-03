/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:39:38 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/03 18:17:45 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../INCLUDES/philosophers.h"

void	write_action(t_data *data, t_philo *ph, char *str)
{
	size_t	time;

	time = get_timestamp() - ph->data->start;
	pthread_mutex_lock(&data->write);
	printf("%lu %d %s\n", time, ph->id, str);
	pthread_mutex_unlock(&data->write);
}

unsigned int	get_timestamp(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) == -1)
	{
		printf("\"gettimeofday\" failed !\n");
		return (0);
	}
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	clean_exit(t_data *data, t_philo **ph_tab, char *err, int exit_code)
{
	free_data(data);
	free_philos(ph_tab);
	if (err != NULL)
	{
		printf("ERROR : %s\n", err);
		if (err == ERR_BAD_ARGS)
		{
			printf("Usage :\n./philo [nb_of_philosophers (200 max)] [time_to_die] [time_to_eat]");
			printf("[time_to_sleep] [number_of_times_each_philosopher_must_eat]\n");
		}
		exit (EXIT_FAILURE);
	}
	else
		exit (EXIT_SUCCESS);
}
//gestion d'erreur lors de la création des threads ?
// INT MAX DANS LES ARGUMENTS

