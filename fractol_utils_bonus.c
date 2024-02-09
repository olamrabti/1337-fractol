/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:36:50 by olamrabt          #+#    #+#             */
/*   Updated: 2024/02/09 16:33:08 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

int	initialize_mlx(t_mlx *frct)
{
	frct->mlx_ptr = mlx_init();
	if (!frct->mlx_ptr)
		return (ft_err_msg(3), 1);
	frct->win = mlx_new_window(frct->mlx_ptr, WIDTH, HEIGHT, frct->title);
	if (!frct->win)
		return (free(frct->mlx_ptr), ft_err_msg(3), exit(0), 1);
	frct->img = mlx_new_image(frct->mlx_ptr, WIDTH, HEIGHT);
	if (!frct->img)
	{
		ft_err_msg(3);
		return (mlx_destroy_window(frct->mlx_ptr, frct->win), 1);
	}
	frct->pxl = mlx_get_data_addr(frct->img, &frct->bpp, &frct->len, &frct->e);
	if (!frct->pxl)
		return (ft_err_msg(3), handle_window_close(frct), 1);
	mlx_mouse_hook(frct->win, &mouse_event_handler, frct);
	mlx_key_hook(frct->win, &key_event_handler, frct);
	mlx_hook(frct->win, 17, 0, &handle_window_close, frct);
	return (0);
}

int	mouse_event_handler(int move, int x, int y, t_mlx *frct)
{
	(void)x;
	(void)y;
	if (move == 4)
	{
		frct->zoom *= 1.1;
		if (frct->iter > 50)
			frct->iter -= 1;
	}
	else if (move == 5)
	{
		frct->zoom *= 0.9;
		frct->iter += 1;
	}
	else
		return (0);
	if (frct->set == 1 || frct->set == 3)
		mandelbrot_or_bs(frct);
	else if (frct->set == 2)
		draw_julia_bonus(frct);
	mlx_put_image_to_window(frct->mlx_ptr, frct->win, frct->img, 0, 0);
	return (0);
}

int	key_event_handler(int move, t_mlx *frct)
{
	if (move == 126)
		frct->sh_v += frct->zoom;
	if (move == 125)
		frct->sh_v -= frct->zoom;
	if (move == 124)
		frct->sh_h += frct->zoom;
	if (move == 123)
		frct->sh_h -= frct->zoom;
	if (move == 24)
		frct->iter += 2;
	if (move == 27)
		frct->iter -= 2;
	if (move == 53)
		exit(0);
	if (frct->set == 1 || frct->set == 3)
		mandelbrot_or_bs(frct);
	else if (frct->set == 2)
		draw_julia_bonus(frct);
	mlx_put_image_to_window(frct->mlx_ptr, frct->win, frct->img, 0, 0);
	return (0);
}

int	handle_window_close(t_mlx *frct)
{
	mlx_clear_window(frct->mlx_ptr, frct->win);
	mlx_destroy_window(frct->mlx_ptr, frct->win);
	free(frct->mlx_ptr);
	exit(0);
	return (0);
}

double	ft_interpolate(double coord, double new_min, double new_max)
{
	return ((new_max - new_min) * coord / HEIGHT + new_min);
}
