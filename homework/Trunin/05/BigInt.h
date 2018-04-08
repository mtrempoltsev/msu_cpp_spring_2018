#include <iostream>
#include <iomanip>

struct BigInt{
    
private:
    int* coef;
    int size;

    bool is_minus;
    int64_t BASE = 10000;
    
void resize(int size_){
    delete[] coef;
    max_size = size_;
    size = 0;
    coef = new int[max_size];
    for(int i = 0; i < max_size; i++){
        coef[i] = 0;
    }
}
    
public:
    
    int max_size;
    
    BigInt(){
        max_size = 8;
        coef = new int[max_size];
        for(int i = 0; i < max_size; i++){
            coef[i] = 0;
        }
        size = 0;
        is_minus = false;
    }
    
    BigInt(int64_t number){
        max_size = 8;
        coef = new int[max_size];
        for(int i = 0; i < max_size; i++){
            coef[i] = 0;
        }
        if(number < 0){
            is_minus = true;
            number = -number;
        }else{
            is_minus = false;
        }
        int64_t tempNum = number;
        size = 0;    
        if(tempNum != 0){            
            while(tempNum > 0) {
                size++;
                coef[size - 1] = tempNum%BASE;
                tempNum /= BASE;
            }    
        }        
        
    }
    
    ~BigInt(){
        delete[] coef;
    }
    
    
    BigInt(const BigInt &copied){
        size = copied.size;
        is_minus = copied.is_minus;
        max_size = copied.max_size;
        coef = new int[max_size];
        std::copy(copied.coef, copied.coef + max_size, coef);
    }
    
    BigInt& operator=(const BigInt &copied){
        if(this == &copied){
            return *this;
        }
        delete[] coef;
        is_minus = copied.is_minus;
        size = copied.size;
        max_size = copied.max_size;
        coef = new int[max_size];
        std::copy(copied.coef, copied.coef + size, coef);
    }
    
    BigInt(BigInt &&moved){
        coef = moved.coef;
        size = moved.size;
        is_minus = moved.is_minus;
        max_size = moved.max_size;
        moved.coef = nullptr;
    }
    
    BigInt& operator=(BigInt &&moved){
        if (this == &moved)
            return *this;
        delete[] coef;
        coef = moved.coef;
        is_minus = moved.is_minus;
        size = moved.size;
        max_size = moved.max_size;
        moved.coef = nullptr;
        return *this;        
    }
    
    BigInt operator+(const BigInt& other) const
    {
        
        if(!is_minus && other.is_minus){
            return *this - (-other);
        }
        
        if(is_minus && !other.is_minus){
            return other - (-*this);
        }
        
        BigInt tmp;
        
        if(is_minus && other.is_minus){
            tmp.is_minus = true;
        }
        
        if(std::max(other.size, size) + 1 > max_size ){
            tmp.resize(2*std::max(other.max_size, max_size));
        } else{
            tmp.resize(std::max(other.max_size, max_size));
        }
        
        int max_size_adders = std::max(other.size, size);
        
        int temp_coef = 0;
        int next_coef = 0;
        tmp.size = 0;
        
        int first_coef = 0;
        int second_coef = 0;
        
        for(int i = 0; (i < max_size_adders || next_coef != 0) ; i++){
            
            if(i >= size){
                first_coef = 0;
            } else {
                first_coef = coef[i];
            }
            
            if(i >= other.size){
                second_coef = 0;
            } else {
                second_coef = other.coef[i];
            }
                
            temp_coef = next_coef + second_coef + first_coef;
            
            tmp.size++;
            if(temp_coef - BASE >= 0) {
                next_coef = 1;
                tmp.coef[i] = temp_coef - BASE;
            } else {
                next_coef = 0;
                tmp.coef[i] = temp_coef;
            }
        }
        
        return tmp;
    }
    
    BigInt operator-(const BigInt& other) const
    {
        
        if( (is_minus && other.is_minus && other < *this) || (!is_minus && !other.is_minus && *this < other) ){
            return -(other - *this);
        }
        
        if(!is_minus && other.is_minus || is_minus && !other.is_minus){
            return *this + (-other);
        }
        
        BigInt tmp;
        
        if(is_minus && other.is_minus){
            tmp.is_minus = true;
        }
        
        tmp.resize(std::max(other.max_size, max_size));
        
        int max_size_adders = std::max(other.size, size);
        
        int temp_coef = 0;
        int next_coef = 0;
        tmp.size = 0;
        
        int first_coef = 0;
        int second_coef = 0;
            
        for(int i = 0; (i < max_size_adders) ; i++){
            
            if(i >= size){
                first_coef = 0;
            } else {
                first_coef = coef[i];
            }
            
            if(i >= other.size){
                second_coef = 0;
            } else {
                second_coef = other.coef[i];
            }
            
            temp_coef = first_coef - second_coef - next_coef;
            tmp.size++;
            if(temp_coef >= 0) {
                next_coef = 0;
                tmp.coef[i] = temp_coef;
            } else {
                next_coef = 1;
                if(i == max_size_adders - 1){
                    tmp.coef[i] = -temp_coef;
                }else{
                    tmp.coef[i] = BASE + temp_coef;
                }
            }
        }
        for(int i = tmp.size - 1; i >= 0; i--){
            if(tmp.coef[i] == 0){
                tmp.size--;
            } else {
                break;
            }
        }
        
        return tmp;
    }
    
