#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

#include "utils.h"
#include "csv.h"

#define LEARNING_RATE  .001
#define EPOCH          1000000

typedef struct {
	double	min[2];
	double	max[2];
	t_csv	*csv;
	double	a;
	double	b;
}	t_data;

void	normalize(t_data *d) {
	double	**csv = d->csv->data;

	d->min[0] = csv[0][0];
	d->min[1] = csv[0][1];
	d->max[0] = csv[0][0];
	d->max[1] = csv[0][1];
	for (int i = 1; i < d->csv->height; ++i)
	{
		d->min[0] = fmin(d->min[0], csv[i][0]);
		d->min[1] = fmin(d->min[1], csv[i][1]);
		d->max[0] = fmax(d->max[0], csv[i][0]);
		d->max[1] = fmax(d->max[1], csv[i][1]);
	}

	for (int y = 0; y < d->csv->height; ++y)
		for (int x = 0; x < d->csv->width; ++x)
			csv[y][x] =
				(csv[y][x] - d->min[x])
				/ (d->max[x] - d->min[x]);
}

#define estimatedPrice(x) (d->a * (x) + d->b)

void	train(t_data *d) {
	double	**csv = d->csv->data;

	d->a = 0;
	d->b = 0;
	for (int i = 0; i < EPOCH; ++i)
	{
		double tmpa = 0;
		double tmpb = 0;
		for (int y = 0; y < d->csv->height; ++y)
		{
			double diff = estimatedPrice(csv[y][0]) - csv[y][1];
			tmpa += csv[y][0] * diff;
			tmpb += diff;
		}
		d->a -= tmpa * LEARNING_RATE / (double)d->csv->height;
		d->b -= tmpb * LEARNING_RATE / (double)d->csv->height;
	}
}

int main(int argc, char **argv) {
	if (argc != 3)
		die("usage: ./linear_regression [data-file] [trained-file]");

	t_csv	*csv = read_csv(argv[1]);

	print_csv(csv);

	if (csv->width != 2)
		die("must have 2 colums in csv");
	if (csv->height < 2)
		die("must have at least 2 rows in csv");

	t_data	data = { .csv = csv };

	normalize(&data);

	puts("Min:");
	printf("[ %10.3f,%10.3f ]\n", data.min[0], data.min[1]);
	puts("Max:");
	printf("[ %10.3f,%10.3f ]\n", data.max[0], data.max[1]);

	puts("Normalized:");
	print_csv(csv);

	train(&data);

	printf("NORM [ %f, %f ]\n", data.a, data.b);

	double	a = data.a
			/ (data.max[0] - data.min[0])
			* (data.max[1] - data.min[1]);
	double	b = 
		(
			(data.a * 1 + data.b) // 0-1 prediction
			* (data.max[1] - data.min[1]) // convert to real value
			+ data.min[1]
		)
		- (a * data.max[0]) // substract multiplicator
	;

	printf("REAL [ %f, %f ]\n", a, b);

	FILE	*file = fopen(argv[2], "w");
	fprintf(file, "%f %f", a, b);
	fclose(file);

	free_csv(csv);
}