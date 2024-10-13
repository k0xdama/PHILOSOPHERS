/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:19:59 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/13 19:37:09 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/philosophers.h"

void	think(t_philo *ph)
{
	write_action(ph->data, ph, PRINT_THINKING);
	usleep(500);
}

void	ft_dodo(t_philo *ph, unsigned int time)
{
	unsigned int dodo_start_time;

	dodo_start_time = get_timestamp();
	write_action(ph->data, ph, PRINT_SLEEPING);
	while (dodo_start_time + time < get_timestamp())
		usleep(25);
}

void	eat(t_philo *ph)
{
	unsigned int meal_start_time;

	meal_start_time = get_timestamp();
	write_action(ph->data, ph, PRINT_EATING);
	while (meal_start_time + ph->data->tt_eat < get_timestamp())
		usleep(25);
	pthread_mutex_unlock(&ph->data->forks[ph->first_fork]);
	pthread_mutex_unlock(&ph->data->forks[ph->second_fork]);
	pthread_mutex_lock(&ph->data->meal);
	ph->last_meal = get_timestamp();
	if (ph->data->must_eat != -1)
		ph->meals_count++;
	pthread_mutex_unlock(&ph->data->meal);
}