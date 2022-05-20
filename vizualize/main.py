import sys
import matplotlib.pyplot as plt

print("### \033[1;91mLaunching visualization\033[0m ###")

a, b = map(float, input().split())

lines = open(sys.argv[1], "r").read().splitlines()
labelX, labelY = lines[0].split(',')
csv = list(map(lambda s: list(map(float, s.split(','))), lines[1:]))

x = list(map(lambda n: n[0], csv))
y = list(map(lambda n: n[1], csv))

minX = min(x)
maxX = max(x)

plt.plot(
	[
		minX,
		maxX
	],
	[
		minX * a + b,
		maxX * a + b
	]
, color="red")

plt.scatter(x, y, color= "blue")

plt.xlabel(labelX)
plt.ylabel(labelY)
plt.title('ft_linear_regression')
plt.show()