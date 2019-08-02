/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 14:36:38 by epham             #+#    #+#             */
/*   Updated: 2019/08/02 15:24:15 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		ants_to_send(t_env *env, t_solution *head)
{
	t_solution *sol;

	sol = head;
	while (sol)
	{
		sol->ants = (env->ant_nb + env->total_len) / env->path_nb - sol->pathlen;
		printf("NUMBER OF ANTS FOR THIS PATH : %d\n", sol->ants);
		sol = sol->next;
	}
}
