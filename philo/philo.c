/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 19:21:32 by ngaurama          #+#    #+#             */
/*   Updated: 2024/12/23 20:36:45 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_philo t_philo;

typedef struct s_fork {
    pthread_mutex_t mutex;
    long fork_id;
} t_fork;

typedef struct s_simulation {
    long num_phi;
    long time_die;
    long time_eat;
    long time_sleep;
    long num_must_eat;
    long simul_over;
    long start_time;
    long threads_ready;
    pthread_mutex_t print_mutex;
    t_fork *forks;
    t_philo *philosophers;
} t_simulation;

typedef struct s_philo {
    long id;
    long times_eaten;
    long last_meal_time;
    long full;
    pthread_mutex_t meal_time_mutex;
    pthread_mutex_t times_eaten_mutex;
    pthread_mutex_t philo_mutex;
    t_fork *left_fork;
    t_fork *right_fork;
    pthread_t thread_id;
    t_simulation *simulation;
} t_philo;

// Get time in milliseconds
long get_time_millis() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000); // milliseconds
}

// Get time in microseconds
long get_time_micros() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000000) + time.tv_usec; // microseconds
}

// Read a value from a shared resource with mutex locking
long get_long(pthread_mutex_t *mutex, long *value) {
    long ret;
    pthread_mutex_lock(mutex);
    ret = *value;
    pthread_mutex_unlock(mutex);
    return ret;
}

// Set a value to a shared resource with mutex locking
void set_long(pthread_mutex_t *mutex, long *dest, long value) {
    pthread_mutex_lock(mutex);
    *dest = value;
    pthread_mutex_unlock(mutex);
}

// Check if the simulation is over
long sim_fin(t_simulation *sim) {
    return (get_long(&sim->print_mutex, &sim->simul_over));
}

// Sleep with high precision, checking if simulation should end
void precise_usleep(long usec, t_simulation *sim) {
    long start = get_time_micros(); // Get start time in microseconds
    while (get_time_micros() - start < usec) {
        if (sim_fin(sim)) break;
        usleep(100); // Sleep for smaller time units
    }
}

// Log function to print activity messages
void print_log(t_philo *philo, char *message) {
    pthread_mutex_lock(&philo->simulation->print_mutex);
    
    if (!philo->simulation->simul_over || strcmp(message, "died") == 0) {
        long current_time = get_time_millis() - philo->simulation->start_time; // Time in milliseconds
        if (current_time < 0) {
            printf("Error: Negative time encountered.\n");
            exit(1);
        }
        printf("%ld %ld %s\n", current_time, philo->id, message);
    }

    pthread_mutex_unlock(&philo->simulation->print_mutex);
}

// Function for philosophers to eat
static void eat(t_philo *philo) {
    pthread_mutex_lock(&philo->left_fork->mutex);
    print_log(philo, "has taken a fork");
    pthread_mutex_lock(&philo->right_fork->mutex);
    print_log(philo, "has taken a fork");
    set_long(&philo->philo_mutex, &philo->last_meal_time, get_time_micros()); // Store last meal time in microseconds
    philo->times_eaten++;
    print_log(philo, "is eating");
    precise_usleep(philo->simulation->time_eat * 1000, philo->simulation); // Convert time_eat to microseconds
    pthread_mutex_unlock(&philo->right_fork->mutex);
    pthread_mutex_unlock(&philo->left_fork->mutex);
}

// Function for philosophers to sleep
static void sleep_philo(t_philo *philo) {
    print_log(philo, "is sleeping");
    precise_usleep(philo->simulation->time_sleep * 1000, philo->simulation); // Convert time_sleep to microseconds
}

// Function for philosophers to think
static void think(t_philo *philo) {
    print_log(philo, "is thinking");
}

// Check if all philosophers have eaten the required number of times
int check_all_ate(t_simulation *sim) {
    int i;
    if (sim->num_must_eat == -1)
        return 0;
    for (i = 0; i < sim->num_phi; i++) {
        pthread_mutex_lock(&sim->philosophers[i].times_eaten_mutex);
        if (sim->philosophers[i].times_eaten < sim->num_must_eat) {
            pthread_mutex_unlock(&sim->philosophers[i].times_eaten_mutex);
            return 0; // Not all philosophers have eaten the required times
        }
        pthread_mutex_unlock(&sim->philosophers[i].times_eaten_mutex);
    }
    return 1; // All philosophers have eaten the required number of times
}

// Function for the philosopher thread
void *philosopher(void *arg) {
    t_philo *philo = (t_philo *)arg;
    t_simulation *sim = philo->simulation;

    // Initialization
    pthread_mutex_lock(&sim->print_mutex);
    sim->threads_ready++;
    if (sim->threads_ready == sim->num_phi) {
        sim->start_time = get_time_millis();
    }
    pthread_mutex_unlock(&sim->print_mutex);

    while (!sim_fin(sim)) {
        if (philo->full) {
            sleep_philo(philo);
            think(philo);
        } else {
            eat(philo);
        }
    }
    return NULL;
}

// Function to initialize the simulation
void init_simulation(t_simulation *sim) {
    long i;

    // Allocate and initialize simulation
    sim->forks = malloc(sizeof(t_fork) * sim->num_phi);
    sim->philosophers = malloc(sizeof(t_philo) * sim->num_phi);
    
    for (i = 0; i < sim->num_phi; i++) {
        pthread_mutex_init(&sim->forks[i].mutex, NULL);
        sim->forks[i].fork_id = i;
        pthread_mutex_init(&sim->philosophers[i].meal_time_mutex, NULL);
        pthread_mutex_init(&sim->philosophers[i].times_eaten_mutex, NULL);
        pthread_mutex_init(&sim->philosophers[i].philo_mutex, NULL);
        sim->philosophers[i].id = i + 1;
        sim->philosophers[i].times_eaten = 0;
        sim->philosophers[i].last_meal_time = 0;
        sim->philosophers[i].full = 0;
        sim->philosophers[i].simulation = sim;
        sim->philosophers[i].left_fork = &sim->forks[i];
        sim->philosophers[i].right_fork = &sim->forks[(i + 1) % sim->num_phi];
    }

    pthread_mutex_init(&sim->print_mutex, NULL);
    sim->simul_over = 0;
    sim->threads_ready = 0;
}

// Function to cleanup the simulation
void cleanup_simulation(t_simulation *sim) {
    long i;
    for (i = 0; i < sim->num_phi; i++) {
        pthread_mutex_destroy(&sim->forks[i].mutex);
        pthread_mutex_destroy(&sim->philosophers[i].meal_time_mutex);
        pthread_mutex_destroy(&sim->philosophers[i].times_eaten_mutex);
        pthread_mutex_destroy(&sim->philosophers[i].philo_mutex);
    }
    pthread_mutex_destroy(&sim->print_mutex);
    free(sim->forks);
    free(sim->philosophers);
}

int main(int argc, char **argv) {
    t_simulation sim;

    if (argc < 5) {
        printf("Usage: ./philosophers num_phi time_die time_eat time_sleep [num_must_eat]\n");
        return 1;
    }

    sim.num_phi = atoi(argv[1]);
    sim.time_die = atoi(argv[2]);
    sim.time_eat = atoi(argv[3]);
    sim.time_sleep = atoi(argv[4]);
    sim.num_must_eat = (argc > 5) ? atoi(argv[5]) : -1;

    init_simulation(&sim);

    // Create philosopher threads
    long i;
    for (i = 0; i < sim.num_phi; i++) {
        pthread_create(&sim.philosophers[i].thread_id, NULL, philosopher, &sim.philosophers[i]);
    }

    // Wait for threads to finish
    for (i = 0; i < sim.num_phi; i++) {
        pthread_join(sim.philosophers[i].thread_id, NULL);
    }

    cleanup_simulation(&sim);
    return 0;
}
