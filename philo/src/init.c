/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte <jdecorte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:27:39 by jdecorte          #+#    #+#             */
/*   Updated: 2022/03/02 11:53:11 by jdecorte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// pthread_create --> thinking
void philo_init(t_info *data)
{
    pthread_t t1[data->n_philo];
    t_philo philo[data->n_philo];
    int i;

    i = 0;
    while(i < data->n_philo)
    {
        philo[i].n = i;
        philo[i].info = data;
        philo[i].t_eat = data->t_eat;
        philo[i].t_sleep = data->t_sleep;
        if (pthread_create(&t1[i], NULL, &philo_life, &(philo[i])) != 0)
            perror("pthread_create");
        printf("%lld %d is thinking\n", timestamp(), philo[i].n + 1);
        i++;
    }
    check_death(data, philo);
    i = -1;
    while(++i < data->n_philo)
    {
        if (pthread_join(t1[i], NULL) != 0)
            perror("pthread_create");
    }
}

void var_init(t_info *data, char **av)
{
    data->n_philo = ft_atoi(av[1]);
    data->t_die = ft_atoi(av[2]);
    data->t_eat = ft_atoi(av[3]);
    data->t_sleep = ft_atoi(av[4]);
    if(av[5])
        data->n_eat = ft_atoi(av[5]);  
    
}