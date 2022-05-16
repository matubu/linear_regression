#pragma once

void die(char *e) {
	fprintf(stderr, "\033[91mError\033[0m: %s\n", e);
	exit(1);
}