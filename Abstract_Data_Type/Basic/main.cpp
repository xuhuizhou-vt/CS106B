#include <iostream>
#include "console.h"

#include "vector.h"
#include "grid.h"
#include "set.h"
#include "map.h"

#include "simpio.h"
using namespace std;

// pass by reference
void dream(Vector<int> &numbers) {
    numbers[1] = 1963;
}

// traversing a grid
void printGrid(Grid<char> &grid) {
    for(int i = 0; i < grid.numRows(); i++) {
        for(int j = 0; j < grid.numCols(); j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
}

int main() {
//    // ADT-1: string
//    Vector<int>  v1 = {1, 2};

//    for (int i = 0; i < 2; i++) {
//        v1.add(randomInteger(0,100));
//    }

//    for (int i: v1) {
//        cout << i << endl;
//    }

//    Vector<string> v2 = {"A", "B", "C"};

//    for (string i: v2) {
//        cout << i << endl;
//    }

//    Vector<int> values = {1929, 1955, 1964};
//    dream(values);
//    cout << values << endl;

//    Vector<string> wordlist;

//    while (true) {
//        string word = getLine("Enter your word: ");
//        if (word == "") {
//            break;
//        }
//        wordlist.add(word);
//    }

//    cout << wordlist << endl;

    // ADT-2: grid

    Grid<int> matrix(2,2);
    matrix[0][0] = 42;
    matrix[0][1] = 6;
    matrix[1][0] = matrix[0][1];
    cout << matrix.numRows() << endl;
    cout << matrix[0][1] << endl;
    cout << matrix[1][1] << endl;

    Grid<char> letters(3,2);
    letters[0][0] = 'a';
    letters[0][1] = 'b';
    letters[1][0] = 'c';
    letters[1][1] = 'd';
    letters[2][0] = 'e';
    letters[2][1] = 'f';
    printGrid(letters);

    // ADT-3: set: no sequence and no no duplicate elements

    Set<string> friends;
    while (true) {
        string name = getLine("Enter friend's name: ");
        if (name == "") {
            break;
        }
        friends.add(name);
    }

    cout << friends << endl;


    // ADT-4: map
    Map<string, int> map = {{"a", 1},{"b", 2}};
    map.put("c", 1);
    cout << map.toString() << endl;

    return 0;
}
