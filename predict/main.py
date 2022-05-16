import sys

lines = open(sys.argv[1], "r").read().splitlines()

a, b = map(float, lines[0].split())

while (1):
	x = float(input("x: "))
	print("Predicted: ", a * x + b)