#include "Header.h"
#include "Heap_sort.h"

//����������� �������� ������
void close_file(fstream* file, int n)
{
	for (int i = 0; i < n; i++)
	{
		file[i].close();
		file[i].flush();
	}
}

//����������� ���������� ���������� �����
void full::rand_full(fstream& file, int count)
{
	try
	{
		if (!file.is_open())
			throw 401;
	}
	catch (int a)
	{
		cerr << "Error 401. Bad file. ";
	}


	srand(time(0));

	for (int i = 0; i < count; i++)
	{
		int a = rand() % 100;
		file << a << ' ';
	}
	file.close();
}

//����������� ���������� �� �����������
void full::increase_full(fstream& file, int n)
{
	int* mas = new int[n];
	for (int i = 0; i < n; i++)
	{
		mas[i] = rand() % 100;
	}
	heap_sort(mas, n);

	file.close();
	file.open(PATHH,ios_base::out);

	for (int i = 0; i < n; i++)
		file << mas[i] << ' ';
}

//����������� ���������� �� ��������
void full::decrease_full(fstream& file, int n)
{
	int* mas = new int[n];
	for (int i = 0; i < n; i++)
	{
		mas[i] = rand() % 100;
	}
	heap_sort(mas, n);

	file.close();
	file.open(PATHH, ios_base::out);

	for (int i = n-1; i > -1; i--)
		file << mas[i] << ' ';
}

//����������� ���������	
int work::splitting(int n,fstream* work_file, fstream& file)
{
	file.open(PATHH, ios::in);
	open_file(work_file, n, 0, 0);
	//int1 - ������ �����, int2 - ������ �����
	int int1, int2;
	file >> int1;
	file >> int2;
	int i = 0;
	int count_spit = 1;

	while (!file.eof())
	{
		//���� ��� ����� �� ������� ������ �������� ������ �� ������������ � ������
		//���� ������ ������������� �� ��������
		if (int1 <= int2)
		{
			//�� ���� ��� ����
				//���������� � ���� ������ ����� � ������������ ��
			while (int1 <= int2)
			{
				int a = 0;
				file >> a;
				if (file.eof() || !file.is_open())
					break;
				work_file[i] << int1 << ' ';
				int1 = int2;
				int2 = a;
				//file.seekp(1, ios::cur);
				
			}
			//����� ����� ���������� �� ���������� ����� � ����
			work_file[i] << int1 << ' ';
			i++;
			int1 = int2;
			file >> int2;
			//���� ��� ���� �� ��������� ���� ����� �� ��������� ������ � �������� ������
			if (file.eof())
			{
				i != n ? work_file[i] << int2 << ' ' : work_file[0] << int2 << ' ';
				//break;
			}
		}
			//���� ��� �������������� �� �������� �� 
		else
		{
			//���������� � 
			work_file[i] << int1 << ' ';
			i++;
			int1 = int2;
			//� ���� ��� ���� �� ��������� �����.... (�� �� ����� ��� � ������)
			file >> int2;
			if (file.eof())
			{
				i != n ? work_file[i] << int2 << ' ' : work_file[0] << int2 << ' ';
				//break;
			}
		}
		if (i == n)
		{
			i = 0;
			count_spit++;
		}

	}
	close_file(work_file, n);
	file.close();
	return count_spit;
}




