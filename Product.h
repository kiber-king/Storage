#pragma once
#include <iostream>
#include <string>

using namespace std;

//�����, �������������� �����
class Product
{
private:
	string name; //��������
	int id; //�������
	int count; //����������
public:
	Product(); //����������� �� ���������
	Product(string name, int id, int count); //����������� � �����������

	//������ ������� � �������� �����
	string get_name() { return name; }
	void set_name(string name) { this->name = name; }
	int get_id() { return id; }
	void set_id(int id) { this->id = id; }
	int get_count() { return count; }
	void set_count(int count) { this->count = count; }

	//��������� ��������� ��������� > (�� ��������) ��� ������� ���������� ����� ������������� �������
	friend bool operator> (const Product& p1, const Product& p2);
	//���������� ������ � ����� ����� ������������� �������
	friend std::ostream& operator <<(std::ostream& os, const Product& product);

};

