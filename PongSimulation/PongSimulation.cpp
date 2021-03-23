#include <iostream>
#include <thread>
#include <mutex>
#include <stdlib.h>
#include <condition_variable>
#include <chrono>
#include "Player.h"
#include "Score.h"

using namespace std;

Score score(0, 0);
mutex m;
int result;
condition_variable cond;
bool xReady = true;
bool yReady = false;

void pongX(Player* playerReady)
{
    unique_lock<mutex> lock(m);

    cond.wait(lock, [] {
        return xReady;
        });

    xReady = false;
    yReady = true;

    cout << "Player X Turn !!!" << endl;

    int* turn = new int;
    srand((int)turn);
    delete turn;

    playerReady->setHits(rand() % 101);
    cout << "---> " << playerReady->getHits();

    if (playerReady->getHits() <= 50) {
        score.theScore(0, 1);
        cout << " ---> X Failed !!!" << endl;
    }
    else {
        score.theScore(1, 0);
        cout << " ---> Y Turn..." << endl;
    }

    cond.notify_one();
    this_thread::sleep_for(chrono::seconds(1));
}

void pongY(Player* playerReady)
{
    unique_lock<mutex> lock(m);

    cond.wait(lock, [] {
        return yReady;
        });

    yReady = false;
    xReady = true;

    cout << "Player Y Turn !!!" << endl;

    int* turn = new int;
    srand((int)turn);
    delete turn;

    playerReady->setHits(rand() % 101);
    cout << "---> " << playerReady->getHits();

    if (playerReady->getHits() <= 50) {
        score.theScore(1, 0);
        cout << " ---> Y Failed !!!" << endl;
    }
    else {
        score.theScore(0, 1);
        cout << " ---> X Turn..." << endl;
    }

    cond.notify_one();
    this_thread::sleep_for(chrono::milliseconds(2500));
}

int main()
{
    Player playerX(1);
    Player playerY = playerX;

    int randPlayer;

    cout << "\t*** Pong Simulation ***" << endl << endl;

    int turns = 0;
    while (score.xScore() < 10 && score.yScore() < 10) {

        turns++;
        cout << "Turn " << turns << endl;

        int* turn = new int;
        srand((int)turn);
        delete turn;

        randPlayer = rand() % 2;

        if (randPlayer == 0) {

            thread px(pongX, &playerX);
            px.join();

            cout << "Current X Score = " << score.xScore() << endl;
            cout << "Current Y Score = " << score.yScore() << endl;
            cout << endl;

        }

        else {

            thread py(pongY, &playerY);
            py.join();

            cout << "Current X Score = " << score.xScore() << endl;
            cout << "Current Y Score = " << score.yScore() << endl;
            cout << endl;

        }

    }

    if (score.xScore() >= 10) {

        cout << "\n*** Player X Wins The Match***" << endl;
        cout << "Final Score (X) = " << score.xScore() << endl;
        cout << "Final Score (Y) = " << score.yScore() << endl;

    }

    else {

        cout << "\n*** Player Y Wins The Match***" << endl;
        cout << "Final Score (X) = " << score.xScore() << endl;
        cout << "Final Score (Y) = " << score.yScore() << endl;

    }


    return 0;
}
