#pragma once

#include "utils.h"

typedef struct {
	double	**data;
	int		width;
	int		height;
}	t_csv;

char	**read_file(int fd) {
	char	**lines = malloc(sizeof(char *));
	int 	lines_count = 0;
	char	buf;

	while (1) {
		char	*line = NULL;
		int 	line_len = 0;

		while (read(fd, &buf, 1) && buf != '\n')
		{
			line = realloc(line, (++line_len + 1) * sizeof(char));
			line[line_len - 1] = buf;
		}

		if (line == NULL)
			break ;
		line[line_len] = '\0';
		lines[lines_count] = line;
		lines = realloc(lines, (++lines_count + 1) * sizeof(char *));
	}
	lines[lines_count] = NULL;
	return (lines);
}

void	free_string_array(char **lines) {
	int	i = 0;
	while (lines[i] != NULL)
	{
		free(lines[i]);
		++i;
	}
	free(lines);
}

double	atod(char **s) {
	double	value = 0;
	while (**s >= '0' && **s <= '9')
	{
		value = value * 10 + **s - '0';
		++*s;
	}
	return (value);
}

double	*parse_csv_line(char *s, int *width) {
	if (*s == '\0')
		die("empty line");

	double	*data = malloc(sizeof(double));

	*width = 1;
	data[0] = atod(&s);
	while (*s)
	{
		if (*s != ',')
			die("unexpected char");
		++s;
		data = realloc(data, ++*width * sizeof(double));
		data[*width - 1] = atod(&s);
	}
	return (data);
}

t_csv	*parse_csv(char **lines) {
	t_csv	*csv = malloc(sizeof(t_csv));

	if (!*lines || !*++lines)
		die("no data");
	
	csv->width = 0;
	csv->height = 1;
	csv->data = malloc(sizeof(double *));

	csv->data[0] = parse_csv_line(*lines, &csv->width);

	while (*++lines != NULL)
	{
		int	width;
		++csv->height;
		csv->data = realloc(csv->data, csv->height * sizeof(double *));
		csv->data[csv->height - 1] = parse_csv_line(*lines, &width);
		if (width != csv->width)
			die("line width not equal");
	}

	return (csv);
}

t_csv	*read_csv(char *filename) {
	int fd = open(filename, O_RDONLY);

	if (fd == -1)
		die("cannot open file");

	char	**lines = read_file(fd);
	t_csv	*csv = parse_csv(lines);
	free_string_array(lines);

	close(fd);
	return (csv);
}

void	free_csv(t_csv *csv) {
	for (int y = 0; y < csv->height; ++y)
		free(csv->data[y]);
	free(csv->data);
	free(csv);
}

void	print_csv(t_csv *csv) {
	puts("\033[94m======  CSV  DATA  ======");
	for (int y = 0; y < csv->height; ++y)
	{
		printf("| ");
		for (int x = 0; x < csv->width; ++x)
			printf("\033[93m%10.3f\033[94m ", csv->data[y][x]);
		puts("|");
	}
	puts("=========================\033[0m");
}