/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:27:39 by jdecorte          #+#    #+#             */
/*   Updated: 2022/03/28 11:38:12 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int philo_init(t_info *data)
{
    
    int i;
    data->stop = 0;
    data->t_start = timestamp();
    data->philo = malloc(sizeof(t_philo) * data->n_philo);
    i = 0;
    while(i < data->n_philo)
    {
        data->philo[i].n = i + 1;
        data->philo[i].last_eat = 0;
        data->philo[i].fork_r = NULL;
        data->philo[i].info = data;
        pthread_mutex_init(&(data->philo[i].fork_l), NULL);
        if(data->n_philo == 1)
            return 1;
        if(i == data->n_philo - 1)
            data->philo[i].fork_r = &data->philo[0].fork_l;
        else
            data->philo[i].fork_r = &data->philo[i + 1].fork_l;
        if (pthread_create(&data->philo[i].thread, NULL, &philo_life, &(data->philo[i])) != 0)
            perror("pthread_create");
        i++;
    }
    i = 0;
    while(i < data->n_philo)
    {
        if(pthread_join(data->philo[i].thread, NULL) != 0)
            perror("pthread_create");
        i++;
    }
    return 0;
}

void var_init(t_info *data, char **av)
{
    pthread_mutex_init(&data->print, NULL);
    pthread_mutex_init(&data->m_stop, NULL);
    pthread_mutex_init(&data->m_eat, NULL);
    pthread_mutex_init(&data->dead, NULL);


    data->stop = 0;
    data->m_count = 0;
    data->n_philo = ft_atoi(av[1]);
    data->t_die = ft_atoi(av[2]);
    data->t_eat = ft_atoi(av[3]);
    data->t_sleep = ft_atoi(av[4]);
    if(av[5])
        data->n_eat = ft_atoi(av[5]);
    
}