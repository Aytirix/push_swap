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
		write(2, "Error\n", 6);
	free_info(info);
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

t_info	dup_info(t_info *info, int dup_instruction)
{
	t_info	pinfo;

	pinfo.instruction = NULL;
	pinfo.temp = NULL;
	pinfo.a = ft_lstdup_d(info->a);
	if (!pinfo.a)
		stop(info, 1);
	pinfo.b = ft_lstdup_d(info->b);
	if (!pinfo.b)
		stop(info, 1);
	if (dup_instruction)
	{
		pinfo.instruction = ft_lstdup_s(info->instruction);
		if (!pinfo.instruction)
			stop(info, 1);
	}
	return (pinfo);
}

void	free_info(t_info *info)
{
	ft_lstclear(&info->a, free);
	ft_lstclear(&info->b, free);
	ft_lstclear(&info->instruction, free);
}
