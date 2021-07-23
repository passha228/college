#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
//путь до файла
static const char* PATHH = "D://work//C++//college//file_sort//log//start_file.txt";
using namespace std;

//заполнение файла
namespace full
{
    //случайное
	void rand_full(fstream&, int);

	//по возрастанию
	void increase_full(fstream&, int);

	//по убыванию
	void decrease_full(fstream&, int);
}
//рабочие функции
namespace work
{
	//разбиение
	int splitting(int, fstream*, fstream&);

	//слияние
	void merger(bool, int);
}

//открытие файла
void open_file(fstream*, int, bool, int);

void close_file(fstream*, int);

//
string create_file_name(int, int);

void print_file(fstream&);