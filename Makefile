NAME = linear_regression

DATAFILE = data.csv
TRAINEDFILE = trained.sps

CFLAG = -Wall -Wextra -Werror -fsanitize=address -g

all: learn vizualize

learn:
	gcc $(CFLAG) learn/main.c
	./a.out $(DATAFILE) $(TRAINEDFILE)
	rm -rf a.out*

predict:
	python3 predict/main.py $(TRAINEDFILE)

vizualize:
	python3 vizualize/main.py $(DATAFILE) < $(TRAINEDFILE)

.PHONY: learn predict vizualize