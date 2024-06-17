/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:37:37 by pmateo            #+#    #+#             */
/*   Updated: 2024/06/17 20:08:05 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/philosophers.h"

int main(int argc, char **argv)
{
    t_data data;
	
	if (argc < 5 || argc > 6)
    {
        printf("Usage :\n./philo [nb_of_philosophers (200 max)] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]\n");
		printf("NB : The last one is optional\n");
		exit(EXIT_FAILURE);
    }
	init_and_fill_struct(&data, argc, argv);
	
}