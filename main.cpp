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
#include <mutex>
#include <future>
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

    void handleSpeedRate(double figure) { speedRate + figure <= 0 ? speedRate : speedRate += figure; }

private:
    double randomRate() { return (rand() % 100 + 50) / 100.0; } //倍率发生器 范围0.5-1.5

protected:
};

class Race
{
    vector<Horse> horses;
    atomic<bool> isOver;

    queue<pair<int, double>> queryQueue;
    mutex mtx;

    int winner = -1;

public:
    Race(int count)
    {
        if (count <= 5)
            count = 5;

        isOver = false;

        // srand((int)chrono::system_clock::to_time_t(chrono::system_clock::now()));
        srand(time(NULL));
        horseMaker(count);
    }

    ~Race() {}

    void start()
    {
        while (true)
        {
            if (isOver)
                break; // 判断结束

            {
                unique_lock<mutex>(this->mtx); //取锁
                if (queryQueue.size() != 0)
                    if (queryQueue.front().first < horses.size())
                    {
                        horses[queryQueue.front().first].handleSpeedRate(queryQueue.front().second);
                        queryQueue.pop();
                    } //处理队列事件
            }

            for (auto &i : this->horses)
                i.horseRun(); //每匹马前进一步

            vector<double> results;
            for (int i = 0; i < horses.size(); i++)
            {
                double location = horses[i].getLocation();
                if (location > 20.0)
                {
                    winner = i;
                    isOver = true;
                }
                results.push_back(location);
            }//获取结果与判断游戏是否结束
            printer(results); //打印结果

            this_thread::sleep_for(std::chrono::seconds(1)); //休眠1s
        }
    }

    bool getIsOver() { return isOver; }

    int getWinner() { return winner; }

    void bananaSkin(int order) { fxxkTheHorse(order, -0.5); }

    void dope(int order) { fxxkTheHorse(order, +0.5); }

private:
    void horseMaker(int count)
    {
        for (int i = 0; i < count; i++)
            horses.emplace_back();
    } //造马机

    void fxxkTheHorse(int order, double figure)
    {
        unique_lock<mutex>(this->mtx);
        queryQueue.push(pair<int, double>(order, figure));
    } //对特定的马进行加速或减速操作

protected:
};

int main()
{
    Race r(10);
    thread t([&]() {
        r.start();
    }); //子进程处理游戏

    while (!r.getIsOver())
    {
        r.dope(0);
        this_thread::sleep_for(std::chrono::milliseconds(500));
    } //主进程施加状态

    cout << "赢家是 " << r.getWinner() << " 号马！nmsl!" << endl;

    if (t.joinable())
        t.join(); //子进程收尾

    system("pause");

    return 0;
}