#include <bits/stdc++.h>
using namespace std;

// board class, manages everything related to the board
class board
{
private:
    // the layout, contains the position of every pawn
    vector<vector<string>> boardLayout = vector<vector<string>>(5, vector<string>(5, "-"));

public:
    // printing the initial status of the board
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

    // filling the board with the players' initial position of pawns
    void updateBoardInit(unordered_map<string, vector<int>> locs, int playerID)
    {

        char playerName = playerID == 1 ? 'A' : 'B';

        for (auto i : locs)
        {
            boardLayout[i.second[0]][i.second[1]] = playerName + i.first;
        }
    }

    // updating the board after every move
    string updateBoardMove(unordered_map<string, vector<int>> P1locs, unordered_map<string, vector<int>> P2locs, char moveBy)
    {
        // cleaning the board
        for (int i = 0; i < boardLayout.size(); i++)
        {
            for (int j = 0; j < boardLayout[i].size(); j++)
            {
                boardLayout[i][j] = "-";
            }
        }

        // filling the board with player's pawns
        for (auto i : P1locs)
        {
            boardLayout[i.second[0]][i.second[1]] = 'A' + i.first;
        }

        for (auto i : P2locs)
        {
            boardLayout[i.second[0]][i.second[1]] = 'B' + i.first;
        }

        string dedChar = "na";

        // check if the a player's pawn dies
        for (auto i : P1locs)
        {
            for (auto j : P2locs)
                if (i.second[0] == j.second[0] && i.second[1] == j.second[1])
                    dedChar = moveBy == 'A' ? 'B' + j.first : 'A' + i.first;
        }
        cout << "-";

        // updating the board

        return dedChar;
    }

    // printing the board
    void printBoard()
    {
        for (int i = 0; i < boardLayout.size(); i++)
        {
            for (int j = 0; j < boardLayout[i].size(); j++)
            {
                cout << boardLayout[i][j] << "\t";
            }
            cout << "\n";
        }
    }
};

// player class, manages everything related to the player's pawns's status
class player
{
    // the pawns
    unordered_map<string, vector<int>> pawns;
    // id of the player
    int playerID;
    // no of pawns left
    int pawnLeft;

public:
    player(int id)
    {
        playerID = id;
    }

    //setting initial location of the pawns
    unordered_map<string, vector<int>> setInitLoc(vector<string> loc)
    {

        int locX = playerID == 1 ? 0 : 4;

        for (int i = 0; i < loc.size(); i++)
        {
            pawns[loc[i]].push_back(locX);
            pawns[loc[i]].push_back(i);
        }

        pawnLeft = 5;
        return pawns;
    }

    // get the location of pawns
    unordered_map<string, vector<int>> getPlayerLoc()
    {
        return pawns;
    }

    // no of pawns left
    int getNoOfPawnsLeft()
    {
        return pawnLeft;
    }

    // updates the pawn locations as per the move
    unordered_map<string, vector<int>> setPlayerMove(string pawnID, char move)
    {
        switch (move)
        {
        case 'F':
            pawns[pawnID][0]++;
            break;
        case 'B':
            pawns[pawnID][0]--;
            break;
        case 'L':
            pawns[pawnID][1]++;
            break;
        case 'R':
            pawns[pawnID][1]--;
            break;
        }
        return pawns;
    }

    // if the players' pawn dies, it is updated here
    void updatePawnStatus(string pawnID)
    {
        pawnLeft--;
        pawns.erase(pawnID);
    }
};

int main()
{
    board b;
    player P1(1), P2(2);

    // getting the initial locations of the pawns from the players
    vector<string> initLocation;
    string loc;
    cout << "Player 1 input:";

    for (int i = 0; i < 5; i++)
    {
        cin >> loc;
        initLocation.push_back(loc);
    }

    b.updateBoardInit(P1.setInitLoc(initLocation), 1);
    b.printBoard();

    cout << "Player 2 input:";
    for (int i = 0; i < 5; i++)
    {
        cin >> loc;
        initLocation.push_back(loc);
    }

    b.updateBoardInit(P2.setInitLoc(initLocation), 2);
    b.printBoard();

    // keeps track of who's chance it is to make a move
    // if it's false then A else B
    bool whoMove = false;

    // the actual game, runs till either P1's or P2's number of pawns become 0
    while (P1.getNoOfPawnsLeft() && P2.getNoOfPawnsLeft())
    {

        if (!whoMove)
        {

            cout << "Player A move: \t";
            string playerMove;
            cin >> playerMove;

            string updates = b.updateBoardMove(P1.setPlayerMove(playerMove.substr(0, 2), playerMove[playerMove.size() - 1]), P2.getPlayerLoc(), 'A');

            if (updates != "na")
                P2.updatePawnStatus(updates.substr(1, 2));
        }

        else
        {
            cout << " Player B move: \t";
            string playerMove;
            cin >> playerMove;

            string updates = b.updateBoardMove(P1.getPlayerLoc(), P2.setPlayerMove(playerMove.substr(0, 2), playerMove[playerMove.size() - 1]), 'B');

            if (updates != "na")
                P1.updatePawnStatus(updates.substr(1, 2));
        }
        b.printBoard();
        whoMove = !whoMove;
    }

    return 0;
}