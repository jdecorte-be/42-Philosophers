#include "philo.h"

// ? OK
void	ft_usleep(int ms)
{
	long	time;

	time = timestamp();
	usleep(ms * 920);
	while (timestamp() < time + ms)
		usleep(ms * 3);
}


// ? OK
void take_fork(t_philo *philo)
{
    pthread_mutex_lock(&(philo->fork_r));      // ! here
    print(philo, " has taken a fork\n");
    pthread_mutex_lock(&(philo->fork_l));       // ! here
    print(philo, " has taken a fork\n");
}

// ? OK
void philo_eat(t_philo *philo)
{
    print(philo, " is eating\n");
    philo->last_eat = timestamp();
    ft_usleep(philo->info->t_eat);
    philo->m_count++;
    pthread_mutex_unlock(&(philo->fork_l));    // ! here
    pthread_mutex_unlock(&(philo->fork_r));   // ! here
}

// ? OK
void    *philo_life(void *phi)
{
    t_philo *philo = (t_philo *)phi;
    philo->last_eat = timestamp();
    int i = 0;

    if(philo->n % 2 != 0)
        ft_usleep(philo->info->t_eat / 10);
    while(philo->info->stop == 0 && !philo->info->n_eat || i < philo->info->n_eat)
    {
        take_fork(philo);
        philo_eat(philo);
        print(philo, " is sleeping\n");
        ft_usleep(philo->info->t_sleep);
        print(philo, " is thinking\n");
        i++;
    }
}