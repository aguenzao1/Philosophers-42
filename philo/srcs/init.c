/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguenzao <aguenzao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:07:49 by aguenzao          #+#    #+#             */
/*   Updated: 2025/03/14 14:40:33 by aguenzao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	ft_initialize_args(t_args *args, char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
		if (!ft_isint(argv[i]))
			return (false);
	args->philo_count = ft_atoi(argv[1]);
	args->time2die = ft_atoi(argv[2]);
	args->time2eat = ft_atoi(argv[3]);
	args->time2sleep = ft_atoi(argv[4]);
	args->max_meals = -1;
	if (argv[5])
		args->max_meals = ft_atoi(argv[5]);
	args->philos = malloc(sizeof(t_philo) * args->philo_count);
	if (!args->philos)
		return (false);
	if (pthread_mutex_init(&args->sync_mutex, NULL) != 0)
	{
		free(args->philos);
		return (false);
	}
	args->start_time = ft_now_ms();
	return (true);
}

bool	ft_initialize_philos(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->philo_count)
	{
		args->philos[i].nbr = i + 1;
		args->philos[i].last_meal_beginning = args->start_time;
		if ((pthread_mutex_init(&args->philos[i].l_fork, NULL)) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&args->philos[i].l_fork);
			pthread_mutex_destroy(&args->sync_mutex);
			free(args->philos);
			return (false);
		}
		if (i + 1 == args->philo_count)
			args->philos[i].r_fork = &args->philos[0].l_fork;
		else
			args->philos[i].r_fork = &args->philos[i + 1].l_fork;
		args->philos[i].args = args;
	}
	return (true);
}
