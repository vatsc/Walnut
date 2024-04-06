#pragma once
#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"
#include "Walnut/Image.h"
#include "Walnut/UI/UI.h"
#include "TaskAccess.h"
#include "TaskDeletion.h"
#include "TaskCreation.h"

#include <ctime>



static int m_AddTask = 0, m_RemoveTask = 0, m_MarkTaskAsComplete = 0, m_Level = 1, m_Hour = 00, m_Minute = 00, m_year = 2005, m_CreateTask = 0, m_Time;
static char m_task[128];


const char* m_day[31] = { "1", "2","3","4","5","6", "7", "8", "9", "10", "11", "12", "13", "14","15","16", "17", "18", "19", "20", "21", "22",  "23",  "24",  "25",  "26",  "27",  "28",  "29",  "30", "31" };
const char* m_Day[30] = { "1", "2","3","4","5","6", "7", "8", "9", "10", "11", "12", "13", "14","15","16", "17", "18", "19", "20", "21", "22",  "23",  "24",  "25",  "26",  "27",  "28",  "29",  "30" };
const char* feb[28] = { "1", "2","3","4","5","6", "7", "8", "9", "10", "11", "12", "13", "14","15","16", "17", "18", "19", "20", "21", "22",  "23",  "24",  "25",  "26",  "27",  "28" };
const char* leap[29] = { "1", "2","3","4","5","6", "7", "8", "9", "10", "11", "12", "13", "14","15","16", "17", "18", "19", "20", "21", "22",  "23",  "24",  "25",  "26",  "27",  "28",  "29" };
const char* m_months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
static int month_current = 0;
static int day_current = 0;
int counter = 0;
static bool checkRT[5];

static bool checkCT = false;



static int date, month, year, tf;
void setCurrent() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    year = 1900 + ltm->tm_year;
    month = 1 + ltm->tm_mon;
    date = ltm->tm_mday;
    tf = 100 * (ltm->tm_hour) + ltm->tm_min;
}

