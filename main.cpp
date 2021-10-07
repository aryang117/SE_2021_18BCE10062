#include <bits/stdc++.h>
using namespace std;
class board
{
private:
    vector<vector<string>> boardLayout = vector<vector<string>>(5, vector<string>(5, "-"));

public:
    board()
    {
        for (vector<string> i : boardLayout)
        {
            for (auto j : i)
            {
                cout << j << "\t";
            }
            cout << "\n";
        }
    }

    void updateBoard(unordered_map<int, vector<int>> locs, int playerID)
    {

        char playerName = playerID == 1 ? 'A' : 'B';

        for (auto i : locs)
        {
            boardLayout[i.second[0]][i.second[1]] = playerName + i.first;
            cout << "updatedLoc";
        }
    }

    void printBoard()
    {
        for (vector<string> i : boardLayout)
        {
            for (auto j : i)
            {
                cout << j << "\t";
            }
            cout << "\n";
        }
    }
};

class player
{
    unordered_map<string, vector<int>> pawns;
    int playerID;

public:

    player(int id)
    {
        playerID = id;
    }
    void setInitLoc(vector<string> loc, board b)
    {

        int locX = playerID == 1 ? 0 : 4;

        for (int i = 0; i < loc.size(); i++)
        {
            pawns[loc[i]].push_back(locX);
            pawns[loc[i]].push_back(i);
        }
    }
};


int main()
{
    board b;
    player P1(1), P2(2);

    vector<string> initLocation;
    string loc;
    cout << "Player 1 input:";

    for (int i = 0; i < 5; i++)
    {
        cin >> loc;
        initLocation.push_back(loc);
    }

    P1.setInitLoc(initLocation, b);
    b.printBoard();

    return 0;
}