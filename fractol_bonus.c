/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:03:23 by olamrabt          #+#    #+#             */
/*   Updated: 2024/02/09 16:59:04 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

void	my_mlx_pixel_put(t_mlx *frct, int x, int y, int color)
{
	char	*dst;

	dst = frct->pxl + (y * frct->len + x * (frct->bpp / 8));
	*(unsigned int *)dst = color;
}

void	mandelbrot_or_bs(t_mlx *frct)
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
			var.cr = ft_interpolate(var.x, -2, 1) * frct->zoom + frct->sh_h;
			var.ci = ft_interpolate(var.y, -1.5, 1.5) * frct->zoom + frct->sh_v;
			if (frct->set == 1)
				ft_do_the_math(frct, &var);
			else
				ft_do_bs_math(frct, &var);
			var.y++;
		}
		(var.x)++;
	}
}

void	draw_julia_bonus(t_mlx *frct)
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
			var.ar = ft_interpolate(var.x, 2, -2) * frct->zoom + frct->sh_h;
			var.ai = ft_interpolate(var.y, -2, 2) * frct->zoom + frct->sh_v;
			ft_do_the_math(frct, &var);
			var.y++;
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
		frct.sh_h = 0;
		frct.sh_v = 0;
		if (initialize_mlx(&frct))
			return (1);
		if (frct.set == 1 || frct.set == 3)
			mandelbrot_or_bs(&frct);
		else
			draw_julia_bonus(&frct);
		mlx_put_image_to_window(frct.mlx_ptr, frct.win, frct.img, 0, 0);
		mlx_loop(frct.mlx_ptr);
		return (0);
	}
	return (1);
}
