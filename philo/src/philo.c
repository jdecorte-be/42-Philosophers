#include "philo.h"

void *check_death(void *phi)
{
    t_philo *philo = (t_philo *)phi;

    ft_usleep(philo->info->t_die + 1);
    pthread_mutex_lock(&philo->info->m_eat);
    pthread_mutex_lock(&philo->info->m_stop);
    if(!is_dead(philo, 0) && timestamp() - philo->last_eat >= (long)(philo->info->t_die))
    {
        pthread_mutex_unlock(&philo->info->m_eat);
        pthread_mutex_unlock(&philo->info->m_stop);
        pthread_mutex_lock(&(philo->info->print));
        print(philo, " died\n");
        pthread_mutex_unlock(&philo->info->print);
        is_dead(philo, 1);
        return NULL;
    }
    pthread_mutex_unlock(&philo->info->m_eat);
    pthread_mutex_unlock(&philo->info->m_stop);
    return NULL;
}

// ? OK
void take_fork(t_philo *philo)
{
    pthread_mutex_lock(&(philo->fork_l));
    pthread_mutex_lock(&(philo->info->print));
    print(philo, " has taken a fork\n");
    pthread_mutex_unlock(&(philo->info->print));
    if (!philo->fork_r)
    {
        ft_usleep(philo->info->t_die * 2);
        return ;
    }
    pthread_mutex_lock((philo->fork_r));
    pthread_mutex_lock(&(philo->info->print));
    print(philo, " has taken a fork\n");
    pthread_mutex_unlock(&(philo->info->print));
}

// ? OK
void philo_eat(t_philo *philo)
{

    pthread_mutex_lock(&(philo->info->print));
    print(philo, " is eating\n");
    pthread_mutex_lock(&(philo->info->m_eat));
    philo->last_eat = timestamp();
    // philo->info->m_count++;
    pthread_mutex_unlock(&(philo->info->m_eat));
    pthread_mutex_unlock(&(philo->info->print));

    ft_usleep(philo->info->t_eat);
    pthread_mutex_unlock((philo->fork_r));
    pthread_mutex_unlock(&(philo->fork_l));

    pthread_mutex_lock(&(philo->info->print));
    print(philo, " is sleeping\n");
    pthread_mutex_unlock(&(philo->info->print));
    ft_usleep(philo->info->t_sleep);
    pthread_mutex_lock(&(philo->info->print));
    print(philo, " is thinking\n");
    pthread_mutex_unlock(&(philo->info->print));
}

// ! OK
void    *philo_life(void *phi)
{
    pthread_t t;
    t_philo *philo = (t_philo *)phi;

    if(philo->n % 2 == 0)
        ft_usleep(philo->info->t_eat / 10);
    while(!is_dead(philo, 0)) 
    {
        pthread_create(&t, NULL, check_death, phi);
        take_fork(philo);
        philo_eat(philo);
        pthread_detach(t);

        // if(philo->info->m_count == philo->info->n_eat)
        // {
        //     pthread_mutex_lock(&philo->info->m_stop);
        //     philo->info->stop = 1;

        //     is_dead(philo, 2);
        //     pthread_mutex_unlock(&philo->info->m_stop);
        //     return NULL;
        // }
    }
    return NULL;
}