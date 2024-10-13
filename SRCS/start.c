/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:33:49 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/13 22:23:41 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../INCLUDES/philosophers.h"

int	detach_threads(t_data *data, t_checker *checker, t_philo *philos)
{
	unsigned int	i;

	i = 0;
	while (i < data->created_philos_th)
	{
		if (pthread_detach(philos[i].th) != 0)
			return (msg_err(ERR_DETACH_THREAD), FAILURE);
		i++;
	}
	if (data->checker_is_created == true)
	{
		if (pthread_detach(checker->th) != 0)
			return (msg_err(ERR_DETACH_THREAD), FAILURE);
	}
	return (SUCCESS);
}

static	int	create_checker(t_data *data, t_checker *checker, t_philo *philos)
{
	checker->th = 0;
	checker->data = data;
	checker->ph_tab = philos;
	if (pthread_create(&checker->th, NULL, &checker_routine, checker) != 0)
		return (msg_err(ERR_CREATE_THREAD), FAILURE);
	else
	{
		data->checker_is_created = true;
		return (SUCCESS);
	}
}

static	int	create_philo(t_philo *philo)
{
	if (pthread_create(&philo->th, NULL, &philos_routine, philo) != 0)
		return (msg_err(ERR_CREATE_THREAD), FAILURE);
	else
		return (SUCCESS);
}

int	start(t_data *data, t_checker *checker)
{
	unsigned int	i;

	i = 0;
	while (i < data->nb_philos )
	{
		if (create_philo(&data->ph_tab[i]) == FAILURE)
		{
			pthread_mutex_lock(&data->stop);
			data->stop_flag = true;
			pthread_mutex_unlock(&data->stop);
			return (FAILURE);
		}
		data->created_philos_th++;
		i++;
	}		
	if (create_checker(data, checker, data->ph_tab) == FAILURE)
	{
		pthread_mutex_lock(&data->stop);
		data->stop_flag = true;
		pthread_mutex_unlock(&data->stop);
		return (FAILURE);
	}
	data->start = get_timestamp();
	return (SUCCESS);
}
