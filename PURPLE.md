Q:

class customer // node
{
public:
string name;
int energy;
customer *prev;
customer *next;

    public:
    	customer() {}
    	customer(string na, int e, customer *p, customer *ne) : name(na), energy(e), prev(p), next(ne) {}
    	~customer() {}
    	void print()
    	{
    		cout << name << "-" << energy << endl;
    	}
    };

class Customer : public customer
{
public:
int timer;
Customer(string na, int e, customer *p, customer *ne, int t) : customer(na, e, p, ne), timer(t) {}
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
    			front = (Customer *)front->next;
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
    			curr = (Customer *)curr->next;
    		} while (curr != front);

    return false;
    	}

    void sortWaitList() {}
    };

Help me implement sortWaitList(), decreasing energy front to back, energy of customer at front will be highest.
Step 1, it will find the Customer with the highest absolute value of energy, if two customer has the same absolute value of energy, it choose the one with lower timer. (timer will be unique so there will be no conflict here.
Step 2, it will use Shell Sort to sort from the position found in step 1, up to the queue front. Essentially push the Customer with the highest absolute value of energy to the front. Also implement the helper function too.
A:

Sure, I can help you implement the `sortWaitList()` function using Shell Sort. Here’s how you can do it:

```cpp
void sortWaitList() {
    if (isEmpty()) {
        return;
    }

    // Step 1: Find the customer with the highest absolute value of energy
    Customer *maxEnergyCustomer = front;
    Customer *curr = (Customer *)front->next;
    do {
        if (abs(curr->energy) > abs(maxEnergyCustomer->energy) ||
            (abs(curr->energy) == abs(maxEnergyCustomer->energy) && curr->timer < maxEnergyCustomer->timer)) {
            maxEnergyCustomer = curr;
        }
        curr = (Customer *)curr->next;
    } while (curr != front);

    // Step 2: Shell Sort
    for (int gap = count / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < count; i++) {
            Customer *temp = getCustomer(i);
            int j;
            for (j = i; j >= gap && compareCustomers(getCustomer(j - gap), temp); j -= gap) {
                setCustomer(j, getCustomer(j - gap));
            }
            setCustomer(j, temp);
        }
    }

    // Move maxEnergyCustomer to front
    if (maxEnergyCustomer != front) {
        // Detach maxEnergyCustomer from its current position
        maxEnergyCustomer->prev->next = maxEnergyCustomer->next;
        maxEnergyCustomer->next->prev = maxEnergyCustomer->prev;

        // Attach maxEnergyCustomer at front
        maxEnergyCustomer->next = front;
        maxEnergyCustomer->prev = rear;
        front->prev = maxEnergyCustomer;
        rear->next = maxEnergyCustomer;

        front = maxEnergyCustomer;
    }
}

// Helper function to compare two customers based on the problem's requirements
bool compareCustomers(Customer *a, Customer *b) {
    return abs(a->energy) < abs(b->energy) ||
           (abs(a->energy) == abs(b->energy) && a->timer > b->timer);
}

// Helper function to get the customer at a specific index in the circular queue
Customer* getCustomer(int index) {
    Customer *curr = front;
    for (int i = 0; i < index; i++) {
        curr = (Customer *)curr->next;
    }
    return curr;
}

// Helper function to set the customer at a specific index in the circular queue
void setCustomer(int index, Customer *customer) {
    Customer *curr = getCustomer(index);
    curr->name = customer->name;
    curr->energy = customer->energy;
    curr->timer = customer->timer;
}
```

This code first finds the customer with the highest absolute energy value. If there are multiple customers with the same energy value, it selects the one with the lower timer. Then it sorts the customers using Shell Sort. Finally, it moves the customer with the highest energy value to the front of the queue.

Please note that this code assumes that all `timer` values are unique and that `count` represents the number of customers in the queue. Also, this code modifies the queue in place. If you don’t want to modify the original queue, you should create a copy of it before sorting.
