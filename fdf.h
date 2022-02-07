#ifndef FDF_H
# define FDF_H

# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h> 
# include <math.h>

typedef struct fdf
{
	int		delta;
	int		place_x;
	int		place_y;
	int		hight;
	int		width;
	int		**matrix;
	int		zooming;
	int		color;
	float	corn;
	void	*mlx_ptr;
	void	*win_ptr;
}	t_fdf;

typedef struct dods
{
	float	x;
	float	x1;
	float	y;
	float	y1;
	float	z;
	float	z1;
	float	movingx;
	float	movingy;
	float	movingz;
}	t_dods;

int		key(int key_button, t_fdf *field);
void	math(float *x, float *y, int z, t_fdf *field);
void	dotdods(t_dods *point, t_fdf *field);
void	draw(t_fdf field);
void	drawlin(t_dods point, t_fdf *field);
int		chars(int fd, int i, char *argc);
char	*buffer(int fd, int i, char *argc, char *buf);
t_fdf	map(char *buf, int i, int fd, t_fdf *field);
int		**full_map(char *buf, int fd, t_fdf field);
t_fdf	main_reader(char *argc);
int		ft_atoi(const char *s);
int		difference(t_fdf field);
char	*ft_itoa(int n);
void	del_pointer(t_fdf *field, int i);
void	counter(int *i, int *count, int *fd);
float	ft_abs(float x);

#endif