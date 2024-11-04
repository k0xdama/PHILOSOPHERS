/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:19:59 by pmateo            #+#    #+#             */
/*   Updated: 2024/11/04 22:20:38 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/philosophers.h"

void	think(t_philo *ph)
{
	write_action(ph->data, ph, PRINT_THINKING);
	usleep(500);
}

void	ft_dodo(t_philo *ph, size_t time, bool print_action)
{
	size_t	dodo_start_time;

	dodo_start_time = get_timestamp();
	if (print_action == true)
		write_action(ph->data, ph, PRINT_SLEEPING);
	// printf("dodo start time == %llu, time == %u et start time == %zu\n",dodo_start_time, time,get_timestamp());
	while (dodo_start_time + time < get_timestamp())
		usleep(100);
	// printf("dodo start time == %llu, time == %u et start time == %zu\n",dodo_start_time, time,get_timestamp());
}

void	eat(t_philo *ph)
{
	size_t	meal_start_time;

	meal_start_time = get_timestamp();
	write_action(ph->data, ph, PRINT_EATING);
	while (meal_start_time + ph->data->tt_eat < get_timestamp())
		usleep(100);
	pthread_mutex_unlock(&ph->data->forks[ph->first_fork]);
	pthread_mutex_unlock(&ph->data->forks[ph->second_fork]);
	pthread_mutex_lock(&ph->data->meal);
	ph->last_meal = get_timestamp();
	if (ph->data->must_eat != -1)
		ph->meals_count++;
	pthread_mutex_unlock(&ph->data->meal);
}