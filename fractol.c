/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:03:23 by olamrabt          #+#    #+#             */
/*   Updated: 2024/02/11 11:06:14 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_mlx_pixel_put(t_mlx *frct, int x, int y, int color)
{
	char	*dst;

	dst = frct->pxl + (y * frct->len + x * (frct->bpp / 8));
	*(unsigned int *)dst = color;
}

void	ft_do_the_math(t_mlx *frct, t_func_var *var)
{
	int		i;
	double	temp;
	int		color;

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
			my_mlx_pixel_put(frct, var->x, (var->y), color);
			break ;
		}
		if (i == frct->iter)
			my_mlx_pixel_put(frct, var->x, (var->y), BLACK);
	}
}

void	draw_mandelbrot(t_mlx *frct)
{
	t_func_var	var;

	var.x = 0;
	while (var.x < WIDTH)
	{
		var.y = 0;
		while (var.y < HEIGHT)
		{
			var.ar = 0;
			var.ai = 0;
			var.cr = ft_interpolate(var.x, -2, 1) * frct->zoom;
			var.ci = ft_interpolate(var.y, -1.5, 1.5) * frct->zoom;
			ft_do_the_math(frct, &var);
			(var.y)++;
		}
		(var.x)++;
	}
}

void	draw_julia(t_mlx *frct)
{
	t_func_var	var;

	var.x = 0;
	var.cr = frct->julia_cr;
	var.ci = frct->julia_ci;
	while (var.x < WIDTH)
	{
		var.y = 0;
		while (var.y < HEIGHT)
		{
			var.ar = ft_interpolate(var.x, 2, -2) * frct->zoom;
			var.ai = ft_interpolate(var.y, -2, 2) * frct->zoom;
			ft_do_the_math(frct, &var);
			(var.y)++;
		}
		(var.x)++;
	}
}

int	main(int ac, char *av[])
{
	t_mlx	frct;

	if (!check_params(ac, av, &frct))
	{
		frct.iter = MAX_ITER;
		frct.zoom = 1;
		if (initialize_mlx(&frct))
			return (1);
		if (frct.set == 1)
			draw_mandelbrot(&frct);
		else if (frct.set == 2)
			draw_julia(&frct);
		mlx_put_image_to_window(frct.mlx_ptr, frct.win, frct.img, 0, 0);
		mlx_loop(frct.mlx_ptr);
		return (0);
	}
	return (1);
}
