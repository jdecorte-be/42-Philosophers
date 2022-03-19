/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:27:39 by jdecorte          #+#    #+#             */
/*   Updated: 2022/03/19 14:08:44 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *check_death(void *phi)
{
    t_philo *philo = (t_philo *)phi;
    int i = 0;
    while(!philo->info.stop)
    {
        i = 0;
        while(i < philo->info.n_philo)
        {
            if (timestamp() > philo[i].last_eat + philo[i].info.t_die)
            {
                pthread_mutex_lock(&philo[i].info.print);
                printf("%lld %d died\n", timestamp(), i + 1);
                philo->info.stop = 1;
                pthread_mutex_unlock(&philo[i].info.print);
                return NULL;
            }
            i++;
        }
        usleep(1000);
    }
}

// pthread_create --> thinking
void philo_init(t_info *data)
{
    pthread_t t1;
    t_philo philo[data->n_philo];
    int i;

    i = 0;
    while(i < data->n_philo)
    {
        philo[i].n = i + 1;
        philo[i].info = *data;
        philo[i].last_eat = 0;
        if (pthread_create(&t1, NULL, &philo_life, &(philo[i])) != 0)
            perror("pthread_create");
        pthread_detach(t1);
        usleep(100);
        i++;
    }
    if (pthread_create(&t1, NULL, &check_death, (void *)philo) != 0)
        perror("pthread_create");
    pthread_detach(t1);
}

void var_init(t_info *data, char **av)
{
    pthread_mutex_init(&data->print, NULL);
    data->stop = 0;
    data->n_philo = ft_atoi(av[1]);
    data->t_die = ft_atoi(av[2]);
    data->t_eat = ft_atoi(av[3]);
    data->t_sleep = ft_atoi(av[4]);
    if(av[5])
        data->n_eat = ft_atoi(av[5]);
    
}