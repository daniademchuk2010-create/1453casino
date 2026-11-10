
#include <iostream>
#include <queue>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

class Human
{
    string name;
    int year;
    int money;
    int wins;

public:

    Human(string n, int y, int m)
    {
        name = n;
        year = y;
        money = m;
        wins = 0;
    }

    void show()
    {
        cout << "\n========== PLAYER INFO ==========\n";
        cout << "Name: " << name << endl;
        cout << "Year: " << year << endl;
        cout << "Points: " << money << endl;
        cout << "Wins: " << wins << endl;
    }

    void Writeaboutyou()
    {
        cout << "Enter your name: ";
        cin >> name;

        cout << "Enter your year: ";
        cin >> year;

        if (year < 18)
        {
            cout << "You are underage!" << endl;
        }
        else
        {
            cout << "Welcome, " << name << "!" << endl;
        }
    }

    void Spin(queue<string>& slot, int rotations)
    {
        for (int i = 0; i < rotations; i++)
        {
            string temp = slot.front();
            slot.pop();
            slot.push(temp);
        }
    }

    void ShowTable(string reels[])
    {
        // Верхня рамка
        cout << char(201);
        for (int i = 0; i < 5; i++)
        {
            cout << string(14, char(205));
            cout << (i == 4 ? char(187) : char(203));
        }
        cout << endl;

        // Назви слотів
        cout << char(186);
        for (int i = 0; i < 5; i++)
        {
            cout << "    " << left << setw(10)
                << ("SLOT " + to_string(i + 1))
                << char(186);
        }
        cout << endl;

        // Розділювач
        cout << char(204);
        for (int i = 0; i < 5; i++)
        {
            cout << string(14, char(205));
            cout << (i == 4 ? char(185) : char(206));
        }
        cout << endl;

        // Символи
        cout << char(186);
        for (int i = 0; i < 5; i++)
        {
            cout << "    " << left << setw(10) << reels[i]
                << char(186);
        }
        cout << endl;

        // Нижня рамка
        cout << char(200);
        for (int i = 0; i < 5; i++)
        {
            cout << string(14, char(205));
            cout << (i == 4 ? char(188) : char(202));
        }
        cout << endl;
    }

    bool isWin(string reels[])
    {
        int winsCount = 0;

        for (int i = 0; i < 5; i++)
        {
            int count = 0;

            for (int j = 0; j < 5; j++)
            {
                if (reels[i] == reels[j])
                    count++;
            }

            if (count > winsCount)
                winsCount = count;
        }

        if (winsCount < 3)
        {
            cout << "\nNo win!\n";
            return false;
        }

        switch (winsCount)
        {
        case 3:
            cout << "\nThree identical symbols!\n";
            cout << "Reward: 30 virtual points!\n";
            money += 30;
            break;

        case 4:
            cout << "\nFour identical symbols!\n";
            cout << "Reward: 100 virtual points!\n";
            money += 100;
            break;

        case 5:
            cout << "\nJACKPOT!!!\n";
            cout << "Reward: 500 virtual points!\n";
            money += 500;
            break;
        }

        wins++;
        return true;
    }

    void Game()
    {
        queue<string> slot[5];

        string symbols[5] =
        {
            "Cherry", "Bell", "Seven", "Star", "Diamond"
        };

        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                slot[i].push(symbols[j]);
            }
        }

        char choice;

        do
        {
            cout << "\n========== ONE-ARMED BANDIT ==========\n";
            cout << "Virtual points: " << money << endl;
            cout << "Press Enter to spin or Q to exit: ";

            cin.ignore(1000, '\n');
            cin.get(choice);

            if (choice == 'q' || choice == 'Q')
                break;

            string reels[5];

            for (int i = 0; i < 5; i++)
            {
                int rotations = rand() % 10 + 1;
                Spin(slot[i], rotations);
                reels[i] = slot[i].front();
            }

            ShowTable(reels);
            isWin(reels);

        } while (true);
    }

    void ChooseGame()
    {
        int choice;

        do
        {
            cout << "\n========== GAME MENU ==========\n";
            cout << "1. One-armed bandit\n";
            cout << "2. Player profile\n";
            cout << "0. Exit\n";

            cout << "Choose: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                Game();
                break;

            case 2:
                show();
                break;

            case 0:
                cout << "Goodbye!\n";
                break;

            default:
                cout << "Wrong choice!\n";
            }

        } while (choice != 0);
    }
};

int main()
{
    srand(time(0));

    Human player("No name", 0, 100);

    player.Writeaboutyou();
    player.ChooseGame();

    return 0;
}