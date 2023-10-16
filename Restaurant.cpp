#include "main.h"

class imp_res : public Restaurant
{
private:
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

public:
	Customer *recent;
	waitListQueue *WL;
	int count;
	int timer;

	imp_res() : recent(nullptr), count(0), timer(0){};
	~imp_res()
	{
		// Yet to be implemented
		while (!isEmpty())
		{
			removeHere();
		}
		delete WL;
	}

	bool isEmpty()
	{
		return count == 0;
	}

	bool isNameInRes(const string &name)
	{
		if (isEmpty())
			return false;
		Customer *curr = recent;
		Customer *begin = recent;
		do
		{
			if (curr->name == name)
			{
				return true;
			}
			// end of loop
			curr = (Customer *)curr->next;
		} while (curr != begin);
		return false;
	}

	bool isNameInWL(const string &name)
	{
		return WL->isNameInWaitList(name);
	}

	bool isNameHere(const string &name)
	{
		return isNameInRes(name) || isNameInWL(name);
	}

	void insertPrev(const string &name, const int &energy) // Need to check count before using
	{
		Customer *newCustomer = new Customer(name, energy, nullptr, nullptr, timer);
		timer++;
		if (isEmpty())
		{
			recent = newCustomer;
			recent->next = recent->prev = recent;
		}
		else
		{
			newCustomer->next = recent;
			newCustomer->prev = recent->prev;
			recent->prev->next = newCustomer;
			recent->prev = newCustomer;
			recent = newCustomer;
		}
		++count;
	}
	void insertNext(const string &name, const int &energy) // Need to check count before using
	{
		Customer *newCustomer = new Customer(name, energy, nullptr, nullptr, timer);
		timer++;
		if (isEmpty())
		{
			recent = newCustomer;
			recent->next = recent->prev = recent;
		}
		else
		{
			newCustomer->next = recent->next;
			newCustomer->prev = recent;
			recent->next->prev = newCustomer;
			recent->next = newCustomer;
			recent = newCustomer;
		}
		++count;
	}
	bool removeHere()
	{
		if (isEmpty())
		{
			return false;
		}
		Customer *temp = recent;
		if (recent == temp)
		{
			recent = nullptr;
		}
		else
		{
			recent->next->prev = recent->prev;
			recent->prev->next = recent->next;
			if (temp->energy > 0)
			{
				recent = (Customer *)temp->next;
			}
			else
			{
				recent = (Customer *)temp->prev;
			}
		}
		temp->next = nullptr;
		temp->prev = nullptr;
		delete temp;
		count--;
		return true;
	}
	bool removePrev()
	{
		if (isEmpty())
		{
			return false;
		}
		Customer *temp = (Customer *)recent->prev;
		if (recent == temp)
		{
			recent = nullptr;
		}
		else
		{
			temp->prev->next = recent;
			recent->prev = temp->prev;
			if (temp->energy > 0)
			{
				recent = (Customer *)temp->next;
			}
			else
			{
				recent = (Customer *)temp->prev;
			}
		}
		temp->next = nullptr;
		temp->prev = nullptr;
		delete temp;
		count--;
		return true;
	}
	bool removeNext()
	{
		if (isEmpty())
		{
			return false;
		}
		Customer *temp = (Customer *)recent->next;
		if (recent == temp)
		{
			recent = nullptr;
		}
		else
		{
			temp->next->prev = recent;
			recent->next = temp->next;
			if (temp->energy > 0)
			{
				recent = (Customer *)temp->next;
			}
			else
			{
				recent = (Customer *)temp->prev;
			}
		}
		temp->next = nullptr;
		temp->prev = nullptr;
		delete temp;
		count--;
		return true;
	}
	void RED(string name, int energy)
	{
		if (energy == 0 || isNameHere(name))
		{
			return;
		}
		int MAXSIZE_2 = MAXSIZE / 2;
		if (count < 0 || count > MAXSIZE || WL->count < 0 || WL->count > MAXSIZE)
		{
			cout << "out of range"
				 << "\n";
			return;
		}
		if (0 <= count && count < MAXSIZE_2)
		{
			if (energy >= recent->energy)
			{
				insertNext(name, energy);
			}
			else
			{
				insertPrev(name, energy);
			}
		}
		else if (MAXSIZE_2 <= count && count < MAXSIZE)
		{
			int max_diff = 0;
			int curr_diff = 0;
			Customer *begin = recent;
			Customer *curr = recent;
			do
			{
				// do this during each loop
				curr_diff = energy - curr->energy;
				if (abs(curr_diff) > abs(max_diff))
				{
					recent = curr;
					max_diff = curr_diff;
				}
				// end of each loop
				curr = (Customer *)curr->next;
			} while (curr != begin);

			if (curr_diff < 0)
			{
				insertPrev(name, energy);
			}
			else
			{
				insertNext(name, energy);
			}
		}
		else // count == MAXSIZE
		{
			if (WL->count < MAXSIZE)
			{
				WL->insertRear(name, energy, timer);
			}
			else
			{
				return;
			}
		}
	}
	void BLUE(int num)
	{
		cout << "blue " << num << endl;
		// BLUE remove num customer
		if (num <= 0)
			return;
		num = (num >= count) ? count : num;
		for (int i = 0; i < num; i++)
		{
			int min_timer = recent->timer;
			Customer *begin = recent;
			Customer *curr = (Customer *)recent->next;
			while (curr != begin)
			{
				if (min_timer > curr->timer)
				{
					min_timer = curr->timer;
				}
			}

			// BLUE add num customer from waitList
		}
	}
	void PURPLE()
	{
		cout << "purple" << endl;
	}
	void REVERSAL()
	{
		cout << "reversal" << endl;
	}
	void UNLIMITED_VOID()
	{
		cout << "unlimited_void" << endl;
	}
	void DOMAIN_EXPANSION()
	{
		cout << "domain_expansion" << endl;
	}
	void LIGHT(int num)
	{
		cout << "light " << num << endl;
	}
};