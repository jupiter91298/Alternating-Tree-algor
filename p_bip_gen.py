import networkx as nx
from networkx.algorithms import bipartite
import matplotlib.pyplot as plt
RB = bipartite.random_graph(10, 10, 0.5)
RB_top = {n for n, d in RB.nodes(data=True) if d["bipartite"] == 0}
RB_bottom = set(RB) - RB_top
fwr = open("t_directed.txt","w+")
fwr.write(str(len(RB.nodes()))+"\n")
fwr.write(str(len(RB.edges()))+"\n")

for edge in RB.edges():
    fwr.write(str(edge[0]+1)+" "+str(edge[1]+1)+"\n")
fwr.write(str(len(RB_top)) + "\n")
for v in RB_top:
    fwr.write(str(v+1) + "\n")
fwr.close()
nx.draw(RB,with_labels=True)
plt.savefig('123.png')
plt.show()