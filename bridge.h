#ifndef __BRIDGE_H__
#define __BRIDGE_H__

#include <vector>
#include <iostream>
#include <string>
#include <map>

using namespace std;

struct configMessage
{
    int dist;
    int from;
    int root;

    bool operator==(const configMessage& m) const
    {
        return (dist==m.dist+1) && (from==m.from) && (root==m.root); 
    }

    bool operator<(const configMessage& m) const
    {
        return  (root<m.root) ||
                ((root==m.root) && (dist<m.dist+1)) ||
                ((root==m.root) && (dist<m.dist+1) && (from<m.from));
    }
};

enum ptype
{
    DP,
    RP,
    NP
};

class Bridge
{
    
    public:
        Bridge(string _name);

        void addport(int lan_idx);
        string getConfig();
        bool receiveConfig(configMessage m, int port);
    
        vector<bool> port;
        map<int,ptype> port_type;
        configMessage message;
        int id;
        int root_port;
        int next_bridge;
};
#endif // __BRIDGE_H__