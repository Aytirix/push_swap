/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <thmouty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:14:49 by thmouty           #+#    #+#             */
/*   Updated: 2024/05/15 04:05:20 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	sa(t_info *info, int add_instruction)
{
	if (info->a && info->a->next)
	{
		ft_lstswap(&(info->a), &(info->a->next));
		if (add_instruction)
			new_instruction(info, "sa");
		return (1);
	}
	return (0);
}

int	sb(t_info *info, int add_instruction)
{
	if (info->b && info->b->next)
	{
		ft_lstswap(&(info->b), &(info->b->next));
		if (add_instruction)
			new_instruction(info, "sb");
		return (1);
	}
	return (0);
}

int	ss(t_info *info, int add_instruction)
{
	int	i;

	i = sa(info, 0) + sb(info, 0);
	if (i)
	{
		if (add_instruction)
			new_instruction(info, "ss");
		return (1);
	}
	return (0);
}

int	pa(t_info *info, int add_instruction)
{
	t_list	*temp;

	if (info->b)
	{
		temp = info->b;
		info->b = info->b->next;
		ft_lstadd_front(&(info->a), temp);
		info_update(info);
		if (add_instruction)
			new_instruction(info, "pa");
		return (1);
	}
	return (0);
}

int	pb(t_info *info, int add_instruction)
{
	t_list	*temp;

	if (info->a)
	{
		temp = info->a;
		info->a = info->a->next;
		ft_lstadd_front(&(info->b), temp);
		info_update(info);
		if (add_instruction)
			new_instruction(info, "pb");
		return (1);
	}
	return (0);
}
