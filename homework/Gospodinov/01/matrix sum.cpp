#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#define MAX 100 // максимальный размер слова
#define MAX_S 100 // максимальный размер строки в файле 
#define MAX_WORD_COUNT 100 // максимальное к-во слов введных с кл-ы

// функция проверяет является ли символ буквой русского алфавита
int is_letter(char s)
{
	if (s >= 'а' && s <= 'я' || s >= 'А' && s <= 'Я')// стоит ли символ s между буквами а и я. или A и Я.
		return 1; // если это сивол - буква - возвращаем 1
	else
		return 0;
}
// str- входная строка, begin - символ с коготорого начинается проверка
// str_size размер. word- это слово, которое мы ищем в строке str
// word_size - его размер
int match(char* str, int begin, int str_size, char* word, int word_size)
{
	if (begin > 0 && (is_letter(str[begin - 1]) || str[begin - 1] == '-')) // если предыдущий символ строки является буквой, значит, мы нашли другое слово (пример: ищем "ты" в строке "черты")
		return 0;
	else if (str_size - begin < word_size)// если входная строка меньше слова, то не можем найти, и вернем 0
		return 0;
	else
	{
		for (int i = 0; i < word_size; i++)// проверяем в цикле каждую букву 
		{
			if (str[i + begin] != word[i])// проверка того, равен ли текущий символ слова текущему символу строки  
				return 0;// если они не равны, мы не можем найти такое слово и возвращаем 0
		}
		if (word_size + begin < str_size && (is_letter(str[word_size + begin]) || str[word_size + begin] == '-')) // если все символы слова совпадают с символами строки, но после этих символов в строке идут буквы, значит мы нашли часть другого слова, а не самостоятельное слово (пример: ищем "ты" в строке "черты")
			return 0;
		return 1;// если все символы совпадают возвращаем 1
	}
}

// принимает new-str(получившаяся строка, из которой мы удалили слова).
// str-начальная строка. str_size - размер строки. word-слово которое удаляем
// word_size - размер удаляемого слова
void delete_words(char* new_str, char* str, int str_size, char* word, int word_size)
{
	int j = 0;
	for (int i = 0; i < str_size; i++)// цикл посимвольной обработки входной строки
	{
		if (!is_letter(str[j])) //если символ не буква, то :
		{
			new_str[j] = str[i]; // мы его копируем в новую строку 
			j++;// сдвигаем размер(индекс новой строки массива)
			continue;// цикл начинается с 37 строки 
		}
		else // если символ является буквой 
		{
			if (match(str, i, str_size, word, word_size))// вызывается функция match. ищем слово word в строке str, начиная с символа str[i].
			{// если нашли 
				i += word_size - 1;// то сдвигаем  индекс, чтобы не копировать слово 
			}
			else
			{
				new_str[j] = str[i];// иначе просто копируем текущий символ
				j++; // переходи мк следующему символу 
			}
		}
	}
	new_str[j] = '\0'; // в конце добавляем символ конца строки 
}

int main(void)
{
	SetConsoleCP(1251); // вводить
	SetConsoleOutputCP(1251); // выводить 

	char word[MAX][MAX_WORD_COUNT];// массив слов, которые нужно удалить 
	int size; // размер массива слов
	printf("/* для окончания ввода слов нажмите <enter> */\n");
	for (size = 0; size < MAX_WORD_COUNT; size++)// считываем слова сначала 
	{
		printf("Введите слово: ");
		gets_s(word[size]);// считываение построчено слов 
		if (strlen(word[size]) == 0)// если мы считали пустую строку, то завершаем считывание 
			break; // оператор остановки цикла 
	}
	printf("Введено %d слов\n", size); // выводит сколько всего слов считано

	FILE* input = fopen("input.txt", "r");// открываем файл input.txt на чтение
	FILE* output = fopen("output.txt", "w");// открываем файл output.txt на запись
	char str[MAX_S]; // буфер для строки 
	while (fgets(str, MAX_S, input) != NULL) // считываем строку из файла  и проверяем не пустая ли она. если она пустая - программа end. а если не пустая то: 
	{
		for (int i = 0; i < size; i++) //в цикле удаляем слова из считанной строки 
			delete_words(str, str, strlen(str), word[i], strlen(word[i]));
		fprintf(output, "%s", str);// выводим эту строку в новый файл 
	}
	fclose(input); // закрываем файлы 
	fclose(output);

	return 0;
}