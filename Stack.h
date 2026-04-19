//Muhammad Yousaf
//i228797
//SE-F
#ifndef STACK_H
#define STACK_H
#include <iostream>
using namespace std;

template <typename T>
class DynamicStack
{
    struct Node
    {
        T value;
        Node* next;

        Node(T val) : value(val), next(nullptr) {}
    };

    Node* top;
    int size;

public:
    DynamicStack()
    {
        top = nullptr;
        size = 0;
    }

    ~DynamicStack()
    {
        Node* temp = top;

        while (top)
        {
            temp = top;
            top = top->next;
            delete temp;
        }
        size = 0;
    }

    bool isEmpty()
    {
        return top == nullptr;
    }

    void push(T val)
    {
        Node* newNode = new Node(val);

        newNode->next = top;
        top = newNode;
        size++;
    }

    void pop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty!" << endl;
        }
        else
        {
            Node* temp = top;
            top = top->next;
            delete temp;
            temp = nullptr;
            size--;
        }
    }

    T showTop()
    {
        return top->value;
    }

    void Display()
    {
        Node* current = top;
        while (current)
        {
            cout << current->value << " ";
            current = current->next;
        }
        cout << endl;
    }

    int getSize()
    {
        return size;
    }
};

#endif // !STACK_H
