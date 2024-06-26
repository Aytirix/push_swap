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
	int		len_a;
	int		len_b;
	int		min;
	int		max;
	int		*max3;
}			t_info;

typedef struct s_cost
{
	int		rot_common;
	int		rota;
	int		rotb;
}			t_cost;

// Algo1
void		algo(t_info *info);
void		algo3(t_info *info, t_list *list);
void		algo5(t_info *info);

// AlgoTurk
void		calcul_place_in(t_info *info, char stack, int val, t_cost *cost);
void		initialize_algo(t_info *info);

// AlgoTurk_Utils
t_list		*get_max(t_list *lst);
t_list		*get_min(t_list *lst);
void		best_rotation_to_top(t_info *info, t_cost *cost, char stack,
				int target_index);
void		execute_rotation(t_info *info, t_cost *cost);
void		calcul_fusion(t_cost *cost);

// controller
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

// Checker
int			execute_instruction(t_info *info, int instruction,
				int (**ins)(t_info *info, int instruction), int len);
int			check_sorted(t_list *list);

// tools
void		stop(t_info *info, int error);
void		print_list(t_list *list, char format);
void		free_info(t_info *info);
void		info_update(t_info *info);

#endif