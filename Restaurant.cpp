#include "main.h"

class imp_res : public Restaurant
{
private:
	class Customer : public customer
	{
	public:
		int timer;
		Customer(string na, int e, customer *p, customer *ne, int t) : customer(na, e, p, ne), timer(t) {}
		~Customer()
		{
			// Unlinking the nodes before
			if (this->next == this)
			{
				this->next = nullptr;
				this->prev = nullptr;
			}
			else
			{
				this->prev->next = this->next;
				this->next->prev = this->prev;

				this->next = nullptr;
				this->prev = nullptr;
			}
		}
	};
	class waitListQueue
	{
	public:
		Customer *front;
		Customer *rear;
		int count;
		int cap;
		waitListQueue()
		{
			cout << "waitList constructor called";
		}
		~waitListQueue() {}
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
			cout << "waitList clear called";
		}
		void insertRear()
		{
		}
		void insertFront() {}
		void removeRear() {}
		void removeFront() {}
		void sortWaitList() {}
	};

public:
	Customer *head;
	Customer *recent;
	waitListQueue *WL;
	int count;
	int cap;
	int timer;

	imp_res() : head(nullptr), recent(nullptr), count(0), cap(MAXSIZE), timer(0){};
	~imp_res()
	{
		// Yet to be implemented
	}

	bool isEmpty()
	{
		return count == 0 && head == nullptr;
	}

	bool isNameInRes(const string &name)
	{
		if (!isEmpty())
			return false;
		Customer *curr = head;
		do
		{
			if (curr->name == name)
			{
				return true;
			}
			// end of loop
			curr = (Customer *)curr->next;
		} while (curr != head);
		return false;
	}

	bool isNameInWL(const string &name)
	{
	}

	bool isNameHere(const string &name)
	{
		return isNameInRes(name) && isNameInWL(name);
	}

	void insert(const string &name, const int &energy) // Need to check cap before using
	{
		Customer *newCustomer = new Customer(name, energy, nullptr, nullptr, timer++);
		if (!isEmpty())
		{
			head = newCustomer;
			head->next = head->prev = head;
		}
		else
		{
			newCustomer->next = head;
			newCustomer->prev = head->prev;
			head->prev->next = newCustomer;
			head->prev = newCustomer;
		}
		recent = newCustomer;
		++count;
	}
	void insertPrev(const string &name, const int &energy) // Need to check cap before using
	{
		Customer *newCustomer = new Customer(name, energy, nullptr, nullptr, timer++);
		if (!isEmpty())
		{
			head = newCustomer;
			head->next = head->prev = head;
		}
		else
		{
			newCustomer->next = recent;
			newCustomer->prev = recent->prev;
			recent->prev->next = newCustomer;
			recent->prev = newCustomer;
		}
		recent = newCustomer;
		++count;
	}
	void insertNext(const string &name, const int &energy) // Need to check cap before using
	{
		Customer *newCustomer = new Customer(name, energy, nullptr, nullptr, timer++);
		if (!isEmpty())
		{
			head = newCustomer;
			head->next = head->prev = head;
		}
		else
		{
			newCustomer->next = recent->next;
			newCustomer->prev = recent;
			recent->next->prev = newCustomer;
			recent->next = newCustomer;
		}
		recent = newCustomer;
		++count;
	}
	void remove()
	{
		if (!isEmpty())
		{
			delete head->prev;
			--count;
		}
	}
	void removePrev()
	{
		if (!isEmpty())
		{
			delete recent->prev;
			--count;
		}
	}
	void removeNext()
	{
		if (!isEmpty())
		{
			delete recent->next;
			--count;
		}
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
				WL->insertRear();
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