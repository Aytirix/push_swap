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

int	rrr(t_info *info, int add_instruction)
{
	int	i;

	i = rra(info, 0) + rrb(info, 0);
	if (i)
	{
		if (add_instruction)
			new_instruction(info, "rrr");
		return (1);
	}
	return (0);
}

void	new_instruction(t_info *info, char *instruction)
{
	char	*buffer;

	buffer = ft_strdup(instruction);
	if (!buffer)
		stop(info, 1);
	ft_lstadd_back(&(info->instruction), ft_lstnew(buffer));
}
