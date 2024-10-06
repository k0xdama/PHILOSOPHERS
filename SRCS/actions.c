/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:19:59 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/05 01:02:41 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/philosophers.h"

void	think(t_philo *ph)
{
	write_action(ph->data, ph, PRINT_THINKING);
}

void	ft_dodo(t_philo *ph, unsigned int time)
{
	unsigned int time_stamp_when_called;

	time_stamp_when_called = get_timestamp();
	write_action(ph->data, ph, PRINT_SLEEPING);
	while (time_stamp_when_called + time < get_timestamp())
		usleep(50);
}

void	eat(t_philo *ph)
{
	write_action(ph->data, ph, PRINT_EATING);
	pthread_mutex_lock(&ph->data->meal);
	ph->last_meal = get_timestamp();
	if (ph->data->must_eat != -1)
		ph->meals_count++;
	pthread_mutex_unlock(&ph->data->meal);
	ft_dodo(ph, ph->data->tt_eat);
	think(ph);
}