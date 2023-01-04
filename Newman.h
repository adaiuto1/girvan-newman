//
// Created by ABD on 4/8/2022.
//

#include "BfsVisitor.h"
#include <map>
#include <string>
#ifndef INC_22S_PA03_GIRVAN_NEWMAN_CHURCHOFCHOVY_NEWMAN_H
#define INC_22S_PA03_GIRVAN_NEWMAN_CHURCHOFCHOVY_NEWMAN_H
struct vertexData{std::string name;};
struct edgeData{int weight = 0;};
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
vertexData, boost::property<boost::edge_weight_t, double>>myGraph;
typedef boost::graph_traits<myGraph> GraphTraits;
typedef GraphTraits::vertex_descriptor Vertex;
typedef GraphTraits::edge_descriptor Edge;
typedef std::map<Vertex, std::size_t>IndexMap;

using namespace std;
class Newman{
public:
    Newman(const int&, const string);
    void readData();
    void writeData();
    void runAlgo();
    void print();
    myGraph& getGraph();
private:
    myGraph g;
    int num;
    GraphTraits::vertex_iterator vi, vi_end;
    GraphTraits::out_edge_iterator out_i, out_end;
    string inputFile;
    IndexMap mapIndex;
    std::map<Edge, int> centralityMap;
    string outputFile;
};
Newman::Newman(const int& n, const string filename){
    num = n;
    inputFile = "data/" + filename + ".graphml";
    outputFile = "output/" + filename + ".graphml";
}
void Newman::readData(){
    ifstream inFile(inputFile);
    boost::dynamic_properties dp(boost::ignore_other_properties);
    dp.property("label", boost::get(&vertexData::name, g));
    boost::read_graphml(inFile, g, dp);
    inFile.close();
}
void Newman::print(){
    boost::print_graph(g);
//    for(boost::tie(vi, vi_end) = boost::vertices(g); vi != vi_end; vi++){
//        Vertex curr = *vi;
//    }
}
myGraph& Newman::getGraph(){
    return g;
}
void Newman::writeData(){
    ofstream oFile(outputFile);
    boost::dynamic_properties dp(boost::ignore_other_properties);
    dp.property("label", boost::get(&vertexData::name, g));
    boost::write_graphml(oFile, g, dp);
    oFile.close();
}
void Newman::runAlgo(){
    //vertex index map required for BFS
    boost::associative_property_map<IndexMap> propmapIndex(mapIndex);
    std::size_t i = 0;
    for (boost::tie(vi, vi_end) = boost::vertices(g); vi != vi_end; ++vi)
    {
        boost::put(propmapIndex, *vi, i++);
    }
    //boost::print_graph(g);
    int iterations = boost::num_edges(g)/num;
    for(int i = 0; i < iterations; i++){
        //store centrality of each edge in centralityMap vector
        //these values change every time an edge is removed
        centralityMap = std::map<Edge, int>();
        for (boost::tie(vi, vi_end) = boost::vertices(g); vi != vi_end; ++vi)
        {
            //perform a breadth-first search through the descendants of the current node
            Vertex vParent = *vi;
            std::vector<Vertex> vertexDescriptors;
            std::vector<Edge> edgeDescriptors;
            //modified bfsvisitor class designed to return the edges traversed rather than the nodes visited
            BfsVisitor<myGraph> bfsVisitor(edgeDescriptors);
            //breadth first search to return the path of edges taken into vector edgeDescriptors
            boost::breadth_first_search(g, vParent, visitor(bfsVisitor).vertex_index_map(propmapIndex));
            //iterate across the traversed edges and increment their centrality if they have already been traversed
            for(auto ei = edgeDescriptors.begin(); ei != edgeDescriptors.end(); ei++){
                if(centralityMap.count(*ei) != 0){
                    centralityMap[*ei] += 1;
                }
                else{
                    //create new KV pair for edges which have not yet been traversed, centrality initiazlied to 0
                    centralityMap.insert(std::pair<Edge, int>(*ei, 0));
                }
            }
        }
        //determine edge with maximum centrality
        auto highest_centrality_edge = centralityMap.begin();
        for(auto iter = centralityMap.begin(); iter != centralityMap.end(); iter++){
            if(iter->second > highest_centrality_edge->second){
                highest_centrality_edge = iter;
            }
        }
        //cout << highest_centrality_edge->first << " " << highest_centrality_edge->second << endl;
        Edge max = highest_centrality_edge->first;
        g.remove_edge(max);
    }
    //boost::print_graph(g);
}
#endif //INC_22S_PA03_GIRVAN_NEWMAN_CHURCHOFCHOVY_NEWMAN_H
