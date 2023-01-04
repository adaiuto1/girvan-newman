//
// Created by ABD on 4/11/2022.
//

#include "Newman.h"
#ifndef INC_22S_PA03_GIRVAN_NEWMAN_CHURCHOFCHOVY_KAREN_H
#define INC_22S_PA03_GIRVAN_NEWMAN_CHURCHOFCHOVY_KAREN_H
using namespace std;

class Karen{
public:
    Karen(myGraph&);
    void findKingpins(string);
    void printTags();
private:
    myGraph h;
    ifstream inFile;
    ofstream oFile;
    GraphTraits::vertex_iterator iter1, iter2;
    GraphTraits::out_edge_iterator eii1, eii2, eio1, eio2;
    std::map<Vertex, vector<Vertex>> kingpins;
    //first = each kingpin
    //second = each author within 2 degrees of separation with out_degree < 10
};
Karen::Karen(myGraph& sh){
    h = sh;
}
void Karen::findKingpins(string subject){
    auto v = boost::get(&vertexData::name, h);
    for(boost::tie(iter1, iter2) = boost::vertices(h); iter1 != iter2; iter1++){
        if(boost::out_degree(*iter1, h) >= 10){
//            kingpins.insert(pair<Vertex, vector<Vertex>>(*iter1, vector<Vertex>()));
            //cout << *iter1 << ": ";
            for(boost::tie(eii1, eii2) = boost::out_edges(*iter1, h); eii1 != eii2; eii1++){ //iterate across out_edges of kingpin
                auto outEdge1 = *eii1;
                auto t = boost::target(outEdge1, h);
                if(boost::out_degree(t, h) < boost::out_degree(*iter1, h)){
                    if(kingpins.count(t) != 0){
                        kingpins[*iter1].push_back(boost::target(outEdge1, h)); //insert all targets of out_edges into domain of kingpin
                    }
                    else{
                        kingpins.insert(std::pair<Vertex, vector<Vertex>>(*iter1, vector<Vertex>()));
                        kingpins[*iter1].push_back(boost::target(outEdge1, h));
                    }
                }
                Vertex firstDegree = boost::source(outEdge1, h); //declare current node as the first degree of separation
                for(boost::tie(eio1, eio2) = boost::out_edges(firstDegree, h); eio1 != eio2; eio1++){ //iterate the out_edges of the out_edges of the kingpin
                    auto outEdge2 = *eio1;
                    auto degree2 = boost::target(outEdge2, h);
                    if(boost::out_degree(degree2, h) < boost::out_degree(*iter1, h)){ //insert all the 2-degree-separation nodes into
                        int fk = 0;
                        for(Vertex vv : kingpins[*iter1]){
                            if(vv == degree2){
                                fk++;
                            }
                        }
                        if(fk == 0){
                            kingpins[*iter1].push_back(degree2);
                        }
                    }
                }
            }

        }
    }
    cout << subject << " assists kingpins:" << endl;
    for(pair<Vertex, vector<Vertex>> p : kingpins){
        //cout << v[p.first] << ": ";
        for(Vertex i : p.second){
            if(v[i] == subject){
                cout << v[p.first] << endl;
                break;
            }

           // cout << v[i] << endl;
        }
    }
}
void Karen::printTags(){

}
#endif //INC_22S_PA03_GIRVAN_NEWMAN_CHURCHOFCHOVY_KAREN_H
