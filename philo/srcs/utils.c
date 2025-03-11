/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguenzao <aguenzao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:11:12 by aguenzao          #+#    #+#             */
/*   Updated: 2025/03/11 14:23:00 by aguenzao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_isspace(int c)
{
	if (c != '\t' && c != '\n' && c != '\v' \
		&& c != '\f' && c != '\r' && c != ' ')
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	size_t		i;
	long int	sum;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	sum = 0;
	while (str[i])
	{
		sum = sum * 10 + (str[i] - '0');
		i++;
	}
	return (sum);
}

static int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}

bool    ft_isint(char *str)
{
    int		i;
    long    num;

    i = 0;
    num = 0;
    if (!str[i])
        return (false);
    if (str[i] == '+')
        i++;
	else if(str[i] == '-')
		return (false);
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (false);
        num = (num * 10) + (str[i] - '0');
        if (num > INT_MAX)
            return (false);
		if(num == 0)
			return (false);
        i++;
    }
    return (true);
}
