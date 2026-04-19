// Muhammad_Yousaf_22i8797_F
#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>

using namespace std;

template <typename T>
struct Node
{
    T value;
    Node<T>* next;
    Node(T val)
    {
        this->value = val;
        next = nullptr;
    }
};

template <typename T>
class Queue
{
    Node<T>* front;
    Node<T>* rear;
    int numItems;

public:
    Queue()
    {
        numItems = 0;
        front = nullptr;
        rear = nullptr;
    }
    ~Queue()
    {
        Node<T>* current = nullptr;
        while (front)
        {
            current = front;
            front = front->next;
            delete current;
        }
        rear = nullptr;
        numItems = 0;
    }

    void enqueue(T val)
    {
        Node<T>* newNode = new Node<T>(val);
        if (isEmpty())
        {
            rear = newNode;
            front = newNode;
            numItems++;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
            numItems++;
        }
    }

    void dequeue()
    {
        if (isEmpty())
        {
            cout << "The queue is empty!" << endl;
            return;
        }
        else
        {
            if (numItems == 1)
            {
                delete front;
                front = nullptr;
                rear = nullptr;
            }
            else
            {
                Node<T>* temp = front;
                front = front->next;
                delete temp;
            }
            numItems--;
        }
    }
    T showFront()
    {
        return front->value;
    }
    bool isEmpty()
    {
        return (this->numItems == 0);
    }

    int getNumItems()
    {
        return numItems;
    }

    void Display()
    {
        Node<T>* current = front;
        while (current)
        {
            cout << current->value << " ";
            current = current->next;
        }
        cout << endl;
    }
};

#endif // !QUEUE_H

