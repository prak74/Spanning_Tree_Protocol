#include <string>
#include <iostream>
#include <map>
#include "bridge.h"
#include "bridgesim.h"

using namespace std;

vector<string> tokenize(string s)
{
    vector<string> tokens;
    for(int i=0;i<s.size();){
        string temp;
        while(i < s.size() && s[i] !=' '){
            temp += s[i];
            i++;
        }
        tokens.push_back(temp);
        i++;
    }
    tokens[0] = tokens[0].substr(0,tokens[0].size()-1);
    return tokens;
}

int main(){

    bool trace;
    cin>>trace;
    cin.ignore();

    int num_bridges;
    cin>>num_bridges;
    cin.ignore();

    BridgeSim stp_sim;

    for(int i=0;i<num_bridges;i++){
        string s;
        getline(cin,s);
        vector<string> tokens = tokenize(s);                    // tokenize input for parsing
        Bridge temp(tokens[0]);                                 //Instantiate bridge object for the current bridge
        for(int j=1;j<tokens.size();j++){
            temp.addport(tokens[j][0]-'A');                     // Add lans to the bridge, assume lan to be an uppercase alphabet
            stp_sim.graph[tokens[j][0]-'A'].push_back(i);       // Add bridge to list of bridges joined to the lan
        }
        stp_sim.add_bridge(temp);                //Add the bridge into bridgesim
    }

    stp_sim.generate_graph(trace);

    return 0;
}