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
		int eDiff(customer *c)
		{
			return this->energy - c->energy;
		}
	};

public:
	Customer *head;
	Customer *recent;
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
		cout << name << " " << energy << endl;
		customer *cus = new customer(name, energy, nullptr, nullptr);
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