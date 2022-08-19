#include "bridge.h"

using namespace std;


Bridge::Bridge(string name)
{
    id = stoi(name.substr(1)) - 1;  //Remove leading 'B', 0-indexing
    root_port = 26;
    port.resize(26,0);
    message.dist = 0;
    message.root = id;
    message.from = id;
    next_bridge = id;
}


void Bridge::addport(int port_idx)
{
    port[port_idx] = 1;
    port_type[port_idx] = DP; 
}

string Bridge::getConfig()
{
    return "B"+to_string(message.root+1)+", "+to_string(message.dist)+", B"+to_string(id+1);
}

bool Bridge::receiveConfig(configMessage m, int port)
{
    if((m.root < message.root)||//If root id less, update root 
        (m.root == message.root && m.dist+1 < message.dist)||//If root same, but distance less, update root port
        (m.root == message.root && m.dist+1 == message.dist && m.from < next_bridge)||//If only sender id less, update root port
        (m.root == message.root && m.dist+1 == message.dist && m.from == message.from && port < root_port))//If only sender id less, update root port
    {
        message.dist = m.dist + 1;
        message.root = m.root;
        next_bridge = m.from;
        root_port = port;

        //Change all ports to DP as network topology changed
        for(auto& x : port_type){
            if(x.second!=DP) x.second=DP;   
        }

        //Set new RP
        port_type[port] = RP;

        //Check if any other port is DP       
        bool flag = true;
        for(auto x : port_type){
            if(x.second == DP){
                flag = false;
                break;
            }
        }
        if(flag){
            port_type[port] = NP;   // If no DP present, then change RP to NP too
        }
        return true;
    }
    
    else if((m.root == message.root) &&
            ((m.dist < message.dist) || 
             (m.dist == message.dist && m.from < id))&&
            (port_type[port]==DP))
    {
        port_type[port] = NP;

        //Check if any other port is DP       
        bool flag = true;
        for(auto x : port_type){
            if(x.second == DP){
                flag = false;
                break;
            }
        }
        if(flag){   // If no DP present, then change RP to NP too
            port_type[root_port] = NP;
            root_port = 26;
        }
        return true;
    }

    else return false;
}