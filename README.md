Andrew Daiuto
CS3353
PA03
	The goal of the Girvan-Newman algorithm is to isolate communities within a graph. This is done by removing edges within the graph which indicate that they connect two or more communities. Using boost library, the graph data is read in from a .graphml file and processed. The first processing task is to determine which cross-community edges require removing. This is done by calculating the betweenness centrality of each edge. Betweenness centrality of an edge e is determined by traversing the shortest path between every combination of two nodes. 
	Boost library supplies a breath-first-search algorithm which will return a path of nodes. This BFS algorithm requires a Visitor object responsible for returning the path of nodes as it traverses across the graph. I utilized a custom implementation of the BfsVisitor class (derived from https://stackoverflow.com/a/43780529) which would return the edges traversed instead of the nodes traversed. Each edge would then be inserted (as an edge_descriptor) into a map containing key-value pairs relating the edge_descriptor objects with their respective centralities. The descriptor-centrality pair with the highest second value is removed and the calculations start again.
    
	This process requires several iterations, but few enough as to not eliminate every edge in the graph. To settle on a satisfactory separation, I determined the number of iterations based on the number of edges in the graph. Below are the runtimes and community outputs for a dataset comprising 4 communities provided by a classmate.
    
![Screenshot_4](https://user-images.githubusercontent.com/78216021/163100961-3e66fdd0-ece5-46e2-b4ae-3c7755bc0cb4.jpg)

	To test this strategy on real-life datasets, it was run on the Football Conference 2000 dataset. The isolation of the conferences is more pronounced for some than others. 
    
![Screenshot_5](https://user-images.githubusercontent.com/78216021/163101721-6e2558ea-cdf8-4802-8e08-1c954937f7ea.jpg)

	I also tested the algorithm on a completely random dataset with arbitrary connections between 300 nodes. It was not able to isolate any communities, and the output looked nearly identical to the input.

