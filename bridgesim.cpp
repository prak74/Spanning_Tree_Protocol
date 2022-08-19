#include "bridgesim.h"
#include <algorithm>

using namespace std;


BridgeSim::BridgeSim()
{
    graph.resize(26);
    t = 0;
}

void BridgeSim::add_bridge(Bridge b)
{
    all_bridges.push_back(b);
}

void BridgeSim::generate_graph(bool trace)
{
    bool update = true;
    while(update){
        update = false;

        vector<pair<int,pair<int,string>>> send;   //<sender,<port,message>>
        vector<pair<pair<int,int>,pair<int,configMessage>>> receive;   //<<sender,receiver>,<port,message>>

        //Send messages
        for(Bridge& b : all_bridges)
        {
            string config = b.getConfig();
            
            for(int i=0;i<26;i++)
            {
                if(b.port[i] && b.port_type[i]==DP) //if DP port, then send message  
                {      
                    //Add message to sent
                    pair<int,string> temp{i,config};
                    send.push_back({b.id,temp});    

                    //Add message to received
                    pair<int,configMessage> temp2{i,b.message};
                    for(auto k : graph[i])
                    {           
                        if(k==b.id) continue;   //If same as sending port, skip
                        receive.push_back({{b.id,k},temp2});   //Else receive the message at the other bridge
                    }
                } 
            }
        }

        sort(send.begin(),send.end());
        if(trace)
        {
            for(auto x : send)
            {
                cout<< t << " s B"<< x.first+1 << " ("<< x.second.second <<")\n";
            }
            cout<<'\n';
        }
        

        t++;
        sort(receive.begin(),receive.end());
        if(trace)
        {
            for(auto x : receive)
            {
                string temp = all_bridges[x.first.first].getConfig();
                cout<< t << " r B"<< x.first.second+1 << " ("<< temp <<")\n";
            }
            cout<<'\n';
        }
        

        //Receive Messages
        for(auto x : receive)
        {
            configMessage config = x.second.second; // Message from sender
            int i = x.second.first; // Port id on which message was sent
            Bridge& receiver = all_bridges[x.first.second];       // Receiver bridge

            update |= receiver.receiveConfig(config, i);
        }
    }
    // Print final status
    for(auto& b : all_bridges){
        cout<<"B"+to_string(b.id+1)+": ";
        for(auto& x : b.port_type){
            string ptype;
            switch(x.second){
                case DP:
                    ptype = "DP";
                    break;
                case RP:
                    ptype = "RP";
                    break;
                case NP:
                    ptype = "NP";
                    break;
            }
            cout<<(char)('A'+x.first)<<"-"<<ptype<<" ";
        }
        cout<<'\n';
    }
}