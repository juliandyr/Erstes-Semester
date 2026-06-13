#include <array>
#include <cstddef>
using namespace std;


int getRandom(int lower, int upper);

enum Allocation{
    hidden, revealed, mine
};

struct Tile{
    Allocation state;
    int sourroundingMines;
};

//Konstanten Deklarieren
constexpr size_t cols = 12;
constexpr size_t rows = 12;


// global 2D-Array Deklarieren (Spielfeld)
extern array<array<Tile, cols>, rows> spielfeld2DA;

//macht jedes tile auf hidden, dann verteilt es rdm die 15 mines
//dann sagt es für eine xy wv mines drumrum sind
void initialize();

//wird für sourroundingmines gebraucht
int countMines(int x, int y);

//für output
void display();

//für input
bool inputfunction(bool continuegame);

//für harmlose nachbarn
bool revealedEmptyNeighbour(int x, int y);
bool checkNeighbours();

int counthiddentiles(int x, int y);
