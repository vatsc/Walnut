#include <iostream>
#include <fstream>
#include <filesystem>
//#include "PriorityQueueLL.cpp"

using namespace std;

//PList ll;

string retName(const string& exact){
    ifstream fi;
    fi.open(exact+".txt");
    string name;
    getline(fi,name);
    fi.close();
    return name;
}

bool retStatus(const string& exact){
    ifstream fi;
    fi.open(exact+".txt");
    string buffer;
    int c=1;
    while(c--){
        getline(fi,buffer);
    }
    bool status;
    fi>>status;
    fi.close();
    return status;
}

int retDate(const string& exact){
    ifstream fi;
    fi.open(exact+".txt");
    string buffer;
    int c=2;
    while(c--){
        getline(fi,buffer);
    }
    int dd;
    fi>>dd;
    fi.close();
    return dd;
}

int retMonth(const string& exact){
    ifstream fi;
    fi.open(exact+".txt");
    string buffer;
    int c=3;
    while(c--){
        getline(fi,buffer);
    }
    int mm;
    fi>>mm;
    fi.close();
    return mm;
}

int retYear(const string& exact){
    ifstream fi;
    fi.open(exact+".txt");
    string buffer;
    int c=4;
    while(c--){
        getline(fi,buffer);
    }
    int yyyy;
    fi>>yyyy;
    fi.close();
    return yyyy;
}

int retTime(const string& exact){
    ifstream fi;
    fi.open(exact+".txt");
    string buffer;
    int c=5;
    while(c--){
        getline(fi,buffer);
    }
    int tm;
    fi>>tm;
    fi.close();
    return tm;
}

short retPrio(const string& exact){
    ifstream fi;
    fi.open(exact+".txt");
    string buffer;
    int c=6;
    while(c--){
        getline(fi,buffer);
    }
    short prio;
    fi>>prio;
    fi.close();
    return prio;
}

bool retToDo(const string& exact){
    ifstream fi;
    fi.open(exact+".txt");
    string buffer;
    int c=7;
    while(c--){
        getline(fi,buffer);
    }
    bool td;
    fi>>td;
    fi.close();
    return td;
}

void editStatus(const string& exact){
    ifstream fi;
    fi.open(exact+".txt");
    string buffer;
    getline(fi,buffer);
    bool status;
    fi>>status;
    fi.close();

    fi.open(exact+".txt");
    ofstream tmp;
    tmp.open("temp.txt");
    int c=0;
    if(status){
        while(getline(fi,buffer)){
            if(c==1){
                tmp<<0<<endl;
            }
            else{
                tmp<<buffer<<endl;
            }
            c++;
        }
    }
    else{
        while(getline(fi,buffer)){
            if(c==1){
                tmp<<1<<endl;
            }
            else{
                tmp<<buffer<<endl;
            }
            c++;
        }
    }
    fi.close();
    tmp.close();

    filesystem::remove(exact+".txt");
    filesystem::rename("temp.txt",exact+".txt");
}


/*
int countPast(){
    Node *nn=ll.head;
    int c=0;
    while(nn!= nullptr && !retToDo(nn->a)){
        c++;
        nn=nn->rlink;
    }
    past=c;
    return c;
}
*/


//Reminder rr;


/*
int main(){
    ll.initialise();
    Node *nn= ll.head;
    string exact;
    REFRESH();
    //refreshToDo();//checks all time
    int cp=countPast();//counts the past
    cout<<"Past Tasks...:\n";
    while(cp--){//past list
        exact=nn->a;
        cout<<retName(exact)<<"\t"<<retDate(exact)<<"/"<<retMonth(exact)<<"/"<<retYear(exact)<<endl;
        nn=nn->rlink;
    }
    cout<<"\nCurrent Date: "<<date<<"/"<<month<<"/"<<year<<"\n\nToDo Tasks...:\n";
    while(nn!= nullptr){//todolist
        exact=nn->a;
        cout<<retName(exact)<<"\t"<<retDate(exact)<<"/"<<retMonth(exact)<<"/"<<retYear(exact)<<endl;
        nn=nn->rlink;
    }
    cout<<"\n\nReminders...:\n";
    //rr.createRem();
    nn=rr.rem.rlink;
    while(nn!= nullptr){
        exact=nn->a;
        cout<<retName(exact)<<"\t"<<retDate(exact)<<"/"<<retMonth(exact)<<"/"<<retYear(exact)<<"\t("<<retPrio(exact)<<")"<<endl;
        nn=nn->rlink;
    }



    editStatus(exact);//assumes that the file exists, works as a toggle
    string name= retName(exact);
    cout<<name<<endl;
    bool status=retStatus(exact);
    cout<<status<<endl;
    int dd= retDate(exact);
    cout<<dd<<endl;
    int mm= retMonth(exact);
    cout<<mm<<endl;
    int yyyy= retYear(exact);
    cout<<yyyy<<endl;
    int tm= retTime(exact);
    cout<<tm<<endl;
    short prio= retPrio(exact);
    cout<<prio<<endl;
    bool td=retToDo(exact);
    cout<<td<<endl;

}*/