/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:16:52 by pmateo            #+#    #+#             */
/*   Updated: 2024/11/06 18:47:22 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/philosophers.h"

void	lone_philo(t_philo *philo)
{
	ft_dodo(philo, philo->data->tt_die, false);
	pthread_mutex_unlock(&philo->data->forks[philo->first_fork]);
}

void	starting_routine(t_philo *philo)
{
	if (philo->id % 2 == 1)
		usleep(1000);
}

static	int	wait_other_threads(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->init_th);
	philo->data->initialized_th += 1;
	pthread_mutex_unlock(&philo->data->init_th);
	while (true)
	{
		pthread_mutex_lock(&philo->data->init_th);
		if (philo->data->initialized_th == philo->data->nb_philos + 1)
		{
			pthread_mutex_unlock(&philo->data->init_th);
			break ;
		}
		pthread_mutex_unlock(&philo->data->init_th);
		pthread_mutex_lock(&philo->data->stop);
		if (philo->data->stop_flag == true)
		{
			pthread_mutex_unlock(&philo->data->stop);
			return (FAILURE);
		}
		pthread_mutex_unlock(&philo->data->stop);
		usleep(300 + (philo->id % 10) * 100);
	}
	return (SUCCESS);
}

void	*philos_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (wait_other_threads(philo) == FAILURE)
		return (finish_philo(philo));
	starting_routine(philo);
	if (philo->data->must_eat == 0)
		return (finish_philo(philo));
	pthread_mutex_lock(&philo->data->stop);
	while (philo->data->stop_flag != true)
	{
		pthread_mutex_unlock(&philo->data->stop);
		pthread_mutex_lock(&philo->data->forks[philo->first_fork]);
		write_action(philo->data, philo, PRINT_TOOK_FORK);
		if (philo->data->nb_philos == 1)
			return (lone_philo(philo), finish_philo(philo));
		pthread_mutex_lock(&philo->data->forks[philo->second_fork]);
		write_action(philo->data, philo, PRINT_TOOK_FORK);
		eat(philo);
		ft_dodo(philo, philo->data->tt_sleep, true);
		think(philo);
		pthread_mutex_lock(&philo->data->stop);
	}
	pthread_mutex_unlock(&philo->data->stop);
	return (finish_philo(philo));
}
