/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguenzao <aguenzao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:55:43 by aguenzao          #+#    #+#             */
/*   Updated: 2025/03/15 17:26:25 by aguenzao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	ft_write_status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->args->sync_mutex);
	if (philo->args->death_occured || philo->args->everybody_full)
	{
		pthread_mutex_unlock(&philo->args->sync_mutex);
		return (false);
	}
	printf("%llu %d %s\n", ft_now_ms() - philo->args->start_time,
		philo->nbr, msg);
	pthread_mutex_unlock(&philo->args->sync_mutex);
	return (true);
}

bool	ft_should_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->sync_mutex);
	if (philo->args->death_occured || philo->args->everybody_full)
	{
		pthread_mutex_unlock(&philo->args->sync_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->args->sync_mutex);
	return (false);
}

static bool	ft_get_forks(t_philo *philo)
{
	if (ft_should_stop(philo))
		return (false);
	pthread_mutex_lock(&philo->l_fork);
	if (!ft_write_status(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(&philo->l_fork);
		return (false);
	}
	if (ft_should_stop(philo))
		return (false);
	pthread_mutex_lock(philo->r_fork);
	if (!ft_write_status(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (false);
	}
	return (true);
}

static bool	ft_sleep_think(t_philo *philo)
{
	if (!ft_write_status(philo, "is sleeping"))
		return (false);
	ft_usleep(philo->args->time2sleep, philo);
	if (!ft_write_status(philo, "is thinking"))
		return (false);
	return (true);
}

void	*proutine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->nbr % 2 == 0)
		ft_usleep(10, philo);
	while (1)
	{
		if (!ft_get_forks(philo))
			break ;
		pthread_mutex_lock(&philo->args->sync_mutex);
		philo->meals_count++;
		philo->last_meal_beginning = ft_now_ms();
		pthread_mutex_unlock(&philo->args->sync_mutex);
		ft_write_status(philo, "is eating");
		ft_usleep(philo->args->time2eat, philo);
		pthread_mutex_lock(&philo->args->sync_mutex);
		if (philo->meals_count == philo->args->max_meals)
			philo->args->total_finished += (philo->args->max_meals != -1);
		pthread_mutex_unlock(&philo->args->sync_mutex);
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		if (!ft_sleep_think(philo))
			break ;
	}
	return (NULL);
}
