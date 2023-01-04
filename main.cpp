#include <boost/regex.hpp>
#include <string>
#include "Karen.h"
#include <chrono>
struct vd{
    string n;
};
using namespace std;
int main()
{
    cout << "enter subject" << endl;
    string input;
    getline(cin, input);
    cout << input << endl;
    int iterations = 20;
    Newman* n = new Newman(iterations, "netscience");
    n->readData();
    n->runAlgo();
//    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
//    vd, boost::property<boost::edge_weight_t, double>>ball;
//    ball basket;
//    boost::dynamic_properties dp1(boost::ignore_other_properties);
//    dp1.property("label", boost::get(&vd::n, basket));
//    ifstream b("data/netscience.graphml");
//    boost::read_graphml(b, basket, dp1);
//    boost::graph_traits<ball>::vertex_iterator v1, v2;
//    auto v = boost::get(&vd::n, basket);
//    for(boost::tie(v1, v2) = boost::vertices(basket); v1 != v2; v1++){
//        cout << v[*v1] << endl;
//    }
//    ofstream o("netscience.graphml");
//    boost::write_graphml(o, basket, dp1);
    //ifstream i("output/netscience.graphml");
    //boost::read_graphml(i, op, dp1);
    Karen k(n->getGraph());
    k.findKingpins(input);
////    auto start1 = std::chrono::steady_clock::now();
//    n->runAlgo();
////    auto end1 = std::chrono::steady_clock::now();
////    std::chrono::duration<double> elapsed_seconds1 = end1-start1;
////    cout << "newman algorithm removing every " << iterations << "th edge: ";
////    cout << fixed <<  elapsed_seconds1.count() << endl;
//    n->writeData();
//
//    n->print();
}