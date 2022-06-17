#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Windows.h"
#include "Product.h"

//ввести данные о продукте (при создании нового или редактировании существующего)
void input_product(Product* p)
{
    string name;
    int id, count;
    cout << "Введите артикул товара: ";
    cin >> id;
    cin.ignore();
    cout << "Введите название: ";
    getline(cin, name);
    cout << "Введите количество на складе: ";
    cin >> count;
    while (count < 0)
    {
        cout << "\nКоличество не может быть отрицательным! Введите корректное значение: ";
        cin >> count;
    }
    //задаем полям объекта введенные значения
    p->set_name(name);
    p->set_id(id);
    p->set_count(count);
}

//вывод списка товаров
void print_products(vector<Product> products)
{
    for (int i = 0; i < products.size(); i++)
        cout << i << ". " << products[i] << endl;
    cout << endl;
}

//сортировка списка товаров по названию
void sort_products(vector<Product>& products)
{
    //пузырьковая сортировка
    for (int i = 0; i < products.size(); i++)
    {
        for (int j = 0; j < products.size() - i - 1; j++)
        {
            if (products[j] > products[j + 1])
            {
                Product t = products[j];
                products[j] = products[j + 1];
                products[j + 1] = t;
            }
        }
    }
}

//запись в файл данных о продуктах
void write_to_file(vector<Product> products, string filename)
{
    ofstream out(filename); //файловый поток для вывода
    for (int i = 0; i < products.size(); i++)
    {
        //запись данных в файл через ;
        out << products[i].get_name() << ";" << products[i].get_id() << ";" << products[i].get_count() << endl;
    }
    out.close(); //сохраняем файл
}

//считать данные из файла
bool read_from_file(vector<Product>& products, string filename)
{
    ifstream in(filename); //файловый поток для чтения
    if (in) //если открылся
    {
        products.clear(); //очищаем список
        string str, token, name;
        int id, count;
        while (getline(in, str)) //пока не считаем все строки
        {
            //getline(in, buf);
            if (str.size() > 0) //если не пустая строка
            {
                stringstream sstr(str);
                getline(sstr, token, ';'); // читаем до разд ;
                name = token;
                getline(sstr, token, ';');
                id = stoi(token);
                getline(sstr, token, ';');
                count = stoi(token);
                products.push_back(Product(name, id, count)); //добавляем считанный продукт в список
            }
        }
        return true;
    }
    else
        return false;
}

int main()
{
    //поддержка ввода-вывода кириллицы
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const string filename1 = "storage.txt";

    vector<Product> products; //список продуктов

    //начальное заполнение списка из файла
    if (read_from_file(products, filename1))
    {
        cout << "Начальное содержимое списка\n";
        print_products(products);
    }
    else
    {
        cout << "Исходный файл " << filename1 << " не был считан! Возможно, его нет на диске\n";
    }
 
    int cmd = -1;
    while (cmd != 0) //пока не выбран выход
    {
        cout << "\n1 - добавить товар на склад\n";
        cout << "2 - список товаров на складе\n";
        cout << "3 - редактировать товар по номеру в списке\n";
        cout << "4 - удалить товар из списка по номеру\n";
        cout << "5 - сортировка товаров по названию\n";
        cout << "0 - выход\n";
        cout << "\nВведите номер команды: ";
        cin >> cmd;
        cout << endl;
        switch (cmd)
        {
            case 1: //добавить новый товар
            {
                read_from_file(products, filename1); //считываем список
                Product p; //создаем новый товар
                input_product(&p); //вводим его данные
                products.push_back(p); //добавляем в список
                write_to_file(products, filename1); //сохраняем
                break;
            }
            case 2: //вывести список товаров
            {
                read_from_file(products, filename1); //считываем список
                cout << "\nТовары на складе:\n";
                print_products(products);
                break;
            }
            case 3: //редактировать по номеру в списке
            {
                read_from_file(products, filename1); //считываем список
                int idx;
                cout << "Введите номер товара в списке: ";
                cin >> idx;
                if (idx >= 0 && idx < products.size()) //корректность индекса
                {
                    cout << "\nРедактирование записи:\n";
                    cout << products[idx] << endl << endl;
                    input_product(&products[idx]);
                    cout << "\nЗапись отредактирована\n";
                    write_to_file(products, filename1); //сохраняем
                }
                else
                {
                    cout << "Некорректный индекс!\n";
                }
                break;
            }
            case 4: //удаление по номеру
            {
                read_from_file(products, filename1); //считываем список
                int idx;
                cout << "Введите номер товара в списке: ";
                cin >> idx;
                if (idx >= 0 && idx < products.size()) //корректность индекса
                {
                    products.erase(products.begin() + idx); //удаляем запись
                    cout << "\nЗапись удалена!\n";
                    write_to_file(products, filename1); //сохраняем
                }
                else
                {
                    cout << "Некорректный индекс!\n";
                }
                break;
            }
            case 5: //сортировка
            {
                read_from_file(products, filename1); //считываем список
                sort_products(products);
                cout << "Список товаров отсортирован\n";
                write_to_file(products, filename1); //сохраняем
                break;
            }
            case 0:
            {
                break;
            }
            default:
            {
                cout << "Неверная команда!\n";
                break;
            }
        }
    }
}