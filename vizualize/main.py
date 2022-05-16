import sys
import matplotlib.pyplot as plt

a, b = map(float, input().split())

lines = open(sys.argv[1], "r").read().splitlines()
labelX, labelY = lines[0].split(',')
csv = list(map(lambda s: list(map(float, s.split(','))), lines[1:]))

x = list(map(lambda n: n[0], csv))
y = list(map(lambda n: n[1], csv))

minX = min(x)
maxX = max(x)

print(a, b)
print(lines)
print(csv)
print(minX, maxX)

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