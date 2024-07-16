/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:15:14 by pmateo            #+#    #+#             */
/*   Updated: 2024/07/16 17:16:47 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/philosophers.h"

static	void	init_struct(t_data *data)
{
	data->nb_philo = 0;
	data->tt_die = 0;
	data->tt_eat = 0;
	data->tt_sleep = 0;
	data->must_eat = 0;
}

static	int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (2048);
	else
		return (0);
}

static int	checks_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(&argv[i][j]) == 2048)
				j++;
			else
				return (-1);
		}
		i++;
	}
	return (0);
}

static	void	fill_struct(t_data *data, int argc, char **argv)
{
	data->nb_philo = (unsigned int)ft_mini_atoi(argv[1]);
	data->tt_die = (unsigned int)ft_mini_atoi(argv[2]);
	data->tt_eat = (unsigned int)ft_mini_atoi(argv[3]);
	data->tt_sleep = (unsigned int)ft_mini_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = (unsigned int)ft_mini_atoi(argv[5]);
}

void	init_and_fill_struct(t_data *data, int argc, char **argv)
{
	init_struct(data);
	if (checks_args(argv) == -1)
	{
		printf("INCORRECT ARGUMENT\n");
		exit(EXIT_FAILURE);
	}
	fill_struct(data, argc, argv);
}