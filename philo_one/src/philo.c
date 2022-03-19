#include "philo.h"

void init_mutex(t_philo *philo)
{
    pthread_mutex_init(&philo->fork_r, NULL); 
    pthread_mutex_init(&philo->fork_l, NULL);
    pthread_mutex_init(&philo->m_check, NULL); 
}

void take_fork(t_philo *philo)
{
    if(philo->n % 2 == 0 && philo->n + 1 == philo->info.n_philo)
    {
        pthread_mutex_lock(&philo->fork_r);     // ! here
        pthread_mutex_lock(&philo->fork_l);     // ! here
    }
    else
    {
        pthread_mutex_lock(&philo->fork_l);     // ! here
        pthread_mutex_lock(&philo->fork_r);      // ! here
    }
    print(philo, " has taken a fork\n");
    print(philo, " has taken a fork\n");
}

void philo_eat(t_philo *philo)
{
    philo->is_eating = 1;
    philo->last_eat = timestamp();
    print(philo, " is eating\n");
    usleep(philo->info.t_eat * 1000);
    philo->is_eating = 0;
    pthread_mutex_unlock(&philo->fork_r);   // ! here
    pthread_mutex_unlock(&philo->fork_l);    // ! here
}

void    *philo_life(void *phi)
{
    t_philo *philo = (t_philo *)phi;
    philo->last_eat = timestamp();
    int i = 0;
    while(!philo->info.stop) // !philo->info->n_eat || i < philo->info->n_eat
    {
        take_fork(philo);
        philo_eat(philo);
        print(philo, " is sleeping\n");
        usleep(philo->info.t_sleep * 1000);
    
    }
}