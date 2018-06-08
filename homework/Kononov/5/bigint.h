// Kononov Sergey BD-11

class BigInt{
	private:
		char * _data;
		bool _minus;
		int _size;

		static int max(int a, int b){
			if (a > b)
				return a;
			else
				return b;
		};

		static int min(int a, int b){
			if (a < b)
				return a;
			else
				return b;
		};

		BigInt shift(int val) const{
			// Добавление k нулей в "конец" числа
			char * data = new char[val + _size];
			for (int i = 0; i < val; i++)
				data[i] = 0;

			std::copy(_data, _data + _size, data + val);

			return BigInt(data, val + _size, _minus);
		};

		BigInt reverse(){
			// Перевернуть число
			for (int i = 0; i < _size / 2; i++)
				std::swap(_data[i], _data[_size - i - 1]);
		};

		BigInt digit_mul(int n) const{
			// Уножение числа на n
			int size = _size + 1;
			char * mul_data = new char[size];

			for (int i = 0; i < size; i++)
				mul_data[i] = 0;

			div_t d_res;
			int prev = 0;
			for (int j = 0, tmp =0; j < _size; j++){
				tmp = _data[j] * n + prev;
				if (tmp > 9){
					d_res = div(tmp, 10);
					mul_data[j] = d_res.rem;
					prev = d_res.quot;
				}
				else{
					mul_data[j] = tmp;
					prev = 0;
				};
			};

			if (prev)
				mul_data[size - 1] = prev;
			else
				size--;

			return BigInt(mul_data, size, 0);
		};

	public:

	BigInt():_size(1),_minus(0), _data(new char[1]){
		_data[0] = 0;
	};

	BigInt(int64_t integer):_size(1), _minus(false){
		// Конструктор из длинного числа
		lldiv_t d_res;
		int64_t tmp_int;

		if (integer < 0){
			_minus = true;
			integer *= -1;
		};
		// Извлечение знака числа

		tmp_int = integer;
		for (tmp_int = integer; tmp_int > 9; tmp_int /= 10)
			_size++;
		// Вычисление размера числа

		_data = new char[_size];
		// Выделение под число памяти

		tmp_int = integer;
		for (int j = 0; tmp_int > 0; j++){
			d_res = lldiv(tmp_int, 10);
			_data[j] = d_res.rem;
			tmp_int = d_res.quot;
		};

		if (integer == 0) _data[0] = 0;
		// Заполнение массива цифрами числа
	};

	BigInt operator-(){
		// Унарный минус
		return BigInt(_data, _size, !_minus);
	};

	BigInt(BigInt && copied):_size(copied._size), _minus(copied._minus), _data(copied._data){
		// Конструктор перемещения
		copied._data = nullptr;
		copied._size = 0;
	};

	BigInt(const BigInt & copied):_size(copied._size), _minus(copied._minus){
		// Конструктор копирования
		_data = new char[_size];
		std::copy(copied._data, copied._data + copied._size, _data);
	};
	
	//BigInt(char * && data, int len, bool minus):_minus(minus), _size(len), _data(data){};
	// Конструктор копирования для r-value

	BigInt(char * data, int length, bool minus):_minus(minus), _size(length){
		// Конструктор из данных (массив, длинна, минус)			
		_data = new char[_size];
		std::copy(data, data + _size, _data);
	};
	
	~BigInt(){
		// Деструктор
		delete [] _data;
	};

	BigInt & operator=(BigInt & other){
		// Оператор присваивания
		if (&other == this)
			return *this;
		// Если присваиваем самого себе

		_size = other._size;
		_minus = other._minus;

		delete[] _data;
		// Чистим существующую память

		_data = new char[_size];
		std::copy(other._data, other._data + other._size, _data);
		// Создаём новую и копируем данные

		return *this;
	};

	BigInt & operator=(BigInt && other){
		// Оператор присваивания для r-value
		
		delete[] _data;
		// Чистим существующую память
		
		_size = other._size;
		_minus = other._minus;
		_data = other._data;
		// Перемещаем данные

		other._data = nullptr;
		other._size = 0;
		// Чистим указатель перемещённого объекта
		
		return *this;
	};