class Node {
public:
    string a;
    Node* llink, * rlink;
    Node()
    {
        a = "0000000000000";
        llink = nullptr;
        rlink = nullptr;

    }
};
class PList {
public:
    Node* head;
    int n;
    PList()
    {
        head = nullptr;
    }
    void initialise() {
        head = nullptr;
        ifstream fi;
        fi.open("Menu.txt");
        string buffer;
        while (getline(fi, buffer)) {
            insert(buffer);
        }
    }
    void display() {
        Node* nn = head;
        while (nn != nullptr) {
            cout << nn->a << endl;
            nn = nn->rlink;
        }
    }
    void insert(string z)
    {
        Node* tmp = new Node();
        Node* nn = head;
        tmp->a = z;
        if (head == nullptr)
        {
            head = tmp;
            return;
        }
        while (nn != nullptr)
        {
            if (tmp->a < nn->a)
            {
                if (nn == head)
                {
                    tmp->rlink = nn;
                    nn->llink = tmp;
                    head = tmp;
                }
                else
                {
                    tmp->rlink = nn;
                    tmp->llink = nn->llink;
                    nn->llink->rlink = tmp;
                    nn->llink = tmp;
                }
                break;
            }
            else if (nn->rlink == nullptr) {
                tmp->llink = nn;
                nn->rlink = tmp;
                tmp->rlink = nullptr;
                break;
            }
            nn = nn->rlink;
        }

    }
    bool find(string s)
    {
        Node* h = head;
        while (h != nullptr)
        {
            if (h->a == s)
            {
                return true;
            }
            h = h->rlink;
        }
        return false;
    }
    void delete_node(string z)
    {
        Node* h = head;
        while (h != nullptr)
        {
            if (h->a == z)
            {
                if (h == head)
                {
                    head = h->rlink;
                    if (head != nullptr) {
                        head->llink = nullptr;
                    }
                    break;
                }
                else if (h->rlink == nullptr)
                {
                    Node* tmp = h->llink;
                    tmp->rlink = nullptr;
                    break;
                }
                else
                {
                    Node* tmp = h->llink;
                    tmp->rlink = h->rlink;
                    h = h->rlink;
                    h->llink = tmp;
                    break;
                }
            }
            h = h->rlink;
        }
    }
};
PList ll;
class Reminder {
public:
    Node* rem;
    void createRem() {
        rem = nullptr;
        Node* nn = ll.head;
        while (nn != nullptr && !retToDo(nn->a)) {
            nn = nn->rlink;
        }
        while (nn != nullptr) {
            string exact = nn->a;
            if (needRem(exact)) {
                insertRem(exact);
            }
            nn = nn->rlink;
        }
    }
    bool needRem(const string& exact) {
        int monthA[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        int d, m, y;
        d = retDate(exact);
        m = retMonth(exact);
        y = retYear(exact);
        short p = retPrio(exact);
        if (p == 1) {
            d -= 2;
            if (d < 1) {
                m--;
                if (m < 1) {
                    m = 12;
                    y--;
                }
                d = monthA[m - 1] + d;
            }
        }
        else if (p == 2) {
            d -= 10;
            if (d < 1) {
                m--;
                if (m < 1) {
                    m = 12;
                    y--;
                }
                d = monthA[m - 1] + d;
            }
        }
        else if (p == 3) {
            m--;
            if (m < 1) {
                m = 12;
                y--;;
            }
        }
        if (y < year) {
            return true;
        }
        if (y == year && m < month) {
            return true;
        }
        if (y == year && m == month && d <= date) {
            return true;
        }
        return false;
    }
    void insertRem(string exact) {
        Node* tmp = new Node;
        tmp->a = exact;
        if (rem == NULL)
        {
            rem = tmp;
            return;
        }

        Node* trav = rem;
        while (trav->rlink != nullptr) {
            trav = trav->rlink;
        }

        //tmp->a = exact;
        tmp->rlink = nullptr;
        trav->rlink = tmp;
        tmp->llink = trav;
    }
};
Reminder rr;

void SetcheckRT()
{
    for (int i = 0; i < 5; i++)
    {
        checkRT[i] = false;
    }
}

void updateToDo(const string& exact) {
    int dd = retDate(exact);
    int mm = retMonth(exact);
    int yyyy = retYear(exact);
    int tm = retTime(exact);
    bool td;
    if (year < yyyy) {
        td = true;
    }
    else if (year > yyyy) {
        td = false;
    }
    else {
        if (month < mm) {
            td = true;
        }
        else if (month > mm) {
            td = false;
        }
        else {
            if (date < dd) {
                td = true;
            }
            else if (date > dd) {
                td = false;
            }
            else {
                if (tf <= tm) {
                    td = true;
                }
                else if (tf > tm) {
                    td = false;
                }
            }
        }
    }
    ifstream fi;
    fi.open(exact + ".txt");
    ofstream tmp;
    tmp.open("temp.txt");
    string buffer;
    int c = 0;
    while (getline(fi, buffer)) {
        if (c == 7) {
            tmp << td << endl;
        }
        else {
            tmp << buffer << endl;
        }
        c++;
    }
    fi.close();
    tmp.close();

    filesystem::remove(exact + ".txt");
    filesystem::rename("temp.txt", exact + ".txt");
}
void refreshToDo() {
    Node* nn = ll.head;
    string exact;
    while (nn != nullptr) {//refresh
        exact = nn->a;
        updateToDo(exact);//checks current time
        nn = nn->rlink;
    }
}
void REFRESH() {
    refreshToDo();
    rr.createRem();
}

Node* past;
Node* present;
Node* future;
class ExampleLayer : public Walnut::Layer
{
public:

