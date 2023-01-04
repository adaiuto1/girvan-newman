//
// Created by ABD on 4/8/2022.
//

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/properties.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/betweenness_centrality.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/visitors.hpp>
#ifndef INC_22S_PA03_GIRVAN_NEWMAN_CHURCHOFCHOVY_BFSVISITOR_H
#define INC_22S_PA03_GIRVAN_NEWMAN_CHURCHOFCHOVY_BFSVISITOR_H
// modified custom bfs visitor class from https://stackoverflow.com/a/43780529
template <class Graph>
        class BfsVisitor : public boost::default_bfs_visitor
                {
                public:
                    typedef typename boost::graph_traits<Graph>::vertex_descriptor VertexDescriptor;
                    typedef typename boost::graph_traits<Graph>::edge_descriptor   EdgeDescriptor;

                    BfsVisitor(std::vector<EdgeDescriptor>& nodesVisited)
                    : m_nodesVisited(nodesVisited){}

                    void tree_edge(EdgeDescriptor e, const Graph& g) const
                    {
                        VertexDescriptor u = source(e, g);
                        VertexDescriptor v = target(e, g);
                        m_nodesVisited.push_back(e);
                    }

                private:
                    std::vector<EdgeDescriptor>& m_nodesVisited;
                };
#endif //INC_22S_PA03_GIRVAN_NEWMAN_CHURCHOFCHOVY_BFSVISITOR_H
