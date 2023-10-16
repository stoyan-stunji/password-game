#ifndef TIMER_H
#define TIMER_H

#include <ctime>
#include <iostream>

class Timer
{
    private:
        size_t start = 0;
        size_t end = 0;
    
    public:
        void begin()
        {
            this->start = std::time(NULL);
            this->end = 0;
        }

        void finish()
        {
            this->end = std::time(NULL);
        }

        void print()
        {
            std::cout << (this->end - this->start);
        }

        size_t getDiff()
        {
            return (this->end - this->start);
        }

        friend std::ostream& operator<<(std::ostream& o, Timer timer)
        {
            timer.print();
            o << " second(s)";
            return o;
        }
};

#endif