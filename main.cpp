#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <queue>

/* C++11 */
#include <chrono>
#include <thread>
#include <atomic>
/* C++11 */

using namespace std;

void printer(vector<double> locations)
{
    system("cls");
    for (int line = 0; line < locations.size(); line++)
    {
        for (int location = 0; location < 20; location++)
        {
            if (location == (int)locations[line])
                cout << "M";
            else
                cout << "+";
        }
        cout << endl;
    }
}

class Horse

{
    double speedRate = 0;
    double location = 0;

public:
    Horse() { this->speedRate = (60 + rand() % 80) / 100.0; } //基础速度

    void horseRun() { this->location += speedRate * randomRate(); } //处理移动 基础速度 * 倍率 = 移动速度

    double getLocation() { return this->location; }

private:
    double randomRate() { return (rand() % 100 + 50) / 100.0; } //倍率发生器 范围0.5-1.5

protected:
};

class Race
{
    vector<Horse> horses;
    bool isOver = false;
    // atomic<bool> isOver(false);

public:
    Race(int count)
    {
        if (count <= 5)
            count = 5;

        srand((int)chrono::system_clock::to_time_t(chrono::system_clock::now()));
        horseMaker(count);
    }

    ~Race() {}

    void start()
    {
        thread t([&](){
            while(true)
            {
                if(isOver) break;

            }
        });

        while (true)
        {
            if(isOver) break;

            for (auto &i : this->horses)
                i.horseRun();

            vector<double> results;
            for (auto &i : this->horses)
            {
                double location = i.getLocation();
                if (location > 20.0)
                    isOver = true;
                else
                    results.push_back(location);
            }
            printer(results);

            this_thread::sleep_for(std::chrono::seconds(1));
        }

        if(t.joinable())
            t.join();
    }

private:
    void horseMaker(int count)
    {
        for (int i = 0; i < count; i++)
            horses.emplace_back();
    }

protected:
};

int main()
{
    Race r(10);
    r.start();
    return 0;
}