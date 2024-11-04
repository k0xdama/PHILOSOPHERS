/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:16:52 by pmateo            #+#    #+#             */
/*   Updated: 2024/11/04 00:57:44 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../INCLUDES/philosophers.h"

void	lone_philo(t_philo *philo)
{
	ft_dodo(philo, philo->data->tt_die, false);
	pthread_mutex_unlock(&philo->data->forks[philo->first_fork]);
}

void	starting_routine(t_philo *philo)
{ 
	philo_debug(philo, "start and last meal value");
	pthread_mutex_lock(&philo->data->meal);
	philo->last_meal = philo->data->start;
	dprintf(2, "start = %lu ; lastmeal = %u\n", philo->data->start, philo->last_meal);
	pthread_mutex_unlock(&philo->data->meal);
	if (philo->id % 2 == 1)
		usleep(100);
}

static	int	wait_other_threads(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->init_th);
	philo->data->initialized_th += 1;
	pthread_mutex_unlock(&philo->data->init_th);
	philo_debug(philo, "has been initialized");
	// dprintf(2, "init th = %u\n", philo->data->initialized_th);
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
		pthread_mutex_unlock(&philo->data->stop);
		usleep(300 + (philo->id % 10) * 100);
	}
	return (SUCCESS);
}

void	*philos_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	philo_debug(philo, "has been created !");
	if (wait_other_threads(philo) == FAILURE)
		return (finish_philo(philo));
	philo_debug(philo, "all thread has been detached");
	starting_routine(philo);
	if (philo->data->must_eat == 0)
		return (finish_philo(philo));
	philo_debug(philo, "before loop");
	while (philo->data->stop_flag != true)
	{
		// philo_debug(philo, "before take first fork");
		pthread_mutex_lock(&philo->data->forks[philo->first_fork]);
		write_action(philo->data, philo, PRINT_TOOK_FORK);
		if (philo->data->nb_philos == 1)
		{	
			lone_philo(philo);
			return (finish_philo(philo));
		}
		pthread_mutex_lock(&philo->data->forks[philo->second_fork]);
		write_action(philo->data, philo, PRINT_TOOK_FORK);
		eat(philo);
		ft_dodo(philo, philo->data->tt_eat, true);
		think(philo);
	}
	return (finish_philo(philo));
}

//PREMIER TOUR ? PHILO TOUT SEUL ? TT_TO DIE à 0 ? NEED TO EAT à 0 ?

// VERIFICATION QUE TOUT LES THREADS ONT ETE DETACHES AVANT DE COMMENCER LA SIMULATION ET QUE CHAQUE THREADS
// COMMENCE SA ROUTINE
