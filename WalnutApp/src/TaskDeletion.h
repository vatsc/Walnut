#include <iostream>
#include <fstream>
#include <filesystem>
//#include "PriorityQueueLL.cpp"
using namespace std;

//PList ll;


void deletion(const string& exact){
    ifstream fi;
    fi.open("Menu.txt");
    ofstream t;
    t.open("tmp.txt");
    string buffer;
    while(getline(fi,buffer)){
        if(buffer!=exact){
            t<<buffer<<endl;
        }
    }
    fi.close();
    t.close();
    filesystem::remove("Menu.txt");
    filesystem::rename("tmp.txt","Menu.txt");
    filesystem::remove(exact+".txt");
    //ll.delete_node(exact);
}