    virtual void OnUIRender() override
    {
        setCurrent();
        ll.initialise();
        refreshToDo();
        rr.createRem();

        ImGui::Begin("Tasks");

        ImGui::PushID(4);
        ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(4 / 7.0f, 0.6f, 0.6f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(4 / 7.0f, 0.7f, 0.7f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(4 / 7.0f, 0.8f, 0.8f));
        if (ImGui::Button("Add Task", ImVec2(350, 100)))
            m_AddTask++;
        ImGui::PopStyleColor(3);
        ImGui::PopID();

        if (m_AddTask & 1)
        {
            ImGui::NewLine();
            ImGui::PushItemWidth(500); ImGui::InputTextWithHint("...", "Enter Task Name", m_task, IM_ARRAYSIZE(m_task)); ImGui::PopItemWidth();
            ImGui::NewLine();
            ImGui::Text("Enter Priority Level of the Task(1 - 3)");
            ImGui::PushItemWidth(100); ImGui::InputInt("..", &m_Level);  ImGui::PopItemWidth();
            ImGui::NewLine();
            ImGui::Text("Enter Time(in 24 hour format)");
            ImGui::PushItemWidth(100); ImGui::InputInt(":", &m_Hour); ImGui::PopItemWidth(); ImGui::SameLine(); ImGui::PushItemWidth(100); ImGui::InputInt(".", &m_Minute); ImGui::PopItemWidth();
            ImGui::NewLine();
            ImGui::InputInt("Year", &m_year);
            ImGui::NewLine();
            ImGui::ListBox("Month", &month_current, m_months, IM_ARRAYSIZE(m_months), 4);
            ImGui::NewLine();
            if (m_year % 4 == 0 && month_current == 1)
                ImGui::ListBox("Date", &day_current, leap, IM_ARRAYSIZE(leap), 10);
            else if (month_current == 1)
                ImGui::ListBox("Date", &day_current, feb, IM_ARRAYSIZE(feb), 10);
            else if (month_current == 0 || month_current == 2 || month_current == 4 || month_current == 6 || month_current == 7 || month_current == 9 || month_current == 11)
                ImGui::ListBox("Date", &day_current, m_day, IM_ARRAYSIZE(m_day), 10);
            else
                ImGui::ListBox("Date", &day_current, m_Day, IM_ARRAYSIZE(m_Day), 10);





            m_Time = m_Hour * 100 + m_Minute;


            if (ImGui::Button("Create Task", ImVec2(200, 50)))
                m_CreateTask++;



            if (m_CreateTask == 1)
            {
                //ImGui::Text("The button was clicked");
                load(m_task, day_current + 1, month_current + 1, m_year, m_Time, m_Level);
                m_CreateTask = 0;
            }
        }
        /*if (ImGui::Button("Remove Task"))
            m_RemoveTask++;
        if (m_RemoveTask & 1)
        {
            ImGui::NewLine();
            ImGui::Text("Mark the Task you want to remove");
            ImGui::Checkbox(m_task, &checkRT);

        }*/
        /*if (ImGui::Button("Mark Task as complete"))
            m_MarkTaskAsComplete++;
        if (m_MarkTaskAsComplete & 1)
        {
            ImGui::NewLine();
            ImGui::Text("Mark the completed tasks");
            ImGui::Checkbox(m_task, &checkCT);
        }*/

        //ImGui::Text("Lets go, First app");
        ImGui::End();
        int runP;
        int runT = 1;
        past = ll.head;
        present = NULL;
        if (past != NULL)
        {
            runP = 1;
            if (!retToDo(past->a))
            {
                while (past != NULL && !retToDo(past->a))
                {
                    past = past->rlink;
                    runT++;
                }
                present = past;

                past = ll.head;
            }
            else
            {
                past = NULL;
                present = ll.head;
            }
        }
        else
        {
            present = past;
        }
        future = rr.rem;
        ImGui::Begin("Status");
        if (!(ImGui::TreeNode("Task's Status")))
        {
            static ImGuiTableFlags flags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable;

            if (ImGui::BeginTable("table1", 3, flags))
            {
                ImGui::TableSetupColumn("Passed Tasks", ImGuiTableColumnFlags_WidthStretch);
                ImGui::TableSetupColumn("To do Tasks", ImGuiTableColumnFlags_WidthStretch);
                ImGui::TableSetupColumn("Reminder", ImGuiTableColumnFlags_WidthStretch);
                ImGui::TableHeadersRow();
                string name;
                string exact;
                int count = 0;
                Node* nn = ll.head;
                while (nn != nullptr) {
                    nn = nn->rlink;
                    count++;
                }


                for (int row = 0; row < count; row++)
                {
                    ImGui::TableNextRow();
                    for (int column = 0; column < 3; column++)
                    {
                        if (past != NULL && column == 0 && !retToDo(past->a))
                        {
                            exact = past->a;
                            ImGui::TableSetColumnIndex(column);

                            name = retName(exact);
                            //   name = "McD";
                                  // ImGui::Text("%s", name.c_str());
                                //   counter++;

                            checkRT[row] = retStatus(exact);
                            if (ImGui::Checkbox(name.c_str(), &checkRT[row]))
                                editStatus(exact);
                            ImGui::NewLine();
                            ImGui::SameLine(); if (checkRT[row]) { ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Completed"); }
                            else { ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Incomplete"); }
                            string DelNo = "Delete " + to_string(runP++);
                            ImGui::SameLine(); ImGui::Text("\t\t\t\t\t"); ImGui::SameLine(); if (ImGui::Button(DelNo.c_str())) { deletion(exact); ll.delete_node(exact); };
                            int time = retTime(exact);
                            if (time % 100 != 0)
                                ImGui::Text("Date - %d/%d/%d    Time - %d:%d", retDate(exact), retMonth(exact), retYear(exact), time / 100, time % 100);
                            else
                                ImGui::Text("Date - %d/%d/%d   Time - %d:%d0", retDate(exact), retMonth(exact), retYear(exact), time / 100, time % 100);
                            past = past->rlink;



                        }
                        else if (present != NULL && column == 1)
                        {
                            exact = present->a;
                            name = retName(exact);
                            ImGui::TableSetColumnIndex(column);
                            //ImGui::Text("%s", name.c_str());
                            bool checkRT = retStatus(exact);

                            if (ImGui::Checkbox(name.c_str(), &checkRT))
                            {
                                editStatus(exact);
                            }
                            ImGui::NewLine();
                            ImGui::SameLine(); if (checkRT) { ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Completed"); }
                            else { ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Incomplete"); }
                            string DelNo = "Delete " + to_string(runT++);
                            ImGui::SameLine(); ImGui::Text("\t\t\t\t\t"); ImGui::SameLine(); if (ImGui::Button(DelNo.c_str())) { deletion(exact); ll.delete_node(exact); };
                            int time = retTime(exact);
                            if (time % 100 != 0)
                                ImGui::Text("Date - %d/%d/%d     Time - %d:%d", retDate(exact), retMonth(exact), retYear(exact), time / 100, time % 100);
                            else
                                ImGui::Text("Date - %d/%d/%d     Time - %d:%d0", retDate(exact), retMonth(exact), retYear(exact), time / 100, time % 100);
                            present = present->rlink;
                        }
                        else if (future != NULL && column == 2)
                        {
                            exact = future->a;
                            name = retName(exact);
                            ImGui::TableSetColumnIndex(column);
                            ImGui::Text("%s", name.c_str());
                            ImGui::Text("Priority: %d", retPrio(exact));
                            ImGui::NewLine();
                            int time = retTime(exact);
                            if (time % 100 != 0)
                                ImGui::Text("Date - %d/%d/%d     Time - %d:%d", retDate(exact), retMonth(exact), retYear(exact), time / 100, time % 100);
                            else
                                ImGui::Text("Date - %d/%d/%d     Time - %d:%d0", retDate(exact), retMonth(exact), retYear(exact), time / 100, time % 100);
                            future = future->rlink;
                        }
                    }
                }
                ImGui::EndTable();
            }
        }
        ImGui::End();

        // ImGui::ShowDemoWindow();

        UI_DrawAboutModal();
    }



    void UI_DrawAboutModal()
    {
        if (!m_AboutModalOpen)
            return;

        ImGui::OpenPopup("About");
        m_AboutModalOpen = ImGui::BeginPopupModal("About", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        if (m_AboutModalOpen)
        {
            auto image = Walnut::Application::Get().GetApplicationIcon();
            ImGui::Image(image->GetDescriptorSet(), { 48, 48 });

            ImGui::SameLine();
            Walnut::UI::ShiftCursorX(20.0f);

            ImGui::BeginGroup();
            ImGui::Text("Walnut application framework");
            ImGui::Text("by Studio Cherno.");
            ImGui::EndGroup();

            if (Walnut::UI::ButtonCentered("Close"))
            {
                m_AboutModalOpen = false;
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }
    }

    void ShowAboutModal()
    {
        m_AboutModalOpen = true;
    }

private:

    bool m_AboutModalOpen = false;
};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{


    Walnut::ApplicationSpecification spec;
    spec.Name = "Task Manager";
    spec.CustomTitlebar = true;

    Walnut::Application* app = new Walnut::Application(spec);
    std::shared_ptr<ExampleLayer> exampleLayer = std::make_shared<ExampleLayer>();
    app->PushLayer(exampleLayer);
    app->SetMenubarCallback([app, exampleLayer]()
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Exit"))
                {
                    app->Close();
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Help"))
            {
                if (ImGui::MenuItem("About"))
                {
                    exampleLayer->ShowAboutModal();
                }
                ImGui::EndMenu();
            }

            //if(ImGui::BeginMenu)
        });
    return app;
}