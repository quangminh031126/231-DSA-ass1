#include <iostream>
#include <string>
#include <math.h>
#include <cassert>

using namespace std;
class Customer
{
public:
    string name;
    int energy;
    int timer;
    Customer *next;
    Customer *prev;
    Customer(string na, int e, Customer *p, Customer *ne, int t) : name(na), energy(e), prev(p), next(ne), timer(t) {}
    ~Customer() {}
};
class waitListQueue
{
public:
    Customer *front;
    Customer *rear;
    int count;
    waitListQueue() : front(nullptr), rear(nullptr), count(0) {}

    ~waitListQueue()
    {
        while (!isEmpty())
        {
            removeFront();
        }
    }
    bool isEmpty()
    {
        return count == 0;
    }
    int size()
    {
        return count;
    }
    void clear()
    {
        while (!isEmpty())
        {
            removeFront();
        }
    }
    void insertRear(const string &name, const int &energy, int &timer)
    {
        Customer *newCustomer = new Customer(name, energy, nullptr, nullptr, timer);
        timer++;
        if (isEmpty())
        {
            front = newCustomer;
            front->next = front->prev = front;
        }
        else
        {
            newCustomer->prev = rear;
            newCustomer->next = front;
            rear->next = newCustomer;
            front->prev = newCustomer;
        }
        rear = newCustomer;
        this->count++;
    }
    bool removeFront()
    {
        if (isEmpty())
        {
            return false;
        }

        Customer *temp = front;

        if (front == rear)
        {
            front = rear = nullptr;
        }
        else
        {
            front = front->next;
            front->prev = rear;
            rear->next = front;
        }
        temp->next = nullptr;
        temp->prev = nullptr;
        delete temp;
        count--;

        return true;
    }
    bool isNameInWaitList(const string &name)
    {
        if (isEmpty())
        {
            return false;
        }

        Customer *curr = front;
        do
        {
            if (curr->name == name)
            {
                return true;
            }
            curr = curr->next;
        } while (curr != front);

        return false;
    }
    void swapCustomers(Customer *a, Customer *b)
    {
        if (a == b)
        {
            return;
        }
        Customer *prevA = a->prev;
        Customer *nextA = a->next;
        Customer *prevB = b->prev;
        Customer *nextB = b->next;

        if (nextA == b)
        {
            a->next = nextB;
            b->prev = prevA;

            if (nextB != NULL)
                nextB->prev = a;
            if (prevA != NULL)
                prevA->next = b;

            b->next = a;
            a->prev = b;
        }
        else if (nextB == a)
        {
            swapCustomers(b, a);
        }
        else
        {
            // nodes are not adjacent
            a->next = nextB;
            a->prev = prevB;
            b->next = nextA;
            b->prev = prevA;

            if (nextA != NULL)
                nextA->prev = b;
            if (prevA != NULL)
                prevA->next = b;

            if (nextB != NULL)
                nextB->prev = a;
            if (prevB != NULL)
                prevB->next = a;
        }

        // Update front and rear pointers
        if (front == a)
            front = b;
        else if (front == b)
            front = a;

        if (rear == a)
            rear = b;
        else if (rear == b)
            rear = a;
    }

    bool compareCustomer(Customer *a, Customer *b)
    {
        return abs(a->energy) < abs(b->energy) ||
               (abs(a->energy) == abs(b->energy) && a->timer > b->timer);
    }
    int getPosition(Customer *customer)
    {
        Customer *curr = front;
        int position = 0;
        do
        {
            if (curr == customer)
            {
                return position;
            }
            curr = curr->next;
            position++;
        } while (curr != front);

        return -1; // Return -1 if the customer is not found in the queue
    }
    Customer *getMaxEnergyCustomer()
    {
        if (isEmpty())
        {
            return nullptr;
        }
        Customer *maxEnergyCustomer = front;
        Customer *curr = front->next;
        do
        {
            if (abs(curr->energy) > abs(maxEnergyCustomer->energy) ||
                (abs(curr->energy) == abs(maxEnergyCustomer->energy)) && curr->timer < maxEnergyCustomer->timer)
            {
                maxEnergyCustomer = curr;
            }
            curr = curr->next;
        } while (curr != front);
        return maxEnergyCustomer;
    }
    Customer *advance(Customer *start, int n)
    {
        Customer *curr = start;
        if (n >= 0)
        {
            for (int i = 0; i < n; i++)
            {
                curr = curr->next;
            }
        }
        else
        {
            for (int i = 0; i < -n; i++)
            {
                curr = curr->prev;
            }
        }
        return curr;
    }
    void printQueue()
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
        }
        else
        {
            Customer *curr = front;
            do
            {
                cout << curr->name << " ";
                curr = curr->next;
            } while (curr != front);
            cout << endl;
        }
    }

    void insSort(Customer *start, int n, int incr)
    {
        Customer *iCustomer = advance(start, incr);
        for (int i = incr; i < n; i += incr)
        {
            Customer *jCustomer = iCustomer;
            Customer *jPrevCustomer = advance(jCustomer, -incr);
            while (jCustomer != start && compareCustomer(jPrevCustomer, jCustomer))
            {
                swapCustomers(jPrevCustomer, jCustomer);
                printQueue();
                jCustomer = jPrevCustomer;
                if (jPrevCustomer != start)
                    jPrevCustomer = advance(jCustomer, -incr);
            }
            iCustomer = advance(iCustomer, incr);
        }
    }
    void shellSort(Customer *start, int n)
    {
        for (int i = n / 2; i > 2; i /= 2)
        {
            Customer *sublistStart = start;
            for (int j = 0; j < i; j++)
            {
                insSort(sublistStart, n - j, i);
                sublistStart = sublistStart->next;
            }
        }
        insSort(start, n, 1);
    }
    void sortWaitList_BLUE()
    {
        Customer *maxEnergyCustomer = getMaxEnergyCustomer();
        int position = getPosition(maxEnergyCustomer);
        shellSort(front, position + 1);
    }
};
void test_sortWaitList_BLUE()
{
    waitListQueue queue;
    int timer = 0;

    // Insert customers into the queue
    queue.insertRear("Customer1", 10, timer);
    queue.insertRear("Customer2", 20, timer);
    queue.insertRear("Customer3", 30, timer);
    queue.insertRear("Customer4", 40, timer);

    // Sort the waitlist
    queue.sortWaitList_BLUE();

    // Check if the customers are sorted correctly
    assert(queue.front->name == "Customer4");
    assert(queue.front->next->name == "Customer3");
    assert(queue.front->next->next->name == "Customer2");
    assert(queue.rear->name == "Customer1");

    cout << "sortWaitList_BLUE() passed all tests!" << endl;
}
int main()
{
    test_sortWaitList_BLUE();
    return 0;
}