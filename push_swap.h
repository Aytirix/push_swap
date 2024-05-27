/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <thmouty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:14:10 by thmouty           #+#    #+#             */
/*   Updated: 2024/05/15 02:36:14 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "Libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_info
{
	t_list	*a;
	t_list	*b;
	t_list	*instruction;
	int		*temp;
}			t_info;

// push_swap
void		controller(int ac, char **av, t_info *info);
void		check_exist(t_info *info, char **av, int i);

// Instruction 1
int			sa(t_info *info, int add_instruction);
int			sb(t_info *info, int add_instruction);
int			ss(t_info *info, int add_instruction);
int			pa(t_info *info, int add_instruction);
int			pb(t_info *info, int add_instruction);

// Instruction 2
int			ra(t_info *info, int add_instruction);
int			rb(t_info *info, int add_instruction);
int			rr(t_info *info, int add_instruction);
int			rra(t_info *info, int add_instruction);
int			rrb(t_info *info, int add_instruction);

// Instruction 3
int			rrr(t_info *info, int add_instruction);
void		new_instruction(t_info *info, char *instruction);

// tools
void		stop(t_info *info, int error);
void		print_list(t_list *list, char format);

#endif