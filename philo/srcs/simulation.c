/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:41:39 by ngaurama          #+#    #+#             */
/*   Updated: 2025/01/21 20:23:41 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_up_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		log_action(philo, "has taken a fork", CYN);
		pthread_mutex_lock(&philo->left_fork->mutex);
		log_action(philo, "has taken a fork", CYN);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		log_action(philo, "has taken a fork", CYN);
		pthread_mutex_lock(&philo->right_fork->mutex);
		log_action(philo, "has taken a fork", CYN);
	}
}

void pick_up_forks_debug(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->right_fork->mutex);
        log_action(philo, "has taken right fork", CYN);
        pthread_mutex_lock(&philo->left_fork->mutex);
        log_action(philo, "has taken left fork", CYN);
    }
    else
    {
        pthread_mutex_lock(&philo->left_fork->mutex);
        log_action(philo, "has taken left fork", CYN);
        pthread_mutex_lock(&philo->right_fork->mutex);
        log_action(philo, "has taken right fork", CYN);
    }
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_time_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->meal_time_mutex);
	log_action(philo, "is eating", GRNB);
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
	log_action(philo, "is sleeping", MAG);
	precise_sleep(philo->simulation->time_sleep);
}

int is_simul_over(t_simulation *simulation)
{
    int result;

    pthread_mutex_lock(&simulation->simul_over_mutex);
    result = simulation->simul_over;
    pthread_mutex_unlock(&simulation->simul_over_mutex);

    return result;
}

void set_simul_over(t_simulation *simulation, int value)
{
    pthread_mutex_lock(&simulation->simul_over_mutex);
    simulation->simul_over = value;
    pthread_mutex_unlock(&simulation->simul_over_mutex);
}

void *philosopher_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (!is_simul_over(philo->simulation))
    {
        think(philo);
        if (is_simul_over(philo->simulation))
            break;
        if (DEBUG)
            pick_up_forks_debug(philo);
        else
            pick_up_forks(philo);
        if (is_simul_over(philo->simulation))
        {
            put_down_forks(philo);
            break;
        }
        eat(philo);
        put_down_forks(philo);
        if (is_simul_over(philo->simulation))
            break;
        sleep_philo(philo);
    }
    return (NULL);
}

// void	*philosopher_routine(void *arg)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)arg;
// 	while (!philo->simulation->simul_over)
// 	{
// 		think(philo);
// 		if (philo->simulation->simul_over)
// 			break ;
// 		pick_up_forks(philo);
// 		if (philo->simulation->simul_over)
// 		{
// 			put_down_forks(philo);
// 			break ;
// 		}
// 		eat(philo);
// 		put_down_forks(philo);
// 		if (philo->simulation->simul_over)
// 			break ;
// 		sleep_philo(philo);
// 	}
// 	return (NULL);
// }
