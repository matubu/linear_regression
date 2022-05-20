import sys

print("### \033[1;91mMSE\033[0m ###")

a, b = map(float, input().split())

lines = open(sys.argv[1], "r").read().splitlines()
csv = list(map(lambda s: list(map(float, s.split(','))), lines[1:]))

mse = 0
for x, y in csv:
	mse += ((a * x + b) - y) ** 2

print('\033[94m', mse / len(csv), '\033[0m', sep="")