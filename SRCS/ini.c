/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:15:14 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/03 19:37:15 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/philosophers.h"

static t_philo	**init_philos(t_data *data)
{
	t_philo philo[data->nb_philo];
	unsigned int	i;

	i = 0;
	while (i <= data->nb_philo)
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

static	void	fill_struct(t_data *data, int argc, char **argv)
{
	int	i;

	i = 0;
	data->nb_philo = (unsigned int)ft_mini_atoi(argv[1]);
	data->tt_die = (unsigned int)ft_mini_atoi(argv[2]);
	data->tt_eat = (unsigned int)ft_mini_atoi(argv[3]);
	data->tt_sleep = (unsigned int)ft_mini_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = (unsigned int)ft_mini_atoi(argv[5]);
	data->forks = malloc(data->nb_philo * sizeof(pthread_mutex_t));
	if (data->forks == NULL)
		clean_exit(data, NULL, ERR_MALLOC, EXIT_FAILURE);
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			clean_exit(data, NULL, ERR_INIT_MUTEX, EXIT_FAILURE);
	}
}

void	assign_fork_to_each_philos(t_data *data, t_philo **ph_tab)
{
	int	i;
	unsigned int nb_fork;

	i = 0;
	nb_fork = data->nb_philo;
	while (i < data->nb_philo)
	{
		ph_tab[i]->first_fork = ph_tab[i]->id;
		ph_tab[i]->second_fork = (ph_tab[i]->id + 1) % nb_fork;
		i++;
	}
}

t_philo	**init_structs_and_philos(t_data *data, t_philo **philo_tab, int argc, char **argv)
{	
	data->checker = NULL;
	data->nb_philo = 0;
	data->tt_die = 0;
	data->tt_eat = 0;
	data->tt_sleep = 0;
	data->must_eat = 0;
	if (checks_args(argv) == -1)
		clean_exit(data, NULL, ERR_BAD_ARGS, EXIT_FAILURE);
	philo_tab = init_philos(data);
	fill_struct(data, argc, argv);
	assign_fork_to_each_philos(data, philo_tab);
}
