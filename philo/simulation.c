/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:41:39 by ngaurama          #+#    #+#             */
/*   Updated: 2025/02/03 15:40:49 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	pick_up_forks_debug(t_philo *philo)
// {
// 	if (philo->id % 2 == 0)
// 	{
// 		pthread_mutex_lock(&philo->right_fork->mutex);
// 		log_action(philo, "has taken right fork", CYN);
// 		pthread_mutex_lock(&philo->left_fork->mutex);
// 		log_action(philo, "has taken left fork", CYN);
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(&philo->left_fork->mutex);
// 		log_action(philo, "has taken left fork", CYN);
// 		pthread_mutex_lock(&philo->right_fork->mutex);
// 		log_action(philo, "has taken right fork", CYN);
// 	}
// }

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

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_time_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->meal_time_mutex);
	log_action(philo, "is eating", GRNB);
	precise_sleep(philo->simulation->time_eat, philo);
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
	precise_sleep(philo->simulation->time_sleep, philo);
}

// void de_sync(t_philo *philo)
// {
// 	if (philo->simulation->num_phi % 2 == 0)
// 	{
// 		if (philo->id % 2 == 0)
// 			precise_sleep(3);
// 	}
// 	else
// 	{
// 		if (philo->id % 2)
// 			thinking(philo, 1);
// 	}
//	put this in routine if you need: de_sync(philo); before loop
//	and: thinking(philo, 0); in loop after first if
// }

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (is_simulation_over(philo))
			break ;
		log_action(philo, "is thinking", WHT);
		if (is_simulation_over(philo))
			break ;
		pick_up_forks(philo);
		if (is_simulation_over(philo))
		{
			put_down_forks(philo);
			break ;
		}
		eat(philo);
		put_down_forks(philo);
		if (is_simulation_over(philo))
			break ;
		sleep_philo(philo);
	}
	return (NULL);
}
