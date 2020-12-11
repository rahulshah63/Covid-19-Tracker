#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

typedef struct node * nodePtr;
struct node
{
	string country;
    int totalCase, totalActive, totalRecovery, totalDeath;
    node *next;
};

nodePtr globalHead;
class linked_list
{
private:
    node *head,*tail;

public:
    linked_list();
    void add_node(string, int, int, int, int);
    void mergeSort(nodePtr*);
    void reverseList();
    void partition(nodePtr, nodePtr*, nodePtr*);
    void display();
    void exchangeData(string **, int);


    nodePtr mergeLists(nodePtr, nodePtr);

    friend void loadFile(int);

public:
    int choice;

};

linked_list::linked_list()
{
    head = NULL;
    tail = NULL;
}

void linked_list::add_node(string name, int tcase, int tactive, int trecovery ,int tdeath)
{
    node *tmp = new node;
    tmp-> country = name;
    tmp-> totalCase = tcase;
    tmp-> totalActive = tactive;
    tmp-> totalRecovery = trecovery;
    tmp-> totalDeath = tdeath;
    tmp-> next = NULL;

    if(head == NULL)
    {
        head = tmp;
        tail = tmp;
        globalHead = head;
    }
    else
    {
        tail->next = tmp;
        tail = tail->next;
    }
}

void linked_list::partition(nodePtr head, nodePtr *front, nodePtr *back)
{
    nodePtr fast;
    nodePtr slow;

    if (head == NULL || head->next == NULL)
    {

        *front = head; // &a
        *back = NULL; // &b

    }
    else
    {
        slow = head;
        fast = head->next;

        while(fast != NULL)
        {

            fast = fast->next;

            if(fast != NULL)
            {
                slow = slow->next;
                fast = fast->next;
            }
        }

        *front = head; // a
        *back = slow->next; // b
        slow->next = NULL;

    }
}

nodePtr linked_list::mergeLists(nodePtr a, nodePtr b)
{
    nodePtr mergedList = NULL;

    if (a == NULL)
    {
        return b;
    }
    else if (b == NULL)
    {
        return a;
    }

int value1, value2;
   if(choice == 1)
    {
        value1 = a->totalCase;
        value2 = b->totalCase;
    }
    else if(choice == 2)
    {
        value1 = a->totalActive;
        value2 = b->totalActive;
    }
    else if(choice == 3)
    {
        value1 = a->totalRecovery;
        value2 = b->totalRecovery;
    }
    else if(choice == 4)
    {
        value1 = a->totalDeath;
        value2 = b->totalDeath;
    }


    if (value1<= value2)
    {
        mergedList = a;
        mergedList->next = mergeLists(a->next, b);
    }
    else
    {
        mergedList = b;
        mergedList->next = mergeLists(a, b->next);
    }

    return mergedList;

}

void linked_list::mergeSort(nodePtr *source)
{
    nodePtr head = *source;
    nodePtr a = NULL;
    nodePtr b = NULL;

    if(head == NULL || head->next == NULL)
    {
        return;

    }

    partition(head, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    *source = mergeLists(a, b);

}

void linked_list::reverseList()
{
    head=globalHead;
    struct node *prevNode, *curNode;

    if(head != NULL)
    {
        prevNode = head;
        curNode = head->next;
        head = head->next;

        prevNode->next = NULL; // Make first node as last node

        while(head != NULL)
        {
            head = head->next;
            curNode->next = prevNode;

            prevNode = curNode;
            curNode = head;
        }

        head = prevNode; // Make last node as head
    }
}

void linked_list::exchangeData(string **nameAndData, int data) {
    struct node *curNode = head;
    for (int i = 0; i < data; i++) {
        for (int j = 0; j < 2; j++) {
             if (j == 0) {
                nameAndData[i][j] = curNode->country;//storing country name as string
             }

            else {
                if (choice == 1)
                    nameAndData[i][j] = to_string(curNode->totalCase);
                else if (choice == 2)
                    nameAndData[i][j] = to_string(curNode->totalActive);
                else if(choice == 3)
                    nameAndData[i][j] = to_string(curNode->totalRecovery);
                else if(choice == 4)
                    nameAndData[i][j] = to_string(curNode->totalDeath);
            }
        }
        curNode = curNode->next;
    }
}

void linked_list::display()
{
   struct node* ptr;
   ptr = head;
   cout << "\nCountry" <<setw(15)<< "TotalCase"<<setw(15)<< "TotalActive"<<setw(15)<< "TotalRecovery"<<setw(15)<< "TotalDeath"<<endl;
   while (ptr != NULL)
    {
      cout<< ptr->country<<setw(15)<< ptr->totalCase<<setw(15)<< ptr->totalActive<<setw(15)<< ptr->totalRecovery<<setw(15)<< ptr->totalDeath<<endl;
      ptr = ptr->next;
    }
}
