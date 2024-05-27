/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <thmouty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:14:44 by thmouty           #+#    #+#             */
/*   Updated: 2024/05/15 02:35:28 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	stop(t_info *info, int error)
{
	if (error)
		ft_printf("Error\n");
	free(info->temp);
	ft_lstclear(&info->a, free);
	ft_lstclear(&info->b, free);
	ft_lstclear(&info->instruction, free);
	exit(error);
}

void	print_list(t_list *list, char format)
{
	t_list	*temp;

	temp = list;
	while (temp)
	{
		if (format == 'd')
			ft_printf("%d\n", *(int *)temp->content);
		else if (format == 's')
			ft_printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
}
