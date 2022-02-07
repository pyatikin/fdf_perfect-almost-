#include "fdf.h"

float	ft_abs(float x)
{
	if (x >= 0)
		return (x);
	else
		return (-1.0 * x);
}

static void	buttom_hook(int key_button, t_fdf *field)
{
	if (key_button == 65362)
		field->place_y -= 50;
	if (key_button == 65364)
		field->place_y += 50;
	if (key_button == 65363)
		field->place_x += 50;
	if (key_button == 65361)
		field->place_x -= 50;
	if (key_button == 65434)
		field->zooming += 10;
	if (key_button == 65435)
		field->zooming -= 10;
	if (key_button == 65505)
		field->corn += 0.05;
	if (key_button == 65506)
		field->corn -= 0.05;
}

int	key(int key_button, t_fdf *field)
{
	int	j;

	j = 0;
	/*write(1, ft_itoa(key_button), sizeof(ft_itoa(key_button))); write(1, "\n", 1); Для полученя кода кнопок!!!!!!!!!!!*/
	buttom_hook(key_button, field);
	if (key_button == 65307)
	{
		mlx_destroy_window(field->mlx_ptr, field->win_ptr);
		while (j < field->hight)
		{
			free(field->matrix[j]);
			j++;
		}
		free(field->matrix);
		exit(0);
	}
	mlx_clear_window(field->mlx_ptr, field->win_ptr);
	draw(*field);
	return (0);
}

int	main(int argv, char **argc)
{
	t_fdf	field;

	field = main_reader(argc[1]);
	field.zooming = 50;
	field.place_x = 0;
	field.place_y = 0;
	field.corn = 0.8;
	field.delta = 65535;
	field.mlx_ptr = mlx_init();
	field.win_ptr = mlx_new_window(field.mlx_ptr, 1000, 1000, "FDF");
	draw(field);
	mlx_key_hook(field.win_ptr, key, &field);
	mlx_loop(field.mlx_ptr);
}
