/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguenzao <aguenzao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:08:55 by aguenzao          #+#    #+#             */
/*   Updated: 2025/03/15 00:01:22 by aguenzao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	ft_break_while(t_args *args, int *i)
{
	pthread_mutex_lock(&args->sync_mutex);
	if (ft_now_ms() - args->philos[*i].last_meal_beginning
		>= (unsigned long long)args->time2die
		|| args->total_finished == args->philo_count)
	{
		if (args->max_meals != -1 && args->total_finished == args->philo_count)
		{
			args->everybody_full = true;
			pthread_mutex_unlock(&args->philos[*i].l_fork);
		}
		else
		{
			args->death_occured = true;
			pthread_mutex_unlock(&args->philos[*i].l_fork);
			printf("%llu %d died\n",
				ft_now_ms() - args->start_time, args->philos[*i].nbr);
		}
		pthread_mutex_unlock(&args->sync_mutex);
		return (true);
	}
	if (*i + 1 == args->philo_count)
		*i = -1;
	pthread_mutex_unlock(&args->sync_mutex);
	return (false);
}

static bool	init_create_philosophers(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->philo_count)
	{
		if (pthread_create(&args->philos[i].thread, NULL, proutine,
				&args->philos[i]) != 0)
		{
			while (--i >= 0)
			{
				pthread_join(args->philos[i].thread, NULL);
				pthread_mutex_destroy(&args->philos[i].l_fork);
			}
			return (false);
		}
	}
	return (true);
}

static	void	cleanup_philosophers(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->philo_count)
		pthread_join(args->philos[i].thread, NULL);
	i = -1;
	while (++i < args->philo_count)
		pthread_mutex_destroy(&args->philos[i].l_fork);
	pthread_mutex_destroy(&args->sync_mutex);
	free(args->philos);
}

static	void	monitor_philosophers(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->philo_count && !ft_break_while(args, &i))
		;
}

int	main(int argc, char **argv)
{
	t_args	args;

	memset(&args, 0, sizeof(t_args));
	if (argc < 5 || argc > 6 || !ft_initialize_args(&args, argv))
	{
		printf("ERROR: invalid input!\n");
		return (1);
	}
	if (!ft_initialize_philos(&args))
		return (1);
	if (!init_create_philosophers(&args))
	{
		cleanup_philosophers(&args);
		return (1);
	}
	monitor_philosophers(&args);
	cleanup_philosophers(&args);
	return (0);
}
