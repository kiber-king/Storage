#include "Product.h"

//� ������������ �� ��������� �������� �� ����������
Product::Product()
{
	this->name = "NoName";
	this->id = 0;
	this->count = 0;
}

//����������� � �����������
Product::Product(string name, int id, int count)
{
	this->name = name;
	this->id = id;
	this->count = count;
}


//�������� >
bool operator>(const Product& p1, const Product& p2)
{
    return p1.name.compare(p2.name) > 0; //��������� �� ��������
}

//����� � �����
std::ostream& operator<<(std::ostream& os, const Product& product)
{
	os << "����� #" << product.id << ". " << product.name << ". � �������: " << product.count << endl;
	return os;
}
