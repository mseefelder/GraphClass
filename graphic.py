import pylab
def get_values(file_name, x = [], y = []):
	file_graph = open(str(file_name), "r")
	values = file_graph.readlines()
	for i in xrange(len(values)):
		space_index = values[i].find(" ")
		x.append(int(values[i][:space_index]))
		y.append(float(values[i][space_index + 1:-1]))

x = []
y = []
pylab.figure(1)
get_values("graph_infoas.txt", x, y)
pylab.plot(x,y)
pylab.show()


