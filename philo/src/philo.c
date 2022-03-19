#include "philo.h"

void	ft_usleep(int msec)
{
	unsigned long	time;

	time = timestamp();
	while (timestamp() < time + msec)
		usleep(1);
}

void take_fork(t_philo *philo)
{
    pthread_mutex_lock(&(philo->fork_r));      // ! here
    print(philo, " has taken a fork\n");
    pthread_mutex_lock(&(philo->fork_l));       // ! here
    print(philo, " has taken a fork\n");
}

void philo_eat(t_philo *philo)
{
    philo->last_eat = timestamp();
    print(philo, " is eating\n");
    ft_usleep(philo->info->t_eat);
    pthread_mutex_unlock(&(philo->fork_l));    // ! here
    pthread_mutex_unlock(&(philo->fork_r));   // ! here
}

void    *philo_life(void *phi)
{
    t_philo *philo = (t_philo *)phi;
    philo->last_eat = timestamp();
    int i = 0;

    if(philo->n % 2 != 0)
        ft_usleep(philo->info->t_eat / 10);
    while(philo->info->stop == 0) // !philo->info->n_eat || i < philo->info->n_eat
    {
        take_fork(philo);
        philo_eat(philo);
        print(philo, " is sleeping\n");
        ft_usleep(philo->info->t_sleep);
        print(philo, " is thinking\n");
    }
}