#include "Product.h"

//в конструкторе по умолчанию значения не определены
Product::Product()
{
	this->name = "NoName";
	this->id = 0;
	this->count = 0;
}

//конструктор с параметрами
Product::Product(string name, int id, int count)
{
	this->name = name;
	this->id = id;
	this->count = count;
}


//оператор >
bool operator>(const Product& p1, const Product& p2)
{
    return p1.name.compare(p2.name) > 0; //сравнение по названию
}

//вывод в поток
std::ostream& operator<<(std::ostream& os, const Product& product)
{
	os << "Товар #" << product.id << ". " << product.name << ". В наличии: " << product.count << endl;
	return os;
}
