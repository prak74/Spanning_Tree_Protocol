#ifndef __BRIDGESIM_H__
#define __BRIDGESIM_H__

#include <vector>
#include "bridge.h"

using namespace std;

class BridgeSim
{
    public:
        vector<vector<int>> graph;      //lan to bridge mapping
        
        BridgeSim();
        void add_bridge(Bridge b);
        void generate_graph(bool trace);

    private:
        vector<Bridge> all_bridges;
        int t;
};
#endif // __BRIDGESIM_H__