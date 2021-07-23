#pragma once
#include <iostream>
using namespace std;
//сломалась кодировка((

// ��������� ��� �������������� � ������ � �������� ����� i, ��� ��������
// �������� � arr[]. n - ������ ������
void heapify(int * mas, int n, int i)
{
    int largest = i;
    // �������������� ���������� ������� ��� ������
    int l = 2 * i + 1; // ����� = 2*i + 1
    int r = 2 * i + 2; // ������ = 2*i + 2

    // ���� ����� �������� ������� ������ �����
    if (l < n && mas[l] > mas[largest])
        largest = l;

    // ���� ������ �������� ������� ������ ��� ����� ������� ������� �� ������ ������
    if (r < n && mas[r] > mas[largest])
        largest = r;

    // ���� ����� ������� ������� �� ������
    if (largest != i)
    {
        swap(mas[i], mas[largest]);

    // ���������� ����������� � ���� ���������� ���������
        heapify(mas, n, largest);
    }
}


void heap_sort(int* arr, int n)
{
    // ������ ������
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    //���������� ������ �������� �������� �� ������ � ������������ ������������ ������
    for (int i = n - 1; i >= 0; i--)
    {
        swap(arr[0], arr[i]);

        heapify(arr, i, 0);
    }
}
