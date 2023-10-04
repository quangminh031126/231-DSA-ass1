#include "main.h"

class imp_res : public Restaurant
{
private:
	class cirCustomer : public customer
	{
	public:
		cirCustomer(string na, int e, cirCustomer *p, cirCustomer *ne) : customer(na, e, p, ne) {}
		cirCustomer(cirCustomer *p = NULL, cirCustomer *ne = NULL)
		{
			this->prev = p;
			this->next = ne;
		}
		~cirCustomer()
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

public:
	cirCustomer *recent;
	int count;
	int cap;

	imp_res() : recent(nullptr), count(0), cap(MAXSIZE){};
	
	void insert(const string& name, const int& energy){
		
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