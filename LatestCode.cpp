#include <iostream>
#include <stdio.h>
#include <atomic>
#include <thread>
#include <vector>
#include <string>

using namespace std;

struct Node {
public:

    int data;   //������ ���� ����
    Node* next; //���� ����� ������ ���� ������(�ּҰ� ����)
};

class LinkedList {
private:
    //Node* head = NULL;
    std::atomic <Node*> head;
    Node* tail;
    int size = 0;           //��ũ�� ����
public:
    LinkedList() : head(nullptr), tail(nullptr) {}
    ~LinkedList() {} //�Ҹ���

public:
    int headReturn() {
        if (head == nullptr)
        {
            return 1;
        }
        else
        {
            return 2;
        }
    }

    void push(Node* pNewNode) {
        //Node* next;
        Node* t = head; //t = next

        while (!head.compare_exchange_weak(t, pNewNode)) //head�� pNewNode�� �Ǹ� Ż��
            pNewNode->next = t;
        //head�� t�� ������ pNewNode�� �ٲ��
        size++;

    }

    Node* pop()
    {
        Node* current = head;
        while (current) {
            if (!head.compare_exchange_weak(current, current->next)) { //current->next

                return current;
            }

            current = head;
        }return NULL;
    }
    void display() {
        Node* ptr;
        if (head == NULL) {
            cout << "stack is empty";
        }
        else {
            ptr = head;
            cout << "stack element : ";
            while (ptr != NULL) {
                cout << ptr->data << " ";
                ptr = ptr->next;
            }
        }
        cout << endl;
    }
    void FUNCfreeList(Node* head)
    {
        for (int i = 0; i < 100; i++)
        {
            Node* node = new Node;      //����� ����ü�� ������ ��
            node->data = i;
            node->next = nullptr;

            if (head == nullptr) //���� �Ӹ��� ������� 
            {
                head = node;
                tail = node;
            }

            else // ���� �Ӹ��� ������� �ڿ� ���� 
            {
                tail->next = node;
                tail = tail->next;
            }
        }
    }

};

LinkedList freeList;    //��ũ�帮��Ʈ ��ü freeList ����
LinkedList headList;

//static void           //(std::atomic<int>& i)
static void ThreadBody1(std::atomic<int>& i)
{
   
    //freeList->head = head;
    //Node* freeList;
    int i = 0;
    while (i < 10000)
    {
        for(int j=0;j<100;j++)
            if (freeList.headReturn() == 1)
            {
                //Node *headList;
                freeList.push(headList);
            }
        for (int j = 0; j < 100; j++)
        {
            if (head != nullptr)
            {
                Node* freeList;
                headList.pop();
                headList.push(freeList * head);
            }
        }
        
        i++;
    }
}
/*
void ThreadBody()
{
    cout << ThreadBody1 << endl;
}
*/

//void ThreadBody();
//std::thread thread1(ThreadBody1);


int main() {
    //void ThreadBody();
  
    //LinkedList<int> List;
    
    thread thread1(ThreadBody1);
    
    /*
    LinkedList(display);
    LinkedList(pop);
    freeeList.display();
    headList.pop();
    */
    std::atomic<int> i = 0;


//    void FUNCfreeList();


//    freeList.display();



    thread1.join();
    


    return 0;
}
