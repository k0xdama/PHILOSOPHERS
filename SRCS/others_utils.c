/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 03:08:54 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/12 20:31:23 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../INCLUDES/philosophers.h"

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
	data->forks = NULL;
}

void	write_debug(t_data *data, char *str)
{
	pthread_t	thread_id = pthread_self();
	pthread_mutex_lock(&data->write);
	dprintf(2, "TH : %ld | %s\n", thread_id, str);
	pthread_mutex_unlock(&data->write);
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
	if (err != NULL)
		msg_err(err);
	if (sim_exit_code == FAILURE)
		return (FAILURE);
	else
		return (SUCCESS);
}