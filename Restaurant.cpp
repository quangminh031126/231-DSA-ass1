#include "main.h"

class imp_res : public Restaurant
{
private:
	customer *recent;
	int count;
	int cap;
	void init() {}
	void removeAll() {}

public:
	imp_res() : recent(nullptr), count(0), cap(MAXSIZE){};

	void moveToName(const string &name) {}
	void moveToEnergy(const int &energy) {}
	int length()
	{
		return count;
	}
	const string &getName() const
	{
		return recent->name;
	}
	const int &getEnergy() const
	{
		return recent->energy;
	}
	void setName(const string &newName)
	{
		this->recent->name = newName;
	}
	void setEnergy(const int &newEnergy)
	{
		this->recent->energy = newEnergy;
	}

	void insert(const string &name, const int &energy)
	{
		recent->next = recent->next->prev = new customer(name, energy, recent, recent->next);
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