	BigInt operator-(const BigInt & other) const{
		bool minus = false;
		
		if (_minus != other._minus)
			return ((*this) + BigInt(other._data, other._size, _minus));

		int max_size = max(_size, other._size);
		int min_size = min(_size, other._size);

		int sub_size = max_size;
		char * sub_data = new char[sub_size];
		
		BigInt tmp1 = *this;
		tmp1._minus = false;
		BigInt tmp2 = other;
		tmp2._minus = false;


		for (int j = 0; j < sub_size; j++)
			sub_data[j] = 0;

		char * ptr_1, * ptr_2;
		if (tmp1 < tmp2){
		//if ((_size < other._size) || (_data[0] < other._data[0]) && (_size == other._size)){
			ptr_1 = _data;
			ptr_2 = other._data;
			minus = !other._minus;
		}
		else{
			ptr_1 = other._data;
			ptr_2 = _data;
			minus = _minus;
		};
		// ptr 1 указывает на более короткое число
		// ptr 2 на более длинное

		for (int j = 0; j < min_size; j++)
			sub_data[j] = ptr_1[j];

		bool prev = false;
		// prev указывает на существование занимаемного разряда
		for (int j = 0, tmp = 0; j < sub_size; j++){
			tmp = - sub_data[j] + ptr_2[j] - prev;
			if (tmp < 0){
				sub_data[j] = tmp + 10;
				prev = true;
			}
			else{
				sub_data[j] = tmp;
				prev = false;
			};
		};
	
		while ((sub_data[sub_size - 1] == 0) && (sub_size > 1))
			sub_size--;
		// Удаляем незначащие нули !!!
		if ((sub_size == 1) && (sub_data[0] == 0))
			minus = 0;

		return BigInt(sub_data, sub_size, minus);
	};

	bool operator>(const BigInt & other) const{
		if ((*this) == other)
			return false;
		
		if ((_minus) && !(other._minus))
			return false;

		if (!(_minus) && (other._minus))
			return true;

		if ((_minus) && (other._minus))
			return ((*this) * (-1)) < other * (-1);
		
		// Оба положительные
		if (_size > other._size)
			return true;
		if (_size < other._size)
			return false;

		for (int i = _size - 1; i >= 0; i--){
			if (_data[i] > other._data[i])
				return true;
			if (_data[i] < other._data[i])
				return false;
		};
		// Сравниваем начиная со старших разрядов
		
		return false;
	};

	bool operator>=(const BigInt & other) const{
		return ((*this) > other) || ((*this) == other);
	};

	bool operator<(const BigInt & other) const{
		return !((*this) >= other);
	};
	
	bool operator<=(const BigInt & other) const{
		return !((*this) > other);
	};

	bool operator==(const BigInt & other) const{
		if (_size != other._size)
			return false;

		if ((_size == 1) && (_data[0] == 0) && (other._data[0] == 0))
			return true;

		if (_minus != other._minus)
			return false;

		for (int i = 0; i < _size; i++)
			if (_data[i] != other._data[i])
				return false;

		return true;
	};
	
	bool operator!=(const BigInt & other) const{
		return (!(*this == other));
	};

	BigInt operator+(const BigInt & other) const{
		bool minus = false;
		
		if (_minus == other._minus)
			minus = _minus;
		else
		{
			if ((*this) > other)
				return (*this - (other * (-1)));
			else
				return (other - ((*this) * (-1)));
		};

		int min_size = min(_size, other._size);
		int max_size = max(_size, other._size);
		
		int sum_size = max_size + 1;
		char * sum_data = new char[sum_size];

		for (int j = 0; j < sum_size; j++)
			sum_data[j] = 0;

		char * ptr_1, * ptr_2;
		if (_size < other._size){
			ptr_1 = _data;
			ptr_2 = other._data;
		}
		else{
			ptr_1 = other._data;
			ptr_2 = _data;
		};
		// ptr 1 указывает на более короткое число
		// ptr 2 на более длинное

		for (int j = 0; j < min_size; j++)
			sum_data[j] = ptr_1[j];
		// Будем прибавлять к более короткому числу

		bool prev = false;
		// Был ли перенос при сложении с умноженным на пред цифру число
		for (int j = 0, tmp = 0; j < sum_size - 1; j++){
			tmp = sum_data[j] + ptr_2[j] + prev;
			if (tmp > 9){
				sum_data[j] = tmp - 10;
				prev = 1;
			}
			else{
				sum_data[j] = tmp;
				prev = 0;
			};
		};

		if (prev)
			sum_data[sum_size - 1] = 1;
		else
			sum_size--;
		// Если последний раз не было переноса, то размер не увеличивается

		return BigInt(sum_data, sum_size, minus);
	};

