/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:41:39 by ngaurama          #+#    #+#             */
/*   Updated: 2025/01/21 17:29:46 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void debug_fork(t_philo *philo, char *fork_side)
{
    if (DEBUG)
        printf("Philosopher %d picked up %s fork\n", philo->id, fork_side);
}

// void	pick_up_forks(t_philo *philo)
// {
// 	if (philo->id % 2 == 0)
// 	{
// 		pthread_mutex_lock(&philo->right_fork->mutex);
// 		log_action(philo, "has taken a fork");
// 		pthread_mutex_lock(&philo->left_fork->mutex);
// 		log_action(philo, "has taken a fork");
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(&philo->left_fork->mutex);
// 		log_action(philo, "has taken a fork");
// 		pthread_mutex_lock(&philo->right_fork->mutex);
// 		log_action(philo, "has taken a fork");
// 	}
// }

void pick_up_forks(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->right_fork->mutex);
        if (DEBUG)
            log_action(philo, "has taken right fork");
        else
            log_action(philo, "has taken a fork");
        pthread_mutex_lock(&philo->left_fork->mutex);
        if (DEBUG)
            log_action(philo, "has taken left fork");
        else
            log_action(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(&philo->left_fork->mutex);
        if (DEBUG)
            log_action(philo, "has taken left fork");
        else
            log_action(philo, "has taken a fork");
        pthread_mutex_lock(&philo->right_fork->mutex);
        if (DEBUG)
            log_action(philo, "has taken right fork");
        else 
            log_action(philo, "has taken a fork");
    }
}


void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_time_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->meal_time_mutex);
	log_action(philo, "is eating");
	precise_sleep(philo->simulation->time_eat);
	pthread_mutex_lock(&philo->times_eaten_mutex);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->times_eaten_mutex);
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

void	sleep_philo(t_philo *philo)
{
	log_action(philo, "is sleeping");
	precise_sleep(philo->simulation->time_sleep);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->simulation->simul_over)
	{
		think(philo);
		if (philo->simulation->simul_over)
			break ;
		pick_up_forks(philo);
		if (philo->simulation->simul_over)
		{
			put_down_forks(philo);
			break ;
		}
		eat(philo);
		put_down_forks(philo);
		if (philo->simulation->simul_over)
			break ;
		sleep_philo(philo);
	}
	return (NULL);
}
