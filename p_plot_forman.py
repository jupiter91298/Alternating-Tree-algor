import networkx as nx
import matplotlib.pyplot as plt
G=nx.DiGraph()
M=lambda:map(int,line.split())
MM=lambda:map(int,line)
file1 = open("t_input.txt")
lines =file1.readlines()
file1.close()
n=0
m=0
cnt=0
for line in lines:
    if cnt==0:
        n=int(line)
        print(n)
        for j in range(1,n+1):
            G.add_node(j)
        print(G.nodes())
    elif cnt==1:
        m=int(line)
    else:
        x,y=M()
        G.add_edge(x,y)
    cnt=cnt+1
file1 = open("t_forman_value.txt")
lines =file1.readlines()
file1.close()
val = [0]*(len(G.nodes())+1)
pos = nx.spring_layout(G,seed=100)
i =1
for line in lines:
    temp = float(line)
    val[i] = temp
    i = i +1 
value = [0]*(len(G.nodes()))
i=0
node_size = [val[v]*500 for v in G] 
for node in G.nodes():
    value[i] = val[node]
    i = i +1 
nx.draw(G,cmap = plt.get_cmap('viridis'),edge_color='0.1',node_color=value,with_labels=True,pos=pos)
plt.savefig('forman_values.png')
plt.show() 