    BigInt operator*(const BigInt& other) const
    {
        BigInt tmp;
        if ((other.size == 0) || this->size == 0) return tmp;

        int max = std::max(other.max_size, max_size);
        if(max > other.size + size){
            tmp.resize(max);
        } else {
            tmp.resize(2*max);
        }
        
        tmp.is_minus = is_minus^other.is_minus;
        
        int64_t carry = 0;
        int i = 0, j;
        int64_t temp;
        
        for(i = 0; i < size; i++){
            carry = 0;
            for(j = 0; j < other.size; j++){
                temp = coef[i]*other.coef[j] + tmp.coef[i + j] + carry;
                carry = temp/BASE;
                tmp.coef[i+j] = temp - carry*BASE;        
            }
            tmp.coef[i+j] = carry;
        }
        i = other.size + size - 1;
        if(tmp.coef[i] == 0) i--;
        tmp.size = i + 1;
        
        return tmp;
    }
    
    BigInt operator*(const int value){
        BigInt tmp;
        if ((value == 0) || this->size == 0) return tmp;
        
        if(size + 1 > max_size){
            tmp.resize(max_size*2);
        }
        
        int r = 0;
        tmp.size = size;
        for(int i = 0; i < tmp.size | r; i++){
            tmp.coef[i] = coef[i] * value + r;
            r = tmp.coef[i]/BASE;
            tmp.coef[i] -= r*BASE;
        }
        if(tmp.coef[tmp.size]){
            tmp.size++;
        }
        return tmp;
    }
    
    void shiftLeft(){
        size++;
        for(int i = size - 1; i >= 1; i--){
            coef[i] = coef[i-1];
        }    
    }
    
    BigInt operator/(const BigInt& other) const
    {
        
        BigInt tmp;
        tmp.resize(max_size);
        tmp.size = 0;
        BigInt curValue;
        curValue.resize(max_size);
        curValue.size = 0;

        tmp.is_minus = is_minus^other.is_minus;
        
        BigInt divider = other;
        if (divider.is_minus) divider = -divider;
        
        for( int i = size - 1 ; i >= 0; i--){
            curValue.shiftLeft();
            curValue.coef[0] = coef[i];
            
            int x = 0;
            int l = 0, r = BASE;
            
            while(l <= r){
                int m = (l+r) >> 1;
                BigInt cur = divider*m;
                if(cur <= curValue){
                    x = m;
                    l = m + 1;
                    if(cur == curValue) break;
                } else {
                    r = m - 1;
                }
                
            }
            tmp.coef[i] = x;
            curValue = curValue - divider*x;
        }
        
        int pos = size;
        while(pos >= 0 && !tmp.coef[pos]){
            pos--;
        }
        
        tmp.size = pos + 1;
        
        return tmp;
    }
    
    bool operator==(const BigInt& value) const{
        if(size == 0 && value.size == 0) return true;
        if(is_minus^value.is_minus) return false;
        if(value.size != size) return false;
        for(int i = size - 1; i >= 0; i--){
            if(value.coef[i] != coef[i]){
                return false;
            }     
        }
        return true;
    }
    
    bool operator<=(const BigInt& value) const{
        if(size == 0 && value.size == 0) return true;
        if(is_minus && !value.is_minus) return true;
        if(!is_minus && value.is_minus) return false;
        if(is_minus && value.is_minus) return -value <= -(*this);
        if(value.size > size) return true;
        if(value.size < size) return false;
        for(int i = size - 1; i >= 0; i--){
            if(value.coef[i] < coef[i]){
                return false;
            } 
            if(value.coef[i] > coef[i]){
                return true;
            }
                
        }
        
        return true;
    }
    
    bool operator!=(const BigInt& value) const{
        return !(*this == value);
    }
    
    bool operator>(const BigInt& value) const{
        return !(*this <= value);
    }
    
    bool operator<(const BigInt& value) const{
        return (*this <= value) && !(*this == value);
    }
    
    bool operator>=(const BigInt& value) const{
        return !(*this < value);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const BigInt& data); 
    
    BigInt operator-() const{
        BigInt tmp = *this;
        tmp.is_minus = !tmp.is_minus;
        return tmp;
    }
        
};

std::ostream& operator<<(std::ostream& os, const BigInt& data) 
    {
        if (data.size == 0){
            os << "0";
            return os;
        }
        
        os.fill('0');
        if(data.is_minus){
            os << "-";
        }
        os << data.coef[data.size - 1];
        for(int i = data.size - 2; i >= 0; i--){
            os << std::setw(4) << data.coef[i];
        }
        
        return os;
    }
