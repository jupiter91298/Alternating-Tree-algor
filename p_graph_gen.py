import networkx as nx
from networkx.algorithms import bipartite
import matplotlib.pyplot as plt
K=nx.erdos_renyi_graph(500,0.09) 
#fwr = open("t_input.txt","w+")
fwr = open("t_directed.txt","w+")
fwr.write(str(len(K.nodes()))+"\n")
fwr.write(str(len(K.edges()))+"\n")

for edge in K.edges():
    fwr.write(str(edge[0]+1)+" "+str(edge[1]+1)+"\n")
fwr.close()
#nx.draw(K)
#plt.show()