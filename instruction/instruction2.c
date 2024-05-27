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

int	ra(t_info *info, int add_instruction)
{
	t_list	*temp;
	t_list	*last;

	if (info->a && info->a->next)
	{
		temp = info->a;
		info->a = temp->next;
		last = ft_lstlast(temp);
		last->next = temp;
		temp->next = NULL;
		if (add_instruction)
			new_instruction(info, "ra");
		return (1);
	}
	return (0);
}

int	rb(t_info *info, int add_instruction)
{
	t_list	*temp;
	t_list	*last;

	if (info->b && info->b->next)
	{
		temp = info->b;
		info->b = temp->next;
		last = ft_lstlast(temp);
		last->next = temp;
		temp->next = NULL;
		if (add_instruction)
			new_instruction(info, "rb");
		return (1);
	}
	return (0);
}

int	rr(t_info *info, int add_instruction)
{
	int	i;

	i = ra(info, 0) + rb(info, 0);
	if (i)
	{
		if (add_instruction)
			new_instruction(info, "rr");
		return (1);
	}
	return (0);
}

int	rra(t_info *info, int add_instruction)
{
	t_list	*temp;
	t_list	*last;

	if (info->a && info->a->next)
	{
		temp = info->a;
		last = ft_lstlast(temp);
		ft_lstprev(temp)->next = NULL;
		info->a = last;
		last->next = temp;
		if (add_instruction)
			new_instruction(info, "rra");
		return (1);
	}
	return (0);
}

int	rrb(t_info *info, int add_instruction)
{
	t_list	*temp;
	t_list	*last;

	if (info->b && info->b->next)
	{
		temp = info->b;
		last = ft_lstlast(temp);
		ft_lstprev(temp)->next = NULL;
		info->b = last;
		last->next = temp;
		if (add_instruction)
			new_instruction(info, "rrb");
		return (1);
	}
	return (0);
}
