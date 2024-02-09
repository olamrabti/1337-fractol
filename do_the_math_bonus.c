/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_the_math_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:26:10 by olamrabt          #+#    #+#             */
/*   Updated: 2024/02/09 16:58:24 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

void	ft_do_the_math(t_mlx *frct, t_func_var *var)
{
	int		i;
	int		color;
	double	temp;

	i = 0;
	color = CLR1;
	while (i++ <= frct->iter)
	{
		temp = var->ar;
		var->ar = var->ar * var->ar - var->ai * var->ai + var->cr;
		var->ai = 2. * temp * var->ai + var->ci;
		if (var->ar * var->ar + var->ai * var->ai >= 4)
		{
			color = abs(CLR1 - (frct->iter - i) * 1200);
			my_mlx_pixel_put(frct, var->x, var->y, color);
			break ;
		}
		if (i == frct->iter)
			my_mlx_pixel_put(frct, var->x, var->y, BLACK);
	}
}

void	ft_do_bs_math(t_mlx *frct, t_func_var *var)
{
	int		i;
	int		color;
	double	temp;

	i = 0;
	color = BLUE;
	while (i++ <= frct->iter)
	{
		temp = var->ar;
		var->ar = fabs(var->ar * var->ar - var->ai * var->ai + var->cr);
		var->ai = fabs(2. * temp * var->ai + var->ci);
		if (var->ar * var->ar + var->ai * var->ai >= 4)
		{
			color = abs(BLUE - (frct->iter - i) * 1000);
			my_mlx_pixel_put(frct, var->x, var->y, color);
			break ;
		}
		if (i == frct->iter)
			my_mlx_pixel_put(frct, var->x, var->y, BLACK);
	}
}