	BigInt operator/(const BigInt & other) const{
		BigInt arg1(*this);
		arg1._minus = false;
		// arg1 - положительное число по модулю равное 1-му аргументу
		// с нулём в начале (старшие разряды)
		
		BigInt divident(arg1);
		
		BigInt divider = other;
		divider._minus = false;
		// divider - абсолютное значение делимого
		
		int current_pos = 0, new_digit = 0, previous_size, x = 0, y = 0;

		if ((*this) == 0)
			return 0;

		if (other == 0)
			throw "Divizion by zero!";

		char * quotient_data = new char[_size];
		// div_data - данные частного
		
		for (int i = 0; i < _size; i++)
			quotient_data[i] = 0;
		// Обнуляем частное

		BigInt quotient(quotient_data, _size, (this -> _minus) xor other._minus);
		// Частное
		
		if (divident < divider)
			quotient._data[++current_pos] = 0;
		else
		while (divident._size > 0)
		{
			if (divident < divider){
				for (int i = 0; i < y; i++)
					quotient._data[++current_pos] = 0;
				break;
			};

			previous_size = divident._size;
			
			char * begin_ptr = divident._data + divident._size - divider._size;
			// Выделение мин числа из начала делимого (от маск порядка) т.ч. оно больше делителя
			// Адрес начала

			BigInt tmp(begin_ptr, divider._size, 0);
			// Выделение числа
			if (tmp < divider)
				if (divider._size == divident._size){
					quotient_data[current_pos] = 0;
					current_pos++;
					break;
				}
				else{
					begin_ptr--;
					tmp = BigInt(begin_ptr, divider._size + 1, 0);
				};
			
			
			x = y - 1 - (divident._size - tmp._size);
			for (int  i = 0; i < x; i++){
				quotient._data[current_pos] = 0;
				current_pos++;
			};
			// Добавление нулей по кол-ву снесённых доп. цифр

			for (int j = 1; j <= 10; j++)
				if (divider * j > tmp){
					new_digit = --j;
					break;
				};		
			// Поиск цифры, которую необходимо добавить в частное
			
			divident = divident - ((divider * new_digit).shift(divident._size - tmp._size));

			quotient._data[current_pos] = new_digit;
			current_pos++;
			
			if ((divident == 0) && (previous_size - (divider * new_digit)._size != 0)){
				for (int i = 0; i < previous_size - (divider * new_digit)._size; i++){
					quotient._data[current_pos] = 0;
					current_pos++;
				};
				break;
			};
					
			
			if ((divident < divider) && (tmp._size == previous_size))
				break;

			y =  previous_size - tmp._size; 

		};
		quotient._size = current_pos;
		
		for (int i = 0; i < quotient._size / 2; i++)
			std::swap(quotient._data[i], quotient._data[quotient._size - i - 1]);
		
		return quotient;
	};

	BigInt operator*(const BigInt & other) const{
		int mul_size = _size + other._size;
		bool minus = _minus xor other._minus;
		char * mul_data = new char[mul_size];

		if ((*this == 0) || (other  == 0))
			return BigInt(0);

		BigInt tmp1 = *this;
		tmp1._minus = false;
		BigInt tmp2 = other;
		tmp2._minus = false;

		for (int i = 0; i < mul_size; i++)
			mul_data[i] = 0;

		BigInt mult(mul_data, mul_size, 0);
		
		for (int i = 0; i < tmp2._size; i++)
			mult = mult + (tmp1.digit_mul(tmp2._data[i])).shift(i);

		if (mult._data[mult._size-1] == 0)
			mult._size--;

		mult._minus = minus;

		return mult; 
	};

	friend std::ostream & operator<<(std::ostream & out, const BigInt & i);
};

std::ostream & operator<<(std::ostream & os, const BigInt & i){
	// Вывод числа
	if (i._minus) os << '-';
	for (int j = i._size - 1; j >= 0; j--)
		os << char(i._data[j] + '0');
	return os;
};
