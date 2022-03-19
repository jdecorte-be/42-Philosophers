/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:27:39 by jdecorte          #+#    #+#             */
/*   Updated: 2022/03/19 17:21:23 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void check_death(t_info *data)
{
    int i = 0;
    while(!data->stop)
    {
        i = 0;
        while(i < data->n_philo && !data->stop)
        {
            if (timestamp() > data->philo[i].last_eat + data->t_die)
            {
                printf("%lld %d died\n", timestamp(), i + 1);
                pthread_mutex_lock(&data->print);
                data->stop = 1;
                return ;
            }
            i++;
        }
        usleep(1000);
    }
}

// pthread_create --> thinking
void philo_init(t_info *data)
{
    int i;

    data->philo = malloc(sizeof(t_philo));
    i = 0;
    while(i < data->n_philo)
    {
        data->philo[i].n = i + 1;
        data->philo[i].info = data;
        data->philo[i].last_eat = 0;
        if (pthread_create(&data->philo[i].thread, NULL, &philo_life, &(data->philo[i])) != 0)
            perror("pthread_create");
        usleep(100);
        i++;
    }
    check_death(data);
    pthread_mutex_unlock(&data->print);
    i = 0;
    while(i < data->n_philo)
    {
        if(pthread_join(data->philo[i].thread, NULL) != 0)
            perror("pthread_create");
        i++;
    }

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