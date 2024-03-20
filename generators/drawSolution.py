import matplotlib.pyplot as plt
import matplotlib
import os
import sys



import networkx as nx
options = {
    "linewidths": 1,
    "edgecolors": "black",
    "node_color": "grey",
    "node_size": 0.25,

}

options_e ={
    "width": 2,
}
options_l = {
    "font_size": 7,

} 

def hello_world():
        G = nx.DiGraph() #or G = nx.MultiDiGraph()
        G.add_node('A')
        G.add_node('B')
        G.add_edge('A', 'B',  rad=0.1, arrowstyle="<-")
        G.add_edge('B', 'A', rad=0.6, arrowstyle="-")

 

        #pos = nx.spring_layout(G)
        #nx.draw(G, pos, with_labels=True, connectionstyle='arc3, rad = 0.1')

        pos = {'A': (0, 0), 'B': (40, 0)}

        nx.draw_networkx_nodes(G, pos,**options)
        nx.draw_networkx_labels(G, pos)
        for edge in G.edges(data=True):
            nx.draw_networkx_edges(G, pos, arrowstyle=edge[2]["arrowstyle"],arrowsize = 30, edgelist=[(edge[0],edge[1])],  connectionstyle=f'arc3, rad = {edge[2]["rad"]}')

        plt.margins(x=0.1, y = 5)
        
        plt.show()
    
def draw_solution(file_name):
    # Using readlines()
    G = nx.DiGraph()
    node = 0
    with open(file_name, 'r') as fp:
        Lines = fp.readlines()
        position_line = False
        solution_line = False
        Position = {}
        count_x = 0
        count = 0
        for line in Lines:
            ## get position information
            if not position_line and not solution_line:
                result = line.startswith('p ')
                if(result):
                    position_line = True
                continue
            if position_line and not solution_line:
                result = line.startswith('d ')
                if(result):
                    solution_line = True
                    continue
                p = line.strip().split(" ")
                Position[str(count_x)] = (float(p[0]) * 1000, 0)
                count_x+= 1
                continue
            if line.startswith('i'):
                #Position[str(count)] = (count*500000,0)
                count = count + 1
                nodes = line.strip().split(': ')
                if len(nodes) == 1:
                    continue
                nodes = nodes[1]
                nodes = nodes.split(' ')
                for in_node in nodes:
                    G.add_edge(str(in_node), str(node), rad=0.6, arrowstyle="-")
                continue
            if line.startswith('o'):
                continue
            node = line.split(':')[0]
            G.add_node(str(node))
                # read edge   
    for i in range(0,count-1):
        #G.add_edge(str(i), str(i+1), rad=0, arrowstyle="-")
        pass
    print(Position)
    nx.draw_networkx_nodes(G, Position,**options)
    #nx.draw_networkx_labels(G, Position)
    for edge in G.edges(data=True):
        nx.draw_networkx_edges(G, Position, arrowstyle=edge[2]["arrowstyle"],arrowsize = 3, edgelist=[(edge[0],edge[1])],  connectionstyle=f'arc3, rad = {edge[2]["rad"]}')
        pass
    #plt.margins(x=0.1, y = 5)
    sep = '.'
    stripped = file_name.split(sep, 1)[0]
    plot_name = stripped + ".png"
    plt.gcf().set_size_inches(15, 7)
    plt.savefig(plot_name )  
    
    plt.show()








if __name__ == "__main__":
    if os.name == 'nt':
        #hello_world();
        cmdargs = str(sys.argv)
        draw_solution(sys.argv[1])