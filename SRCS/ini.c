/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:15:14 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/08 12:48:05 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/philosophers.h"

static	void	assign_fork_to_each_philos(t_data *data)
{
	unsigned int	i;
	unsigned int 	nb_fork;
	t_philo			**philos_tab;

	i = 0;
	nb_fork = data->nb_philos;
	philos_tab = data->ph_tab;
	while (i < data->nb_philos)
	{
		philos_tab[i]->first_fork = philos_tab[i]->id;
		philos_tab[i]->second_fork = (philos_tab[i]->id + 1) % nb_fork;
		i++;
	}
}

static 	int	init_others_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->meal, NULL) != 0)
		return (cleaner(data, FAILURE, ERR_INIT_MUTEX));
	if (pthread_mutex_init(&data->write, NULL) != 0)
		return (cleaner(data, FAILURE, ERR_INIT_MUTEX));
	if (pthread_mutex_init(&data->stop, NULL) != 0)
		return (cleaner(data, FAILURE, ERR_INIT_MUTEX));
	return (SUCCESS);
}

static	int	fill_struct(t_data *data, int argc, char **argv)
{
	int	i;

	i = 0;
	data->nb_philos = (unsigned int)ft_mini_atoi(argv[1]);
	data->tt_die = (unsigned int)ft_mini_atoi(argv[2]);
	data->tt_eat = (unsigned int)ft_mini_atoi(argv[3]);
	data->tt_sleep = (unsigned int)ft_mini_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = (unsigned int)ft_mini_atoi(argv[5]);
	data->forks = malloc(data->nb_philos * sizeof(pthread_mutex_t));
	if (data->forks == NULL)
		return (msg_err(ERR_MALLOC), FAILURE);
	while (i < (int)data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while ((i - 1) >= 0)
				pthread_mutex_destroy(&data->forks[i--]);
			free(data->forks);
			data->forks = NULL;
			return (msg_err(ERR_INIT_MUTEX), FAILURE);
		}
	}
	return (init_others_mutex(data));
}

static	void	init_philos(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i <= data->nb_philos)
	{
		data->ph_tab[i]->id = i + 1;
		data->ph_tab[i]->first_fork = 0;
		data->ph_tab[i]->second_fork = 0;
		data->ph_tab[i]->last_meal = 0;
		data->ph_tab[i]->meals_count = 0;
		data->ph_tab[i]->eating = false;
		data->ph_tab[i]->is_starving = false;
		data->ph_tab[i]->is_dead = false;
		data->ph_tab[i]->data = data;
		i++;
	}
}

int	init_structs_and_philos(t_data *data, int argc, char **argv)
{	
	data->ph_tab = malloc(data->nb_philos * sizeof(t_philo));
	data->nb_philos = 0;
	data->initialized_th = 0;
	data->finished_th = 0;
	data->tt_die = 0;
	data->tt_eat = 0;
	data->tt_sleep = 0;
	data->must_eat = -1;
	if (checks_args(argv) == -1)
		return (msg_err(ERR_BAD_ARGS), FAILURE);
	init_philos(data);
	if (fill_struct(data, argc, argv) == FAILURE)
		return (FAILURE);
	assign_fork_to_each_philos(data);
	return (SUCCESS);
}
