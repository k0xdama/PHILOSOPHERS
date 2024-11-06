/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:19:59 by pmateo            #+#    #+#             */
/*   Updated: 2024/11/06 18:42:39 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/philosophers.h"

void	think(t_philo *ph)
{
	size_t	ttd;
	size_t	lm;
	size_t	tte;

	ttd = ph->data->tt_die;
	lm = ph->last_meal;
	tte = ph->data->tt_eat;
	pthread_mutex_lock(&ph->data->dead);
	if (ph->is_dead == false)
	{
		pthread_mutex_unlock(&ph->data->dead);
		write_action(ph->data, ph, PRINT_THINKING);
		while (get_timestamp() - ph->last_meal < 0.9 * ph->data->tt_die)
			usleep(1000);
	}
	else
		pthread_mutex_unlock(&ph->data->dead);
}

void	ft_dodo(t_philo *ph, size_t time, bool print_action)
{
	size_t	dodo_start_time;

	dodo_start_time = 0;
	pthread_mutex_lock(&ph->data->dead);
	if (ph->is_dead == true)
	{
		pthread_mutex_unlock(&ph->data->dead);
		return ;
	}
	pthread_mutex_unlock(&ph->data->dead);
	dodo_start_time = get_timestamp();
	if (print_action == true)
		write_action(ph->data, ph, PRINT_SLEEPING);
	pthread_mutex_lock(&ph->data->dead);
	while (ph->is_dead == false && get_timestamp() < dodo_start_time + time)
	{
		pthread_mutex_unlock(&ph->data->dead);
		usleep(20);
		pthread_mutex_lock(&ph->data->dead);
	}
	pthread_mutex_unlock(&ph->data->dead);
}

void	eat(t_philo *ph)
{
	size_t	meal_start_time;

	meal_start_time = get_timestamp();
	pthread_mutex_lock(&ph->data->meal);
	ph->last_meal = meal_start_time;
	pthread_mutex_unlock(&ph->data->meal);
	write_action(ph->data, ph, PRINT_EATING);
	pthread_mutex_lock(&ph->data->dead);
	while (ph->is_dead == false
		&& get_timestamp() < meal_start_time + ph->data->tt_eat)
	{
		pthread_mutex_unlock(&ph->data->dead);
		usleep(20);
		pthread_mutex_lock(&ph->data->dead);
	}
	pthread_mutex_unlock(&ph->data->dead);
	pthread_mutex_unlock(&ph->data->forks[ph->first_fork]);
	pthread_mutex_unlock(&ph->data->forks[ph->second_fork]);
	pthread_mutex_lock(&ph->data->meal);
	if (ph->data->must_eat != -1)
		ph->meals_count++;
	pthread_mutex_unlock(&ph->data->meal);
}
