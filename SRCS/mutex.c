/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 03:08:54 by pmateo            #+#    #+#             */
/*   Updated: 2024/11/06 18:39:29 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/philosophers.h"

int	create_forks(t_data *data)
{
	int				i;
	unsigned int	nb_fork;
	pthread_mutex_t	*forks_tab;

	i = 0;
	nb_fork = data->nb_philos;
	forks_tab = malloc(nb_fork * sizeof(pthread_mutex_t));
	if (forks_tab == NULL)
		return (msg_err(ERR_MALLOC), FAILURE);
	data->forks = forks_tab;
	while (i < (int)data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (i > 0)
				pthread_mutex_destroy(&data->forks[i--]);
			free(data->forks);
			data->forks = NULL;
			return (msg_err(ERR_INIT_MUTEX), FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	init_others_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->meal, NULL) != 0)
		return (msg_err(ERR_INIT_MUTEX), FAILURE);
	if (pthread_mutex_init(&data->write, NULL) != 0)
		return (msg_err(ERR_INIT_MUTEX), FAILURE);
	if (pthread_mutex_init(&data->stop, NULL) != 0)
		return (msg_err(ERR_INIT_MUTEX), FAILURE);
	if (pthread_mutex_init(&data->dead, NULL) != 0)
		return (msg_err(ERR_INIT_MUTEX), FAILURE);
	if (pthread_mutex_init(&data->init_th, NULL) != 0)
		return (msg_err(ERR_INIT_MUTEX), FAILURE);
	if (pthread_mutex_init(&data->finish_th, NULL) != 0)
		return (msg_err(ERR_INIT_MUTEX), FAILURE);
	return (SUCCESS);
}

void	destroy_forks(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	data->forks = NULL;
}

void	destroy_others_mutex(t_data *data)
{
	pthread_mutex_destroy(&data->meal);
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->stop);
	pthread_mutex_destroy(&data->dead);
	pthread_mutex_destroy(&data->init_th);
	pthread_mutex_destroy(&data->finish_th);
}
