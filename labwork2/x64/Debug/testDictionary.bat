@echo off
chcp 1251

echo Тест 1: Существующий словарь
dictionary.exe dictionary.txt < input1.txt

echo Тест 2: Добавление нового слова в словарь
dictionary.exe dictionary.txt < input2.txt

echo Тест 3: Завершение программы без сохранения изменений
dictionary.exe dictionary.txt < input3.txt

echo Тест 4: Тест на строчные и прописные буквы
dictionary.exe dictionary.txt < input4.txt

echo Тест 5: Несуществующий файл словаря
dictionary.exe non_existing_dictionary.txt < input5.txt
