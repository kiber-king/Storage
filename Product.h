#pragma once
#include <iostream>
#include <string>

using namespace std;

//класс, представляющий товар
class Product
{
private:
	string name; //название
	int id; //артикул
	int count; //количество
public:
	Product(); //конструктор по умолчанию
	Product(string name, int id, int count); //конструктор с параметрами

	//методы доступа к закрытым полям
	string get_name() { return name; }
	void set_name(string name) { this->name = name; }
	int get_id() { return id; }
	void set_id(int id) { this->id = id; }
	int get_count() { return count; }
	void set_count(int count) { this->count = count; }

	//перегузка оператора сравнения > (по названию) для будущей сортировки через дружественную функцию
	friend bool operator> (const Product& p1, const Product& p2);
	//перегрузка вывода в поток через дружественную функцию
	friend std::ostream& operator <<(std::ostream& os, const Product& product);

};

