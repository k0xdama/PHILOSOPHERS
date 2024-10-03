/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:16:52 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/03 21:06:23 by pmateo           ###   ########.fr       */
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

void	*philos_routine(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	starting_routine(philo);
	while (philo->data->stop_flag != true)
	{
		pthread_mutex_lock(&philo->data->forks[philo->first_fork]);
		write_action(philo->data, philo, PRINT_TOOK_FORK);
		pthread_mutex_lock(&philo->data->forks[philo->second_fork]);
		write_action(philo->data, philo, PRINT_TOOK_FORK);
		eat(philo);
		pthread_mutex_unlock(&philo->data->forks[philo->first_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->second_fork]);
	}
}
