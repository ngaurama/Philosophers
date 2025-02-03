/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:06:07 by ngaurama          #+#    #+#             */
/*   Updated: 2025/02/03 14:39:12 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "ansi_colors.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				fork_id;
}					t_fork;

typedef struct s_simulation
{
	int				num_phi;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_must_eat;
	int				simul_over;
	pthread_mutex_t	simul_over_mutex;
	long			start_time;
	pthread_mutex_t	print_mutex;
	t_fork			*forks;
	struct s_philo	*philosophers;
}					t_simulation;

typedef struct s_philo
{
	int				id;
	int				times_eaten;
	long			last_meal_time;
	pthread_mutex_t	meal_time_mutex;
	pthread_mutex_t	times_eaten_mutex;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_simulation	*simulation;
	pthread_t		thread;
}					t_philo;

// Design
void				print_intro(void);
void				print_summary(t_simulation *simulation, int i);
void				print_simulation_details(t_simulation *simulation);

// inits
int					init_forks(t_simulation *simul);
int					init_philosophers(t_simulation *simul);
int					init_philo(t_simulation *simul);
int					check_specifics(int argc, t_simulation *simulation);
int					init_input(char **argv, int argc, t_simulation *simulation);

// Philo utils
long				get_time(void);
void				precise_sleep(long duration_ms, t_philo *philo);
void				log_action(t_philo *philo, const char *action, char *color);
int					is_simulation_over(t_philo *philo);
// simulation
void				pick_up_forks(t_philo *philo);
void				eat(t_philo *philo);
void				put_down_forks(t_philo *philo);
void				sleep_philo(t_philo *philo);
void				*philosopher_routine(void *arg);

// monitor
void				*monitor_philosopher(t_simulation *simulation, int i,
						int *all_satisfied);
void				*monitor_simulation(void *arg);

// Start and clean
int					start_threads(t_simulation *simulation);
void				cleanup_simulation(t_simulation *simulation);
int					single_philo(t_simulation *simulation);

// Utils
int					ft_atoi(const char *str);

#endif
