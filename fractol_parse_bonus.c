/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_parse_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:36:36 by olamrabt          #+#    #+#             */
/*   Updated: 2024/02/09 15:00:13 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

static double	ft_atoi(const char *str, int *i, int *sign)
{
	unsigned long long	num;

	num = 0;
	if (!str)
		return (-3);
	while (str[*i] && (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13)))
		(*i)++;
	if (str[*i] && (str[*i] == '-' || str[*i] == '+'))
	{
		if (str[(*i)++] == '-')
			*sign = -1;
	}
	while (str[*i] && (str[*i] >= '0' && str[*i] <= '9'))
		num = num * 10 + str[(*i)++] - 48;
	return (num);
}

double	ft_atof(char *str)
{
	t_atof	atof;
	int		i;

	i = 0;
	atof.x = 1;
	atof.sign = 1;
	atof.dnum = ft_atoi(str, &i, &atof.sign);
	if (atof.dnum > 2)
		return (-4);
	if (!str[i])
		return (atof.sign * atof.dnum);
	if (str[i++] != '.' || !(str[i] >= '0' && str[i] <= '9'))
		return (-5);
	atof.j = i;
	atof.fnum = ft_atoi(str, &i, &atof.x);
	if (atof.fnum < 0)
		return (-6);
	atof.x = 1;
	while (atof.j++ < i)
		atof.x *= 10;
	if (str[i] || (atof.dnum + atof.fnum / atof.x) > 2 || atof.x > 100000)
		return (-7);
	return (atof.sign * (atof.dnum + atof.fnum / atof.x));
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	if (!s1 || !s2)
		return (-1);
	while (n > 0 && (*s1 || *s2))
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}

int	check_params(int ac, char *av[], t_mlx *frct)
{
	if (ac == 2 && !ft_strncmp(av[1], "m", 1))
	{
		frct->set = 1;
		frct->title = "Mandelbrot";
		return (0);
	}
	else if (ac == 2 && !ft_strncmp(av[1], "b", 1))
	{
		frct->set = 3;
		frct->title = "Burning Ship";
		return (0);
	}
	else if (ac == 4 && !ft_strncmp(av[1], "j", 1))
	{
		frct->set = 2;
		frct->title = "Julia";
		if (ft_atof(av[2]) < -2 || ft_atof(av[3]) < -2)
			return (ft_err_msg(2), 2);
		frct->julia_cr = ft_atof(av[2]);
		frct->julia_ci = ft_atof(av[3]);
		return (0);
	}
	return (ft_err_msg(1), 1);
}

void	ft_err_msg(int err)
{
	if (err == 2)
	{
		write(1, "For Julia : <./fractol j num1 num2 > \n\n", 39);
		write(1, "Also! num1 & num2 must be between -2 & 2\n", 41);
		write(1, "only 4 digits after ex: 0.1234\n", 31);
	}
	else if (err == 1)
	{
		write(1, "Error : Invalid parameters!\n\n try :\n", 36);
		write(1, "For Mandelbrot : <./fractol m > \n", 33);
		write(1, "For Burning Ship : <./fractol b > \n", 35);
		write(1, "For Julia : <./fractol j num1 num2 > \n", 38);
	}
	else if (err == 3)
		write(1, "Error : Initialization failed\n", 38);
}
