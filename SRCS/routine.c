/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:16:52 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/10 18:43:44 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../INCLUDES/philosophers.h"

void	starting_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal);
	philo->last_meal = philo->data->start;
	pthread_mutex_unlock(&philo->data->meal);
	if (philo->id % 2 == 1)
		usleep(100);
}

static	int	wait_other_threads(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->stop);
	philo->data->initialized_th += 1;
	pthread_mutex_unlock(&philo->data->stop);
	while (true)
	{
		pthread_mutex_lock(&philo->data->stop);
		if (philo->data->initialized_th == philo->data->nb_philos + 1)
		{
			pthread_mutex_unlock(&philo->data->stop);
			break;
		}
		if (philo->data->stop_flag == true)
		{
			pthread_mutex_unlock(&philo->data->stop);
			return (FAILURE);
		}
		usleep(500);
	}
	return (SUCCESS);
}

void	*philos_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	printf("is dead : %d", ((t_philo *)ptr)->is_dead);
	printf("stop_flag : %d", philo->data->stop_flag);
	if (wait_other_threads(philo) == FAILURE)
		return (philo->data->finished_th++, NULL);
	starting_routine(philo);
	if (philo->data->must_eat == 0)
		return (philo->data->finished_th++, NULL);
	while (philo->data->stop_flag != true)
	{
		pthread_mutex_lock(&philo->data->forks[philo->first_fork]);
		write_action(philo->data, philo, PRINT_TOOK_FORK);
		pthread_mutex_lock(&philo->data->forks[philo->second_fork]);
		write_action(philo->data, philo, PRINT_TOOK_FORK);
		eat(philo);
		pthread_mutex_unlock(&philo->data->forks[philo->first_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->second_fork]);
		ft_dodo(philo, philo->data->tt_sleep);
	}
	return (philo->data->finished_th++, NULL);
}

//PREMIER TOUR ? PHILO TOUT SEUL ? TT_TO DIE à 0 ? NEED TO EAT à 0 ?

// VERIFICATION QUE TOUT LES THREADS ONT ETE DETACHES AVANT DE COMMENCER LA SIMULATION ET QUE CHAQUE THREADS
// COMMENCE SA ROUTINE
