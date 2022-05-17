NAME = linear_regression

DATAFILE = data.csv
TRAINEDFILE = trained.ssv

CFLAG = -Wall -Wextra -Werror -Ofast

all: learn vizualize

learn:
	gcc $(CFLAG) learn/main.c
	time ./a.out $(DATAFILE) $(TRAINEDFILE)
	rm -rf a.out*

predict:
	python3 predict/main.py $(TRAINEDFILE)

vizualize:
	python3 vizualize/main.py $(DATAFILE) < $(TRAINEDFILE)

.PHONY: learn predict vizualize