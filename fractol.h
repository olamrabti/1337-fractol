/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:03:28 by olamrabt          #+#    #+#             */
/*   Updated: 2024/02/11 11:06:21 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# include <stdio.h>

# define WIDTH 800
# define HEIGHT 800
# define MAX_ITER 50

# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00
# define CYAN 0x00FFFF
# define GRAY 0x808080
# define LIGHT_GRAY 0xC0C0C0
# define ORANGE 0xFFA500
# define PURPLE 0x800080
# define ELECTRIC_BLUE 0x00BFFF
# define LIME_GREEN 0x32CD32
# define MAGENTA 0xFF00FF
# define CLR1 0xDAA520
# define CHARTREUSE 0x7FFF00

typedef struct s_mlx_variables
{
	void	*mlx_ptr;
	void	*win;
	void	*img;
	void	*pxl;
	char	*title;
	int		bpp;
	int		len;
	int		e;
	int		iter;
	int		set;
	double	zoom;
	double	julia_cr;
	double	julia_ci;
}	t_mlx;

typedef struct s_func_variables
{
	double	x;
	double	y;
	double	ar;
	double	ai;
	double	cr;
	double	ci;
}	t_func_var;

typedef struct s_atof_variables
{
	double	fnum;
	double	dnum;
	int		sign;
	int		j;
	int		x;
}	t_atof;

int		ft_strncmp(char *s1, char *s2, size_t n);
int		initialize_mlx(t_mlx *frct);
int		mouse_event_handler(int move, int x, int y, t_mlx *frct);
int		key_event_handler(int move, t_mlx *frct);
int		handle_window_close(t_mlx *frct);
int		check_params(int ac, char *av[], t_mlx *frct);
double	ft_interpolate(double coord, double new_min, double new_max);
double	ft_atof(char *str);
void	ft_err_msg(int err);
void	draw_julia(t_mlx *frct);
void	draw_mandelbrot(t_mlx *frct);

#endif