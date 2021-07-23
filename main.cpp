//������������ ����������
#include <iostream>
#include <fstream>
#include "Header.h"


namespace test
{
	void random_full();
	void increase_full();
	void decrease_full();
	void merger(int n);
	int split();
}


int main()
{


	test::random_full();
	test::increase_full();
	test::decrease_full();
	for (int i = 0; i < 1; i++)
	{
		int n = test::split();
		test::merger(n);
	}
}

void test::random_full()
{
	fstream file(PATHH, ios::out);
	full::rand_full(file, 10);
	file.close();
	file.open(PATHH, ios::in);
	print_file(file);
	file.close();
}

void test::decrease_full()
{
	fstream file(PATHH, ios::out);
	full::decrease_full(file, 10);
	file.close();
	file.open(PATHH, ios::in);
	print_file(file);
	file.close();
}

void test::increase_full()
{
	fstream file(PATHH, ios::out);
	full::increase_full(file, 10);
	file.close();
	file.open(PATHH, ios::in);
	print_file(file);
	file.close();
}

int test::split()
{
	cout << "/////////////Splitting///////////////\n";
	fstream file(PATHH, ios::out);
	full::rand_full(file, 10);
	//full::decrease_full(file, 10);
	cout << "file: \n";
	file.close();
	file.open(PATHH, ios::in);
	print_file(file);
	file.close();

	int n = 3;
	auto* work_file = new fstream[n];

	int m = work::splitting(n, work_file, file);

	open_file(work_file, n, 1, 0);
	cout << "work file:\n";
	for (int i = 0; i < n; i++)
	{
		cout << '[' << i << "] ";
		print_file(work_file[i]);
	}
	delete[]work_file;	
	return m;
}

void test::merger(int n)
{
	if (n == 1)
		work::merger(false, 3);
	else
		while(n)
		{
			work::merger(false, 3);
			n--;
			if (!n)
				break;
			work::merger(true, 3);
			n--;
		}
	fstream file("D://work//C++//college//file_sort//log//file[0][0].txt", ios::in);
	cout << '\n';
	print_file(file);
	file.close();
	file.open("D://work//C++//college//file_sort//log//file[1][0].txt", ios::in);
	print_file(file);
	file.close();
}