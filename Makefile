NAME = linear_regression

DATAFILE = test.csv
TRAINEDFILE = trained.ssv

CFLAG = -Wall -Wextra -Werror -Ofast

vizualize: learn
	@python3 vizualize/main.py $(DATAFILE) < $(TRAINEDFILE)

learn:
	@gcc $(CFLAG) learn/main.c
	time ./a.out $(DATAFILE) $(TRAINEDFILE)
	@rm -rf a.out*
	@make mse

predict: learn
	python3 predict/main.py $(TRAINEDFILE)

mse:
	@python3 mse/main.py $(DATAFILE) < $(TRAINEDFILE)

.PHONY: vizualize learn predict mse