/*/////////////////////////////////////////////////////////////////
					half
					0 - ������ ����� �� ������ ������ �� ������
					1 - ������ ����� �� ������ ������ �� ������
*/////////////////////////////////////////////////////////////////
void work::merger(bool half, int n)
{
	fstream* file[2];
	file[0] = new fstream[n];
	file[1] = new fstream[n];
	vector<int> mas;
	//�������� � �������� ������ � ����������� �� ���� ����� ����� ����
	if (!half)
	{
		if (file[0][0].is_open())
			close_file(file[0], n);
		if (file[1][0].is_open())
			close_file(file[1], n);
		open_file(file[0], n, 1, 0);
		open_file(file[1], n, 0, 1);


		for (int i = 0; i < n; i++)
		{
			int vec;
			file[0][i] >> vec;
			mas.push_back(vec);
		}
	}
	else
	{
		if (file[0][0].is_open())
			close_file(file[0], n);
		if (file[1][0].is_open())
			close_file(file[1], n);
		open_file(file[0], n, 0, 0);
		open_file(file[1], n, 1, 1);


		for (int i = 0; i < n; i++)
		{
			int vec;
			file[1][i] >> vec;
			mas.push_back(vec);
		}
	}


	vector<bool> check_file(n);
	bool main_check = 0;
	int iter_file = 0;

	while (!main_check)
	{
		// 1 - ��� ����� �����������
		// 0 - ���� ���� ���� �� �������������

		//�������� 
		if (iter_file == n)
			iter_file = 0;
		vector<bool> check_end(n);
		for (int i = 0; i < n; i++)
			check_end[i] = 0;


		bool inside_check = 0;


		while (!inside_check)
		{
			if (!half)
				for (int i = 0; i < n; i++)
					check_file[i] = file[0][i].eof();
			else
				for (int i = 0; i < n; i++)
					check_file[i] = file[1][i].eof();


			//���������� ��������
			main_check = 1;
			inside_check = 1;


			int min = 100;
			int min_i = 0;
			//���������� �������� � �������
			for (int i = 0; i < n; i++)
			{
				if (!check_file[i])
					if (!check_end[i])
						if (mas[i] < min)
						{
							min = mas[i];
							min_i = i;
						}
			}

			//������ � ���� � ����� ��������� ���������� �� ���� � ����������� �� ������������������ �������������� �� ��������
			if (!half)
			{
				file[1][iter_file] << mas[min_i] << ' ';
				mas[min_i] = mas[min_i];
				file[0][min_i] >> mas[min_i];
				if (file[0][min_i].eof() || !file[0][min_i].is_open())
				{
					file[0][min_i].close();
					check_file[min_i] = 1;
					check_end[min_i] = 1;
				}
				else
				{
					if (mas[min_i] < min)
						check_end[min_i] = 1;
				}
			}
			else
			{
				file[0][iter_file] << mas[min_i] << ' ';
				mas[min_i] = mas[min_i];
				file[1][min_i] >> mas[min_i];
				if (file[1][min_i].eof() || !file[1][min_i].is_open())
				{
					file[1][min_i].close();
					check_file[min_i] = 1;
					check_end[min_i] = 1;
				}
				else
				{
					if (mas[min_i] < min)
						check_end[min_i] = 1;
				}
			}
			//����� ��������� ��� ����� �� ������� ��������� �������������������
			//���� ��� ��� ����������� �� ��������� �� ���� ������ �� ���������� � �� ������� �� ����� �.� inside_check == 1
			for (int i = 0; i < n; i++)
			{
				if (!check_end[i])
					inside_check = 0;
			}


			for (int i = 0; i < n; i++)
				if (!check_file[i])
					main_check = 0;

			if (main_check)
				inside_check = 1;

			int a = 0;
			for (int i = 0; i < n; i++)
				if (!check_end[i] == check_file[i])
					a++;
			if (a == n)
				inside_check = 1;
		}

		//������ � ��������� ����
		cout << "Iter " << iter_file;
		iter_file++;
		

	}
	
	delete[]file[0];
	delete[]file[1];
}



/*////////////////////////////////////////////////////////////
					open mod
					0 - �� ������
					1 - �� ������
*////////////////////////////////////////////////////////////
void open_file(fstream* file, int n, bool open_mod, int j)
{
	//������ ��������� ����� � ����������� �� ���� ��� ��������� �� ���� �������
	for (int i = 0; i < n; i++)
	{
		if (!open_mod)
			file[i].open(create_file_name(i, j), ios::out);
		if (open_mod)
			file[i].open(create_file_name(i, j), ios::in);
		//���� ���� �� ����������� ���������� ���������� 401
		try
		{
			if (!file[i].is_open())
				throw 401;
		}
		catch (int a)
		{
			cerr << "Error 401. Bad file. ";
		}
	}
}



//������� ��� ��� �����
//�� ����������, � �������
//����� � ���������� ����� ��� ��� �����
string create_file_name(int count, int j)
{
	string str("D://work//C++//college//file_sort//log//[");
	str += to_string(j);
	str += "][";
	str += to_string(count);
	str += "].txt";
	return str;
}


void print_file(fstream& file)
{		
	int some;
	file >> some;
	while(!file.eof())
	{
		cout << some << ' ';
		file >> some;
	}
	cout << "\n\n";
}