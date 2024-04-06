#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

int YEAR, MONTH, DATE, TF;

void checkCurrent() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    YEAR= 1900 + ltm->tm_year;
    MONTH= 1 + ltm->tm_mon;
    DATE= ltm->tm_mday;
    TF=100*(ltm->tm_hour)+ltm->tm_min;
}

class CreateTask{
public:
    string name;//name of Task
    bool status;//true=complete
    int dd,mm,yyyy;//int value of the date
    int tm;//time in 24 hour format
    short prio;//priority(1,2,3)

    //the following values are input dependant

    bool td;//false=date has passed, true= to do
    string exact;//has the exact time in yyyymmddttttx format
    string fname;//stores the file name of the Task;


    CreateTask(){//default constructor
        name="";
        status=false;
        dd=0,mm=0,yyyy=0;
        tm=0000;
        prio=0;
        td=true;
        exact="0000000000000";
        fname="0000000000000.txt";
    }
    void refresh();//this updates the values of the input dependant values. Needs to be called after input.
    void createFile();//creates the file
};

void CreateTask::refresh(){
    if(YEAR<yyyy){
        td=true;
    }
    else if(YEAR> yyyy){
        td=false;
    }
    else{
        if(MONTH< mm){
            td=true;
        }
        else if(MONTH> mm){
            td=false;
        }
        else{
            if(DATE< dd){
                td=true;
            }
            else if(DATE> dd){
                td=false;
            }
            else{
                if(TF<=tm){
                    td=true;
                }
                else if(TF>tm){
                    td=false;
                }
            }
        }
    }
    if(yyyy>999){
        exact=to_string(yyyy);
    }
    else if(yyyy>99){
        exact="0"+to_string(yyyy);
    }
    else if(yyyy>9){
        exact="00"+to_string(yyyy);
    }
    else{
        exact="000"+to_string(yyyy);
    }
    if(mm>9){
        exact= exact+to_string(mm);
    }
    else{
        exact=exact+"0"+to_string(mm);
    }
    if(dd>9){
        exact= exact+to_string(dd);
    }
    else{
        exact=exact+"0"+to_string(dd);
    }
    if(tm>999){
        exact=exact+to_string(tm);
    }
    else if(tm>99){
        exact=exact+"0"+to_string(tm);
    }
    else if(tm>9){
        exact=exact+"00"+to_string(tm);
    }
    else{
        exact=exact+"000"+to_string(tm);
    }
    //fname=exact+".txt";
}

void CreateTask::createFile(){
    for(int i=0; i<10; i++) {
        ifstream test;
        fname=exact+to_string(i)+".txt";
        test.open(fname);
        if (!test) {
            fstream fio;
            fio.open(fname, ios::out);
            fio << name << endl << status << endl << dd << endl << mm << endl << yyyy << endl << tm << endl << prio
                << endl << td;
            exact+=to_string(i);
            fio.close();
            test.close();
            break;
        }
    }
    fstream menu;
    menu.open("Menu.txt", ios::app);
    menu<<exact<<endl;
    menu.close();
    //ll.insert(exact);
}

void load(string namo, int dd, int mm, int yy, int tt, short pp){
    checkCurrent();
    CreateTask q;
    q.name=namo;
    q.dd=dd;
    q.mm=mm;
    q.yyyy=yy;
    q.tm=tt;
    q.prio=pp;
    q.refresh();
    q.createFile();
}