/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:03:28 by olamrabt          #+#    #+#             */
/*   Updated: 2024/02/07 18:53:19 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <stdlib.h> 
# include <unistd.h> 
# include <math.h>
# include "../../../../Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/Tk.framework/Versions/8.5/Headers/X11/X.h"

# include <stdio.h> 


# define WIDTH 800
# define HEIGHT 800
# define MAX_ITER 50


# define BLACK         0x000000
# define WHITE         0xFFFFFF
# define RED           0xFF0000
# define BLUE          0x0000FF
# define YELLOW        0xFFFF00
# define CYAN          0x00FFFF
# define GRAY          0x808080
# define LIGHT_GRAY    0xC0C0C0
# define ORANGE        0xFFA500
# define PURPLE        0x800080
# define ELECTRIC_BLUE   0x00BFFF
# define LIME_GREEN      0x32CD32
# define MAGENTA         0xFF00FF
# define GOLDENROD       0xDAA520
# define CHARTREUSE      0x7FFF00


typedef struct s_mlx_variables
{
    void *mlx_ptr;
    void *win_ptr;
    void *image;
    void *img_pxl_ptr;
    char *title;
    int bits_per_pixel;
    int size_line;
    int endian;
    int mouse;
    int button;
    int keyboard;
    int max_iter;
    double zoom;
    double shift_h;
    double shift_v;
    int set;
    double julia_cr;
    double julia_ci;
} t_mlx;

typedef struct s_func_variables
{
    double x;
    double y;
    double ar;
    double ai;
    double cr;
    double ci;
} t_func_var;

typedef struct s_atof_variables
{
    double fnum;
    double dnum;
    int sign;
    int j;
    int x;
} t_atof;

int ft_strncmp(char *s1, char *s2, size_t n);
int initialize_mlx(t_mlx *fract_setup);
// void   ft_clean_mlx(t_mlx *fract_setup);
void draw_julia(t_mlx *fract_setup);
void mandelbrot_or_bs(t_mlx *fract_setup);
void mandelbrot_or_bs(t_mlx *fract_setup);
double ft_interpolate(double coord, double new_min, double new_max, double old_min, double old_max);
int mouse_event_handler(int move, int x, int y, t_mlx *fract_setup);
int key_event_handler(int move, t_mlx *fract_setup);
int handle_window_close(void);
void ft_do_the_math(t_mlx *fract_setup , t_func_var *var);
void ft_do_bs_math(t_mlx *fract_setup, t_func_var *var);
double ft_atof(char *str);
int check_params(int ac ,char *av[], t_mlx *fract_setup);
void ft_throw_error(int err);

#endif