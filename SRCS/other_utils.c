/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:39:38 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/12 04:45:57 by pmateo           ###   ########.fr       */
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

static	void	destroy_others_mutex(t_data *data)
{
	pthread_mutex_destroy(&data->meal);
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->stop);
}

static	void	destroy_forks(t_data *data)
{
	unsigned	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	data->forks = NULL;
}

void	msg_err(char *err)
{
	printf("ERROR : %s\n", err);
	if (ft_strcmp(err, ERR_BAD_ARGS) == 0)
	{
		printf("Usage :\n./philo [nb_of_philosophers (200 max)] [time_to_die] [time_to_eat]");
		printf("[time_to_sleep] [number_of_times_each_philosopher_must_eat]\n");
	}
}

int	cleaner(t_data *data, int sim_exit_code, char *err)
{
	if (data->forks != NULL)
		destroy_forks(data);
	destroy_others_mutex(data);
	if (sim_exit_code == FAILURE)
	{
		msg_err(err);
		return (FAILURE);
	}
	else
		return (SUCCESS);
}
//gestion d'erreur lors de la création des threads :
// - 
// INT MAX DANS LES ARGUMENTS

