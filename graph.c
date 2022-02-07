#include "fdf.h"

void	math(float *x, float *y, int z, t_fdf *field)
{
	*x = (*x - *y) * cos(field->corn);
	*y = (*x + *y) * sin(field->corn) - z;
}

void	dotdods(t_dods *point, t_fdf *field)
{
	point->z = field->matrix[(int)point->y][(int)point->x];
	point->z1 = field->matrix[(int)point->y1][(int)point->x1];
	point->x = (point->x) * field->zooming;
	point->x1 = (point->x1) * field->zooming;
	point->y = (point->y) * field->zooming;
	point->y1 = (point->y1) * field->zooming;
	math(&point->x, &point->y, point->z, field);
	math(&point->x1, &point->y1, point->z1, field);
	point->x = (point->x + field->place_x);
	point->x1 = (point->x1 + field->place_x);
	point->y = (point->y + field->place_y);
	point->y1 = (point->y1 + field->place_y);
	point->movingx = point->x1 - point->x;
	point->movingy = point->y1 - point->y;
	point->movingz = (point->z1 - point->z);
}

void	draw(t_fdf field)
{
	t_dods	point;

	point.y = 0;
	while (point.y < field.hight)
	{
		point.x = 0;
		while (point.x < field.width)
		{
			if (point.x < field.width - 1)
			{
				point.y1 = point.y;
				point.x1 = point.x + 1;
				drawlin(point, &field);
			}
			if (point.y < field.hight - 1)
			{
				point.y1 = point.y + 1;
				point.x1 = point.x;
				drawlin(point, &field);
			}
			point.x++;
		}
		point.y++;
	}
}

static void	make_step(t_dods *point)
{
	if (ft_abs(point->movingx) > ft_abs(point->movingy))
	{
		point->movingy = point->movingy / ft_abs(point->movingx);
		point->movingz = point->movingz / ft_abs(point->movingx);
		point->movingx = point->movingx / ft_abs(point->movingx);
	}
	else
	{
		point->movingx = point->movingx / ft_abs(point->movingy);
		point->movingz = point->movingz / ft_abs(point->movingy);
		point->movingy = point->movingy / ft_abs(point->movingy);
	}
}

void	drawlin(t_dods point, t_fdf *field)
{
	dotdods(&point, field);
	make_step(&point);
	while ((int)(point.x - point.x1) || (int)(point.y - point.y1))
	{
		if (point.z < point.z1 || point.z >= 0)
		{
			field->color = 0x00ffffff - (field->delta * point.z)
				/ difference(*field);
			point.z += point.movingz;
		}
		else if (point.z >= point.z1 && point.z < 0)
		{
			field->color = 0x00ffffff - (field->delta * point.z1)
				/ difference(*field);
			point.z1 += point.movingz;
		}		
		mlx_pixel_put(field->mlx_ptr, field->win_ptr,
			point.x, point.y, field->color);
		point.x = point.x + point.movingx;
		point.y = point.y + point.movingy;
	}
}
