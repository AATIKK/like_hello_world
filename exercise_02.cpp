#include<iostream>
#include<cstdlib>
using namespace std;

class list {
public:
    list *head;  // pointer to start of list
    list *tail;  // pointer to end of list
    list *next;  // pointer to next node
    int num;     // value to be stored in node

    list() : head(nullptr), tail(nullptr), next(nullptr), num(0) {}

    virtual void store(int i) = 0;
    virtual int retrieve() = 0;
};

// Create a queue-type list.
class queue : public list {
public:
    void store(int i);
    int retrieve();
};

void queue::store(int i) {
    list *item = new queue;
    if (!item) {
        cout << "Allocation error.\n";
        exit(1);
    }
    item->num = i;

    // Put on end of list
    if (tail) {
        tail->next = item;
    }
    tail = item;
    if (!head) {
        head = item;
    }
}

int queue::retrieve() {
    if (!head) {
        cout << "List empty.\n";
        return 0;
    }

    int i = head->num;
    list *p = head;
    head = head->next;
    delete p;
    if (!head) {
        tail = nullptr;
    }
    return i;
}

// Create a stack-type list.
class stack : public list {
public:
    void store(int i);
    int retrieve();
};

void stack::store(int i) {
    list *item = new stack;
    if (!item) {
        cout << "Allocation error.\n";
        exit(1);
    }
    item->num = i;

    // Put on front of list for stack-like operation
    item->next = head;
    head = item;
    if (!tail) {
        tail = head;
    }
}

int stack::retrieve() {
    if (!head) {
        cout << "List empty.\n";
        return 0;
    }

    int i = head->num;
    list *p = head;
    head = head->next;
    delete p;
    if (!head) {
        tail = nullptr;
    }
    return i;
}

// Create a sorted list.
class sorted : public list {
public:
    void store(int i);
    int retrieve();
};

void sorted::store(int i) {
    list *item = new sorted;
    if (!item) {
        cout << "Allocation error.\n";
        exit(1);
    }
    item->num = i;

    // Find where to put new item
    list *p = head;
    list *p2 = nullptr;
    while (p) {
        if (p->num > i) {
            item->next = p;
            if (p2) {
                p2->next = item;  // Not 1st element
            } else {
                head = item;  // New 1st element
            }
            break;
        }
        p2 = p;
        p = p->next;
    }
    if (!p) {  // Goes at the end
        if (tail) {
            tail->next = item;
        }
        tail = item;
        item->next = nullptr;
    }
    if (!head) {  // Empty list
        head = item;
    }
}

int sorted::retrieve() {
    if (!head) {
        cout << "List empty.\n";
        return 0;
    }

    int i = head->num;
    list *p = head;
    head = head->next;
    delete p;
    if (!head) {
        tail = nullptr;
    }
    return i;
}

// Create a list of pointers to list objects
int main() {
    list *p;

    // Demonstrate queue
    queue q_ob;
    p = &q_ob;
    p->store(1);
    p->store(2);
    p->store(3);
    cout << "Queue: ";
    cout << p->retrieve() << " ";
    cout << p->retrieve() << " ";
    cout << p->retrieve() << endl;

    // Demonstrate stack
    stack s_ob;
    p = &s_ob;
    p->store(1);
    p->store(2);
    p->store(3);
    cout << "Stack: ";
    cout << p->retrieve() << " ";
    cout << p->retrieve() << " ";
    cout << p->retrieve() << endl;

    // Demonstrate sorted list
    sorted sorted_ob;
    p = &sorted_ob;
    p->store(4);
    p->store(1);
    p->store(3);
    p->store(9);
    p->store(5);
    cout << "Sorted: ";
    cout << p->retrieve() << " ";
    cout << p->retrieve() << " ";
    cout << p->retrieve() << " ";
    cout << p->retrieve() << " ";
    cout << p->retrieve() << endl;

    return 0;
}

