/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:15:14 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/06 02:47:30 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/philosophers.h"

static	void	assign_fork_to_each_philos(t_data *data, t_philo **ph_tab)
{
	int	i;
	unsigned int nb_fork;

	i = 0;
	nb_fork = data->nb_philos;
	while (i < data->nb_philos)
	{
		ph_tab[i]->first_fork = ph_tab[i]->id;
		ph_tab[i]->second_fork = (ph_tab[i]->id + 1) % nb_fork;
		i++;
	}
}

static 	int	init_others_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->meal, NULL) != 0)
		return (cleaner(data, FAILURE, ERR_INIT_MUTEX));
	if (pthread_mutex_init(&data->write, NULL) != 0)
		return (cleaner(data, FAILURE, ERR_INIT_MUTEX));
	if (pthread_mutex_init(&data->stop_flag, NULL) != 0)
		return (cleaner(data, FAILURE, ERR_INIT_MUTEX));
	return (SUCCESS)
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
		return (err_msg(ERR_MALLOC), FAILURE);
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while ((i - 1) >= 0)
				pthread_mutex_destroy(&data->forks[i--]);
			free(data->forks);
			data->forks = NULL;
			return (err_msg(ERR_INIT_MUTEX), FAILURE);
		}
	}
	return (init_others_mutex(data));
}

static t_philo	**init_philos(t_data *data)
{
	t_philo philo[data->nb_philos];
	unsigned int	i;

	i = 0;
	while (i <= data->nb_philos)
	{
		philo[i].id = i + 1;
		philo[i].first_fork = 0;
		philo[i].second_fork = 0;
		philo[i].last_meal = 0;
		philo[i].meals_count = 0;
		philo[i].eating = false;
		philo[i].is_starving = false;
		philo[i].is_dead = false;
		philo[i].data = data;
		i++;
	}
}

int	init_structs_and_philos(t_data *data, t_philo **philos_tab, int argc, char **argv)
{	
	data->ph_tab = NULL;
	data->nb_philos = 0;
	data->initialized_th = 0;
	data->finished_th = 0;
	data->tt_die = 0;
	data->tt_eat = 0;
	data->tt_sleep = 0;
	data->must_eat = -1;
	if (checks_args(argv) == -1)
		return (err_msg(ERR_BAD_ARGS), NULL);
	philos_tab = init_philos(data);
	data->ph_tab = philos_tab;
	if (fill_struct(data, argc, argv) == FAILURE)
		return (FAILURE);
	assign_fork_to_each_philos(data, philos_tab);
	return (SUCCESS);
}
