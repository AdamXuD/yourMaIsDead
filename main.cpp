#include <iostream>
#include <vector>

using namespace std;

class Horse
{
    unsigned int speedRate = 0;
    double location = 0;

public:
    Horse() {  this->speedRate = 80 + rand() % 40 + 1; }

private:
protected:
};

class Race
{
    Horse *horse[5];

public:
    Race() { memset(this->horse, 0, sizeof(Horse*[5])); }


private:
    void horseMaker()
    {
        for(auto i : this->horse)
            i = new Horse;
    }

protected:
};

void printer()
{

}

void start()
{

}

int main()
{
    return 0;
}