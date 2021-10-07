#include "fractol.h"

double	ft_abs(double n)
{
	if (n  < 0)
		return (-n);
	return (n);
}

double	pow(double x, double n)
{
	int		c;
	double	r;

	r = 1;
	c = 0;
	while (c < n)
	{
		r = r * x;
		c++;
	}
	return (r);
}

double	complex_abs(t_complex *z)
{
	return (pow(z->re, 2) + pow(z->im, 2));
}
