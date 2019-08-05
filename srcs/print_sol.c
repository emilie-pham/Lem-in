/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 16:42:11 by epham             #+#    #+#             */
/*   Updated: 2019/08/05 17:27:41 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void    print_end(t_solution *sol)
{
    int i;

    i = 1;
    while (i <= sol->ants)
    {
        printf("L%d-%s\n", i, sol->path->room->name);
        i++;
    }
}

void    next_step(t_env *env, t_path *head, int *next_ant)
{
    while (ft_strcmp(env->optimal_sol->path->room->name, head->next->room->name))
    {
        if (env->optimal_sol->path->prev)
            env->optimal_sol->path->ant_index = env->optimal_sol->path->prev->ant_index;
        if (!ft_strcmp(env->optimal_sol->path->room->name, env->end->name))
        {                  
            if (env->optimal_sol->ants_arrived < env->optimal_sol->ants_sent)
            {         
                printf("L%d-%s ", env->optimal_sol->path->ant_index, env->optimal_sol->path->room->name);
                env->optimal_sol->ants_arrived++;
            }
        }
        else if (env->optimal_sol->path->ant_index != env->optimal_sol->path->next->ant_index)
            printf("L%d-%s ", env->optimal_sol->path->ant_index, env->optimal_sol->path->room->name);
        env->optimal_sol->path = env->optimal_sol->path->prev;
    }
    if (!ft_strcmp(env->optimal_sol->path->room->name, head->next->room->name) && env->optimal_sol->ants_sent < env->optimal_sol->ants)
    {
        env->optimal_sol->path->ant_index = *next_ant;
        env->optimal_sol->ants_sent++;
        (*next_ant)++;
        printf("L%d-%s ", env->optimal_sol->path->ant_index, env->optimal_sol->path->room->name);
    }
}

void    print_sol(t_env *env)
{
    int         next_ant;
    t_solution  *sol;
    t_path      *head;
    int         steps;

    next_ant = 1;
    sol = env->optimal_sol;
    while (env->steps)
    {
        env->optimal_sol = sol;
        while (env->optimal_sol)
        {
            head = env->optimal_sol->path;
            if (!ft_strcmp(env->optimal_sol->path->room->name, env->start->name))
                env->optimal_sol->path = env->optimal_sol->path->next;
            while (env->optimal_sol->path->ant_index && env->optimal_sol->path->next)
                env->optimal_sol->path = env->optimal_sol->path->next;
            if (!ft_strcmp(head->next->room->name, env->end->name))
                return (print_end(env->optimal_sol));
            next_step(env, head, &next_ant);
            env->optimal_sol->path = head;
            env->optimal_sol = env->optimal_sol->next;
        }
        env->steps--;
        printf("\n");
    }
}
