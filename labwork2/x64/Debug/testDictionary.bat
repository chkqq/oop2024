@echo off
chcp 1251

echo ���� 1: ������������ �������
dictionary.exe dictionary.txt < input1.txt

echo ���� 2: ���������� ������ ����� � �������
dictionary.exe dictionary.txt < input2.txt

echo ���� 3: ���������� ��������� ��� ���������� ���������
dictionary.exe dictionary.txt < input3.txt

echo ���� 4: ���� �� �������� � ��������� �����
dictionary.exe dictionary.txt < input4.txt

echo ���� 5: �������������� ���� �������
dictionary.exe non_existing_dictionary.txt < input5.txt
