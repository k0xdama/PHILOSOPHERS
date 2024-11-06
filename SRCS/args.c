/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 20:36:01 by pmateo            #+#    #+#             */
/*   Updated: 2024/11/06 21:05:46 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/philosophers.h"

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (2048);
	else
		return (0);
}

long	ft_mini_atoi(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

int	checks_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit((int)argv[i][j]) == 2048)
				j++;
			else
				return (FAILURE);
		}
		if (ft_mini_atoi(argv[i]) > INT_MAX)
			return (FAILURE);
		i++;
	}
	if (ft_mini_atoi(argv[1]) > 200 || ft_mini_atoi(argv[1]) == 0)
		return (FAILURE);
	if (ft_mini_atoi(argv[2]) == 0)
		return (FAILURE);
	return (SUCCESS);
}
