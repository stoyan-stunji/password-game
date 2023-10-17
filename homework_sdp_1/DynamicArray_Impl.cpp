#include <iostream>
#include <cstdlib>

#include <vector>
#include <string>
#include <sstream>

using namespace std;

//prefer .h file

template <typename T>
class DynamicArray
{
private:
    T* data;
    std::size_t size;
    std::size_t capacity;

    static const std::size_t REALLOC_STEP = 2;

    void copy(const DynamicArray &other) 
    {
        if (other.capacity == 0) 
        {
            *this = DynamicArray();
            return;
        }

        this->data = new T[other.capacity];
        this->capacity = other.capacity;
        for (this->size = 0; this->size < other.size; this->size++) 
        {
            data[this->size ] = other[this->size ];
        }
    }

    void free() 
    {
        delete[] this->data;
        this->data = nullptr;
        this->size = 0;
        this->capacity = 0;
    }

    void reserve(std::size_t n)
    {
        T* buffer = new T[n];

        for (std::size_t i = 0; i < this->size; ++i) 
        {
            buffer[i] = this->data[i];
        }

        delete[] this->data;
        this->data = buffer;
        this->capacity = n;
    }

    void swap(T& first, T& second)
    {
        T temp = first;
        first = second;
        second = temp;
    }

    T min(const T& a, const T& b) 
    {
        return (a < b) ? a : b;
    }

public:
    DynamicArray() : data(nullptr), size(0), capacity(0) 
    {}

    DynamicArray(const DynamicArray &other) 
    {
        copy(other);
    }

    DynamicArray& operator= (const DynamicArray &other) 
    {
        if (this != &other) 
        {
            free();
            copy(other);
        }
        return *this;
    }

    ~DynamicArray() 
    {
        free();
    }

    std::size_t getSize() const 
    {
        return this->size;
    }

    T& operator[] (std::size_t index) 
    {
        return this->data[index];
    }

    const T& operator[] (std::size_t index) const 
    {
        return this->data[index];
    }

    void print() const
    {
        std::cout << "[ ";
        for (size_t i = 0; i < this->size; i++)
        {
            std::cout << this->data[i] << " ";
        }
        std::cout << "]\n";
    }

    //Task 1:
    void push_back(const T &elem) 
    {
        if (this->size == this->capacity) 
        {
            if(this->capacity == 0)
            {
                reserve(1);
            }
            else
            {
                reserve(this->capacity * REALLOC_STEP);
            }
        }

       this->data[this->size] = elem;
       this->size++;
    }

    void pop_back() 
    {
        this->size--;
    }

    //Task 2:
    void reverse()
    {
        for (size_t i = 0; i < this->size / 2; i++)
        {
            swap(this->data[i], this->data[this->size - i - 1]);
        }      
    }

    //Task 3:
    void clear()
    {
        while (this->size > 0)
        {
            pop_back();
        }     
    }

    //Task 4:
    DynamicArray operator+(const DynamicArray& other)
    {   
        DynamicArray result;
        std::size_t minSize = min(this->size, other.size);

        for (size_t i = 0; i < minSize; i++)
        {
            result.push_back(this->data[i] + other.data[i]);
        }

        if (this->size > other.size)
        {
            for (size_t i = other.size; i < this->size; i++)
            {
                result.push_back(this->data[i]);
            }
        }
        else
        {
            for (size_t i = this->size; i < other.size; i++)
            {
                result.push_back(other.data[i]);
            }
        }
        return result;
    }

    DynamicArray& operator+=(const DynamicArray& other)
    {
        return (*this = *this + other);
    }

    //Task 5:
    void removeMax()
    {
        if (this->size == 0)
        {
            return;
        }

        T maxElement = this->data[0];
        for (size_t i = 1; i < this->size; i++)
        {
            if (this->data[i] > maxElement)
            {
                maxElement = this->data[i];
            }
        }

        size_t newSize = 0;
        for (size_t i = 0; i < this->size; i++)
        {
            if (this->data[i] != maxElement)
            {
                this->data[newSize] = this->data[i];
                newSize++;
            }
        }

        this->size = newSize;
    }

    //Task 6:
    void insert(size_t pos, const T& elem)
    {
        if (this->size <= pos)
        {
            throw std::out_of_range("Invalid index! //insert");
            //throw "Invalid index!";
            //then try-catch (const char* error) in the main
        }

        if (this->size == this->capacity)
        {
            if (this->capacity == 0)
            {
                reserve(1);
            }
            else
            {
                reserve(this->capacity * REALLOC_STEP);
            }
        }

        for (size_t i = this->size; i > pos; i--)
        {
            this->data[i] = this->data[i - 1];
        }

        this->data[pos] = elem;
        this->size++;
    }

    void insertAfter(size_t pos, const T& elem)
    {
        insert(pos + 1, elem);
    }

    //Task 7:
    void pop(size_t pos)
    {
        if (this->size <= pos)
        {
            throw std::out_of_range("Invalid index! //pop");
        }

        for (std::size_t i = pos; i < this->size - 1; i++)
        {
            this->data[i] = this->data[i + 1];
        }

        this->size--;
    }

    void replace(size_t pos, const T& elem)
    {
        if (this->size <= pos)
        {
            throw std::out_of_range("Invalid index! //replace");
        }

        this->data[pos] = elem;
    }

    void modifyByInstruction(const std::string& instructions) 
    {
        std::istringstream iss(instructions);
        std::string instruction;

        while (iss >> instruction) 
        {
            if (instruction == "insert") 
            {
                size_t pos;
                T elem;
                iss >> pos >> elem;
                if(this->size <= pos)
                {
                    throw std::invalid_argument("Invalid position! //insert");
                }
                insert(pos, elem);
                //print();
            } 
            else if (instruction == "replace") 
            {
                size_t pos;
                T elem;
                iss >> pos >> elem;
                if(this->size <= pos)
                {
                    throw std::invalid_argument("Invalid position! //replace");
                }
                replace(pos, elem);
                //print();
            } 
            else if (instruction == "delete") 
            {
                size_t pos;
                T elem;
                iss >> pos >> elem;
                if(this->size <= pos)
                {
                    throw std::invalid_argument("Invalid position! //delete");
                }
                pop(pos);
                //print();
            } 
            else 
            {
                throw std::invalid_argument("Invalid instructions!");
            }
        }
    }
};

int main() 
{
    DynamicArray<int> arr;
    arr.push_back(4);
    arr.push_back(6);
    arr.push_back(7);
    arr.push_back(9);
    arr.print();
    
    arr.modifyByInstruction("delete 2 -1 insert 0 8 replace 1 5");
    arr.print();
}