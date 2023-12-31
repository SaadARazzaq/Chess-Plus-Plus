#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <math.h>
#include <limits>
using namespace std;

#define max(a,b) (((a) > (b)) ? (a) : (b))

HANDLE console_color;
fstream myFile;

const char WHITE_ROOK = 'R';
const char WHITE_PAWN = 'P';
const char WHITE_HORSE = 'H';
const char WHITE_BISHOP = 'B';
const char WHITE_QUEEN = 'Q';
const char WHITE_KING = 'K';

const char BLACK_ROOK = 'r';
const char BLACK_PAWN = 'p';
const char BLACK_HORSE = 'h';
const char BLACK_BISHOP = 'b';
const char BLACK_QUEEN = 'q';
const char BLACK_KING = 'k';

bool WHITE_CASTLE_LEFT = true;
bool WHITE_CASTLE_RIGHT = true;
bool WHITE_CASTLE_KING = true;

bool BLACK_CASTLE_LEFT = true;
bool BLACK_CASTLE_RIGHT = true;
bool BLACK_CASTLE_KING = true;

char BLACK_EN_PASSANT;
char WHITE_EN_PASSANT;

const char EMPTY_SQUARE = -2;
const char VERTICAL_LINE = -70;
const char HORIZONTAL_LINE = -51;

const char WHITE_PLAYER = 1;  // The uppercase player
const char BLACK_PLAYER = 2;  // The lowercase player

void ClearInputBuffer() {
    while (cin.get() != '\n') {
        // Keep reading and discarding characters until a newline is encountered
    }
}

int StartUP_menu()
{
	int input;
start:
	system("CLS");
cout << "\033[1;31m";
cout<<"         ######  ##     ## ########  ######   ######                 \n";  
cout<<"        ##    ## ##     ## ##       ##    ## ##    ##      ##     ##   \n";
cout<<"        ##       ##     ## ##       ##       ##            ##     ##   \n";
cout<<"        ##       ######### ######    ######   ######     ###### ###### \n";
cout<<"        ##       ##     ## ##             ##       ##      ##     ##   \n";
cout<<"        ##    ## ##     ## ##       ##    ## ##    ##      ##     ##   \n";
cout<<"         ######  ##     ## ########  ######   ######                   \n";
                                                                 
            cout<<"\033[1;0m";

	cout << endl;
	cout << "  1) Start The Game" << endl;
	cout << "  2) Basic Rules" << endl;
	cout << "  3) Exit Game" << endl;
	cout << endl;
	cout << "  Select Option(1-3): ";
	cin >> input;
	while (!cin.good() || input < 1 || input>4)
	{
		cin.clear();
		// cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Could have used this too to clean input buffer
        ClearInputBuffer();
		system("CLS");
        
cout << "\033[1;31m";
cout<<"         ######  ##     ## ########  ######   ######                 \n";  
cout<<"        ##    ## ##     ## ##       ##    ## ##    ##      ##     ##   \n";
cout<<"        ##       ##     ## ##       ##       ##            ##     ##   \n";
cout<<"        ##       ######### ######    ######   ######     ###### ###### \n";
cout<<"        ##       ##     ## ##             ##       ##      ##     ##   \n";
cout<<"        ##    ## ##     ## ##       ##    ## ##    ##      ##     ##   \n";
cout<<"         ######  ##     ## ########  ######   ######                   \n";
                                                                 
            cout<<"\033[1;0m";
            
		cout << endl;
        cout << "  1) Start The Game" << endl;
        cout << "  2) Basic Rules" << endl;
        cout << "  3) Exit Game" << endl;
        cout << endl;
        cout << "  Select Option(1-3): ";
		cin >> input;
	}
	switch (input)
	{
	case 1:
		break;
	case 2:
		system("CLS");
		cout << "White Player (UPERCASE)--> P,Q,K,R,B,H" << endl;
		cout << "BLACK Player (LOWERCASE)--> p,q,k,r,b,h" << endl;
		cout << endl;
		cout << "Pieces List/ Movement:" << endl;
		cout << endl;
		cout << " - PAWN (P/p) --> Moves one square at a time, it can only move forward,\nit can only capture enemy pieces diagonally (one square to the left/Right and one up),\nif it has not moved yet they can start by moving two squares forward, \nit can do an en passant capture this happens when the opponent pawn does a double move in the start \nand then if you have a pawn that could have killed the enemy pawn if it had moved only one square \nthen you can still caputre it. \nIf it reaches the final square on the board you can promote it to whatever piece you want except for pawn itself." << endl;
		cout << endl << endl;
		cout << " - Rook (R/r) --> Moves vertically and horizontally the amount of squares you want without passing through any pieces." << endl;
		cout << endl << endl;
		cout << " - Horse (H/h) --> Moves in an L shape, two squares horizontally and one vertically or two squares vertically and one square horizontally." << endl;
		cout << endl << endl;
		cout << " - Bishop (B/b) --> Moves Diagonally the amount of squares you want without passing through any pieces." << endl;
		cout << endl << endl;
		cout << " - Queen (Q/q) --> Moves like a rook and a bishop, it can move diagonally/vertically/horizontally\nthe amount of squares you want without passing through any pieces" << endl;
		cout << endl << endl;
		cout << " - King (K/k) --> Can only move one square in any direction, you can castle the king queen side or king side, \nthis means that if there are no pieces between your king and either of your rooks you can move your king two squares \nin the direction you are castling and put the rook on that side \nnext to the king(if you castled king side then your king will go from e1 to g1 and the rook will go from h1 to f1), \nthis can only be done if neither the king and rook that you are using to castle have moved that game and if your king isn't in check." << endl;
		cout << endl << endl;
		cout << "Basic Knowledge:" << endl << endl;
		cout << endl << endl;
		cout << "Check --> Your King is being attacked by an enemy piece you must move your king to a safe spot or kill the \natacker or interpose the attack with another piece." << endl;
		cout << "Checkmate --> Your King is being attacked and you can't do anything to protect him, you lost the game." << endl;
		cout << "Stalemate --> The player that has to make a move can't move any of his pieces, it is a tie." << endl;
		system("pause");
		goto start;
	case 3:
		exit(0);
	}
	return 0;
}

void Create_Grid(char Grid[][8])  // First of all create empty 8x8 grid with all the blocks initialized to white blocks 
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Grid[i][j] = EMPTY_SQUARE;
		}
	}

	//Setup Pieces at indexes of the grid

	for (int j = 0; j < 8; j++)
	{
		Grid[1][j] = BLACK_PAWN;
		Grid[6][j] = WHITE_PAWN;
	}

	Grid[0][0] = BLACK_ROOK;
	Grid[0][1] = BLACK_HORSE;
	Grid[0][2] = BLACK_BISHOP;
	Grid[0][3] = BLACK_QUEEN;
	Grid[0][4] = BLACK_KING;
	Grid[0][5] = BLACK_BISHOP;
	Grid[0][6] = BLACK_HORSE;
	Grid[0][7] = BLACK_ROOK;

	Grid[7][0] = WHITE_ROOK;
	Grid[7][1] = WHITE_HORSE;
	Grid[7][2] = WHITE_BISHOP;
	Grid[7][3] = WHITE_QUEEN;
	Grid[7][4] = WHITE_KING;
	Grid[7][5] = WHITE_BISHOP;
	Grid[7][6] = WHITE_HORSE;
	Grid[7][7] = WHITE_ROOK;
}

void Display_Grid(char Grid[][8])
{
	system("CLS");
	cout << "\t\t";
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, FOREGROUND_RED); // Red
	for (int j = 0; j < 8; j++){
        cout << (char)(j + 97) << "\t";  // For displaying the a-h characters on top of the board for keeping track of columns
    }
	cout << endl;

	cout << " \t       ";
	for (int i = 0; i < 59; i++){
        cout << HORIZONTAL_LINE;
    }

    SetConsoleTextAttribute(console_color, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Reset

	for (int i = 0; i < 8; i++)
	{
        cout<<endl;
        SetConsoleTextAttribute(console_color, FOREGROUND_RED); // Red
		cout << "\t    " << (8 - i) << " " << VERTICAL_LINE << " ";  // (8 - i) is written to print he numbers from 8 to 1 reverse in grid
		SetConsoleTextAttribute(console_color, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Reset
        for (int j = 0; j < 8; j++)
		{
			cout << Grid[i][j];
            if(j<7){
                cout<<"\t";
            }
            if(j==7){
                SetConsoleTextAttribute(console_color, FOREGROUND_RED); // Red
		        cout << " " << VERTICAL_LINE;
		        SetConsoleTextAttribute(console_color, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Reset
            }
		}
		cout << endl;
	}

    SetConsoleTextAttribute(console_color, FOREGROUND_RED); // Red
	cout << " \t       ";
	for (int i = 0; i < 59; i++){
        cout << HORIZONTAL_LINE;
    }
    SetConsoleTextAttribute(console_color, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Reset

    cout<<endl;
    cout<<endl;
}

bool Check_Start(char Grid[][8], char x, char y, char player)  //  This function checks VALIDITY OF MOVES
{
	char pos = Grid[x][y];  // Any position on the grid

	// Check piece existence. If the block has no piece then return false as the move will be invalid.

	if (pos == EMPTY_SQUARE)
	{
        //Returns false if the starting position is wrong
		return false;
	}

	// Check if it is your piece

	if (player == WHITE_PLAYER)
	{
        //  Check if position that is selected has white piece on it
		if (pos != WHITE_BISHOP && pos != WHITE_HORSE && pos != WHITE_ROOK && pos != WHITE_KING && pos != WHITE_QUEEN && pos != WHITE_PAWN)
			return false;
	}
	else if (player == BLACK_PLAYER)
	{
        //  Check if position that is selected has black piece on it
		if (pos != BLACK_BISHOP && pos != BLACK_HORSE && pos != BLACK_ROOK && pos != BLACK_KING && pos != BLACK_QUEEN && pos != BLACK_PAWN)
			return false;
	}

	return true;
}

bool Player_In_Check(char Grid[][8], char player)  // This function was made to tell that if there is any threaten to the opposite king

/* In this function, Checking for bishops and queens is done 
-  because these pieces have diagonal attack patterns and can 
-  potentially threaten the opponent's king diagonally.
*/

{
	int s,t,x,y;
	if (player == BLACK_PLAYER)
	{
		for (int p = 0; p < 8; p++)
		{
			for (int m = 0; m < 8; m++)
			{
                // Check for Black Bishops and Queens
				if (Grid[p][m] == BLACK_BISHOP || Grid[p][m] == BLACK_QUEEN)
				{
					//Look on all directions
					//Search TOP Left x-- y--
					s = m - 1;
					t = p - 1;
					while (t >= 0 && s >= 0)
					{
                        // Check for pieces blocking or White King
						if (Grid[t][s] != EMPTY_SQUARE && Grid[t][s] != WHITE_KING)
							break;
						else if (Grid[t][s] == WHITE_KING)
							return true;
						s--;
						t--;
					}					
					//Search BOTTOM Right x++ y++
					s = m + 1;
					t = p + 1;
					while (t < 8 && s < 8)
					{
						if (Grid[t][s] != EMPTY_SQUARE && Grid[t][s] != WHITE_KING)
							break;
						else if (Grid[t][s] == WHITE_KING)
							return true;
						s++;
						t++;
					}
					//Search BOTTOM Left x++ y--
					s =  - 1;
					t = p + 1;
					while (s >= 0 && t < 8)
					{
						if (Grid[t][s] != EMPTY_SQUARE && Grid[t][s] != WHITE_KING)
							break;
						else if (Grid[t][s] == WHITE_KING)
							return true;
						s--;
						t++;
					}
					//Search top Right x-- y++
					s = m + 1;
					t = p - 1;
					while (s < 8 && t >= 0)
					{
						if (Grid[t][s] != EMPTY_SQUARE && Grid[t][s] != WHITE_KING)
							break;
						else if (Grid[t][s] == WHITE_KING)
							return true;
						s++;
						t--;
					}
				}
				if (Grid[p][m] == BLACK_ROOK || Grid[p][m] == BLACK_QUEEN)
				{
					//Look Right
					for (int t = m + 1; t < 8; t++)
					{
						if (Grid[p][t] != EMPTY_SQUARE && Grid[p][t] != WHITE_KING)
							break;
						else if (Grid[p][t] == WHITE_KING)
							return true;
					}
					//Look Left
					for (int t = m - 1; t >= 0; t--)
					{
						if (Grid[p][t] != EMPTY_SQUARE && Grid[p][t] != WHITE_KING)
							break;
						else if (Grid[p][t] == WHITE_KING)
							return true;
					}
					//Look Up
					for (int t = p + 1; t < 8; t++)
					{
						if (Grid[t][m] != EMPTY_SQUARE && Grid[t][m] != WHITE_KING)
							break;
						else if (Grid[t][m] == WHITE_KING)
							return true;
					}
					//Look Down
					for (int t = p - 1; t >= 0; t--)
					{
						if (Grid[t][m] != EMPTY_SQUARE && Grid[t][m] != WHITE_KING)
							break;
						else if (Grid[t][m] == WHITE_KING)
							return true;
					}
				}
				if (Grid[p][m] == BLACK_HORSE)
				{
                    // Check if horse can threaten 2 squares down, 1 square right
					if (p + 2 < 8 && m + 1 < 8 && Grid[p + 2][m + 1] == WHITE_KING)
						return true;
                    // Check if horse can threaten 2 squares down, 1 square left
					if (p + 2 < 8 && m - 1 >= 0 && Grid[p + 2][m - 1] == WHITE_KING)
						return true;
                    // Check if horse can threaten 2 squares up, 1 square right
					if (p - 2 >= 0 && m + 1 < 8 && Grid[p - 2][m + 1] == WHITE_KING)
						return true;
                    // Check if horse can threaten 2 squares up, 1 square left
					if (p - 2 >= 0 && m - 1 >= 0 && Grid[p - 2][m - 1] == WHITE_KING)
						return true;
                    // Check if horse can threaten 1 square down, 2 squares right
					if (p + 1 < 8 && m + 2 < 8 && Grid[p + 1][m + 2] == WHITE_KING)
						return true;
                    // Check if horse can threaten 1 square down, 2 squares left
					if (p + 1 < 8 && m - 2 >= 0 && Grid[p + 1][m - 2] == WHITE_KING)
						return true;
                    // Check if horse can threaten 1 square up, 2 squares right
					if (p - 1 >= 0 && m + 2 < 8 && Grid[p - 1][m + 2] == WHITE_KING)
						return true;
                    // Check if horse can threaten 1 square up, 2 squares left
					if (p - 1 >= 0 && m - 2 >= 0 && Grid[p - 1][m - 2] == WHITE_KING)
						return true;
				}
				else if (Grid[p][m] == BLACK_PAWN)
				{
					if (m + 1 < 8 && Grid[p + 1][m + 1] == WHITE_KING)  // Check if a pawn can threaten from the top-right position
						return true;
					if (m + 1 < 8 && Grid[p + 1][m - 1] == WHITE_KING)  // Check if a pawn can threaten from the top-left position
						return true;
				}
			}
		}
	}
	else if (player == WHITE_PLAYER)
	{
		for (int p = 0; p < 8; p++)
		{
			for (int m = 0; m < 8; m++)
			{
				if (Grid[p][m] == WHITE_BISHOP || Grid[p][m] == WHITE_QUEEN)
				{
					//Look on all directions
					//Search TOP Left x-- y--
					s = m - 1;
					t = p - 1;
					while (t >= 0 && s >= 0)
					{
						if (Grid[t][s] != EMPTY_SQUARE && Grid[t][s] != BLACK_KING)
							break;
						else if (Grid[t][s] == BLACK_KING)
							return true;
						s--;
						t--;
					}
					//Search BOTTOM Right x++ y++
					s = m + 1;
					t = p + 1;
					while (t < 8 && s < 8)
					{
						if (Grid[t][s] != EMPTY_SQUARE && Grid[t][s] != BLACK_KING)
							break;
						else if (Grid[t][s] == BLACK_KING)
							return true;
						s++;
						t++;
					}
					//Search BOTTOM Left x++ y--
					s = m - 1;
					t = p + 1;
					while (s >= 0 && t < 8)
					{
						if (Grid[t][s] != EMPTY_SQUARE && Grid[t][s] != BLACK_KING)
							break;
						else if (Grid[t][s] == BLACK_KING)
							return true;
						s--;
						t++;
					}
					//Search top Right x-- y++
					s = m + 1;
					t = p - 1;
					while (s < 8 && t >= 0)
					{
						if (Grid[t][s] != EMPTY_SQUARE && Grid[t][s] != BLACK_KING)
							break;
						else if (Grid[t][s] == BLACK_KING)
							return true;
						s++;
						t--;
					}
				}
				if (Grid[p][m] == WHITE_ROOK || Grid[p][m] == WHITE_QUEEN)
				{
					//Look Right
					for (int t = m + 1; t < 8; t++)
					{
						if (Grid[p][t] != EMPTY_SQUARE && Grid[p][t] != BLACK_KING)
							break;
						else if (Grid[p][t] == BLACK_KING)
							return true;
					}
					//Look Left
					for (int t = m - 1; t >= 0; t--)
					{
						if (Grid[p][t] != EMPTY_SQUARE && Grid[p][t] != BLACK_KING)
							break;
						else if (Grid[p][t] == BLACK_KING)
							return true;
					}
					//Look Up
					for (int t = p + 1; t < 8; t++)
					{
						if (Grid[t][m] != EMPTY_SQUARE && Grid[t][m] != BLACK_KING)
							break;
						else if (Grid[t][m] == BLACK_KING)
							return true;
					}
					//Look Down
					for (int t = p - 1; t >= 0; t--)
					{
						if (Grid[t][m] != EMPTY_SQUARE && Grid[t][m] != BLACK_KING)
							break;
						else if (Grid[t][m] == BLACK_KING)
							return true;
					}
				}
				if (Grid[p][m] == WHITE_HORSE)
				{
					if (p + 2 < 8 && m + 1 < 8 && Grid[p + 2][m + 1] == BLACK_KING)
						return true;
					if (p + 2 < 8 && m - 1 >= 0 && Grid[p + 2][m - 1] == BLACK_KING)
						return true;
					if (p - 2 >= 0 && m + 1 < 8 && Grid[p - 2][m + 1] == BLACK_KING)
						return true;
					if (p - 2 >= 0 && m - 1 >= 0 && Grid[p - 2][m - 1] == BLACK_KING)
						return true;
					if (p + 1 < 8 && m + 2 < 8 && Grid[p + 1][m + 2] == BLACK_KING)
						return true;
					if (p + 1 < 8 && m - 2 >= 0 && Grid[p + 1][m - 2] == BLACK_KING)
						return true;
					if (p - 1 >= 0 && m + 2 < 8 && Grid[p - 1][m + 2] == BLACK_KING)
						return true;
					if (p - 1 >= 0 && m - 2 >= 0 && Grid[p - 1][m - 2] == BLACK_KING)
						return true;
				}
				else if (Grid[p][m] == WHITE_PAWN)
				{
					if (m + 1 < 8 && Grid[p - 1][m + 1] == BLACK_KING)
						return true;
					if (m + 1 < 8 && Grid[p - 1][m - 1] == BLACK_KING)
						return true;
				}
			}
		}
	}

	//Check that both kings are not in contact
	
	//First locate the kings
	for (s = 0; s < 8; s++){
		for (t = 0; t < 8; t++){
			if (Grid[s][t] == BLACK_KING){
				goto fd;
			}
		}
	}
fd:

	for (x = 0; x < 8; x++){
		for (y = 0; y < 8; y++){
			if (Grid[x][y] ==WHITE_KING){
				goto fd2;
			}
		}
	}
fd2:
	//Then we check if they are close, this will be checked by their block distance as king can attack in one block anywhere from the king so check if other king not present in that block

	if (abs(x - s) <= 1 && abs(y - t) <= 1)
		return true;
	return false;
}

bool Check_ADVANCED(char Grid[][8], char x, char y, char j, char z, char player)
{
	// x: Represents the row index of the source square
	// y: Represents the column index of the source square
	// j: Represents the row index of the destination square
	// z: Represents the column index of the destination square

	char piece = Grid[x][y];
	char dest = Grid[j][z];
	bool Castle_Left = false;
	bool Castle_Right = false;
	bool King_Move = false;
	bool check = false;
	char en_passant = 'z';
	char aux, aux_piece;  // temporary variables
	int m, s, t;
	//Basic movement and Captures
	switch (piece)
	{
	case WHITE_PAWN:  // for handling pawn moves, captures, promotion, and en passant
	case BLACK_PAWN:
		//Check backwards movement
		if (piece == WHITE_PAWN && j > x)  // if white pawn want to move backward
			return false;
		else if (piece == BLACK_PAWN && x > j)  // if black pawn want to move backward
			return false;

		//Check posible DOUBLE move if FIRST time moving pawn 
		if (abs(x - j) == 2 && abs(y - z) == 0) // if column is same but row moved 2 times
		{
			if (player == WHITE_PLAYER && x == 6)  //  For cheeck if piece selected is white pawn
			{
				en_passant = y;
				goto CHECK_CHECK;
			}
			else if (player == BLACK_PLAYER && x == 1)  //  For cheeck if piece selected is black pawn
			{
				en_passant = y;
				goto CHECK_CHECK;
			}
		}

		// Check if en passant has been performed
		if (dest == EMPTY_SQUARE && abs(y - z) != 0 && ((player == WHITE_PLAYER && Grid[j + 1][z] == BLACK_PAWN && BLACK_EN_PASSANT == z) || (player == BLACK_PLAYER && Grid[j - 1][z] == WHITE_PAWN && WHITE_EN_PASSANT == z)))
		{
			en_passant = 'k';
			goto CHECK_CHECK;
		}

		//Check that the move is not further than one square and if it goes diagonally there is not an empty square and can t kill enemies just walking forward
		if (abs(y - z) > 1 || abs(x - j) > 1 || ((y != z) && (dest == EMPTY_SQUARE)) || ((y == z) && (dest != EMPTY_SQUARE)))
			return false;
		//check promote
		if (j == 0 || j == 7)
		{
			cout << "What do you want to promote to?" << endl;
			cout << "Queen (Q/q) Bishop (B/b) Horse (H/h) Rook (R/r)" << endl;
			cin >> piece;
			bool white_promote = (player == WHITE_PLAYER && (piece == WHITE_HORSE || piece == WHITE_BISHOP || piece == WHITE_QUEEN || piece == WHITE_ROOK));
			bool black_promote = (player == BLACK_PLAYER && (piece == BLACK_HORSE || piece == BLACK_BISHOP || piece == BLACK_QUEEN || piece == BLACK_ROOK));
			bool result = !(white_promote ^ black_promote);  // used xor to check if current move involves promotion of pawn or not
			while (!cin.good() || result)  // cin.good() returns true if the input stream is in a good state, meaning that no errors have occurred during previous input operations
			{
				cin.clear();
		        // cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Could have used this too to clean input buffer
				ClearInputBuffer();
                system("CLS");
				Display_Grid(Grid);
				cout << "What do you want to promote to?" << endl;
				cout << "Queen (Q/q) Bishop (B/b) Horse (H/h) Rook (R/r)" << endl;
				cout << "Insert Correct data" << endl;
				cin >> piece;
				white_promote = (player == WHITE_PLAYER && (piece == WHITE_HORSE || piece == WHITE_BISHOP || piece == WHITE_QUEEN || piece == WHITE_ROOK));
				black_promote = (player == BLACK_PLAYER && (piece == BLACK_HORSE || piece == BLACK_BISHOP || piece == BLACK_QUEEN || piece == BLACK_ROOK));
				result = !(white_promote ^ black_promote);
			}
			Grid[x][y] = piece;
		}
		break;
	case WHITE_HORSE:
	case BLACK_HORSE:
		//Basic movement
		if (abs(x - j) == 2 && abs(y - z) == 1)
			goto CHECK_CHECK;
		if (abs(y - z) == 2 && abs(x - j) == 1)
			goto CHECK_CHECK;
		return false;
	case WHITE_QUEEN:
	case BLACK_QUEEN:
	case WHITE_ROOK:
	case BLACK_ROOK:
		//Check Vertical movement
		if (x == j && y != z)  // src and dest column is same but row not same
		{
			y < z ? aux = y : aux = z;
			for (int t = 1; t < abs(y - z); t++)
				if (Grid[x][t + aux] != EMPTY_SQUARE)
					return false;
			if (piece == BLACK_ROOK || piece == WHITE_ROOK)
			{
				if (y == 7) Castle_Right = true;
				if (y == 0) Castle_Left = true;
			}
			goto CHECK_CHECK;
		}
		//Check Horizontal movement
		if (z == y && x != j)
		{
			x < j ? aux = x : aux = j;
			for (int t = 1; t < abs(x - j); t++)
				if (Grid[t + aux][y] != EMPTY_SQUARE)
					return false;
			if (piece == BLACK_ROOK || piece == WHITE_ROOK)
			{
				if (y == 7) Castle_Right = true;
				if (y == 0) Castle_Left = true;
			}
			goto CHECK_CHECK;
		}
		if (piece == BLACK_ROOK || piece == WHITE_ROOK)
			return false;
	case WHITE_BISHOP:
	case BLACK_BISHOP:
		//Check diagonal movement
		if (abs(x - j) != abs(y - z) || abs(x - j) == 0)
			return false;
		//Search TOP Left x-- y--
		if (x > j && y > z)
		{
			m = y - 1;
			for (int t = x - 1; t > j; t--)
			{
				if (Grid[t][m] != EMPTY_SQUARE)
					return false;
				m--;
			}
		}
		//Search BOTTOM Right x++ y++
		else if (x < j && y < z)
		{
			m = y + 1;
			for (int t = x + 1; t < j; t++)
			{
				if (Grid[t][m] != EMPTY_SQUARE)
					return false;
				m++;
			}
		}
		//Search BOTTOM Left x++ y--
		else if (x < j && y>z)
		{
			m = y - 1;
			for (int t = x + 1; t < j; t++)
			{
				if (Grid[t][m] != EMPTY_SQUARE)
					return false;
				m--;
			}
		}
		//Search top Right x-- y++
		else
		{
			m = y + 1;
			for (int t = x - 1; t > j; t--)
			{
				if (Grid[t][m] != EMPTY_SQUARE)
					return false;
				m++;
			}
		}
		goto CHECK_CHECK;
		break;
	case WHITE_KING:
	case BLACK_KING:
		//Basic movement
		if (abs(j - x) > 1 || abs(y - z) > 2 || (abs(y - z) > 1 && y != 4))
			return false;
		//Castling
		if (abs(y - z) == 2 && abs(j - x) == 0 && (x == 0 || x == 7) && y == 4)
		{
			if (player == WHITE_PLAYER && WHITE_CASTLE_KING == true && (WHITE_CASTLE_LEFT == true || WHITE_CASTLE_RIGHT == true))
			{
				if (z == 6) //Castle right
				{
					if (Grid[x][5] != EMPTY_SQUARE || Grid[x][6] != EMPTY_SQUARE || WHITE_CASTLE_RIGHT == false)
						return false;
					Grid[x][5] = WHITE_ROOK;
					Grid[x][6] = WHITE_KING;
					Grid[x][7] = EMPTY_SQUARE;
					King_Move = true;
					goto CHECK_CHECK;
				}
				if (z == 2) //Castle left
				{
					if (Grid[x][3] != EMPTY_SQUARE || Grid[x][2] != EMPTY_SQUARE || Grid[x][1] != EMPTY_SQUARE || WHITE_CASTLE_LEFT == false)
						return false;
					Grid[x][3] = WHITE_ROOK;
					Grid[x][2] = WHITE_KING;
					Grid[x][0] = EMPTY_SQUARE;
					King_Move = true;
					goto CHECK_CHECK;
				}
			}
			if (player == BLACK_PLAYER && BLACK_CASTLE_KING == true && (BLACK_CASTLE_LEFT == true || BLACK_CASTLE_RIGHT == true))
			{
				if (z == 6)//Castle right
				{
					if (Grid[x][5] != EMPTY_SQUARE || Grid[x][6] != EMPTY_SQUARE || BLACK_CASTLE_RIGHT == false)
						return false;
					Grid[x][5] = BLACK_ROOK;
					Grid[x][6] = BLACK_KING;
					Grid[x][7] = EMPTY_SQUARE;
					King_Move = true;
					goto CHECK_CHECK;
				}
				if (z == 2)
				{
					if (Grid[x][3] != EMPTY_SQUARE || Grid[x][2] != EMPTY_SQUARE || Grid[x][1] != EMPTY_SQUARE || BLACK_CASTLE_LEFT == false)
						return false;
					Grid[x][3] = BLACK_ROOK;
					Grid[x][2] = BLACK_KING;
					Grid[x][0] = EMPTY_SQUARE;
					King_Move = true;
					goto CHECK_CHECK;
				}
			}
			return false;
		}
		King_Move = true;
		break;
	}
CHECK_CHECK:
	//We perform the move on the actual Grid but check that if the move is not posible we goto restore and we change the grid again to the reset grid.
	Grid[x][y] = EMPTY_SQUARE;
	aux_piece = Grid[j][z];
	Grid[j][z] = piece;
	if (player == WHITE_PLAYER)
	{
		//An en passant capture is being checked
		if (en_passant == 'k'){
			Grid[j + 1][z] = EMPTY_SQUARE;
		}

		check = Player_In_Check(Grid, player % 2 + 1);

		if (check == true)
		{
			if (en_passant == 'k') {
				Grid[j + 1][z] = BLACK_PAWN;
			}
			goto restore;
		}

		//update castle variables
		if (WHITE_CASTLE_KING == true) WHITE_CASTLE_KING = !King_Move;
		if (WHITE_CASTLE_LEFT == true) WHITE_CASTLE_LEFT = !Castle_Left;
		if (WHITE_CASTLE_RIGHT == true) WHITE_CASTLE_RIGHT = !Castle_Right;
		//update en passant column
		if (en_passant != 'z' && en_passant != 'k') WHITE_EN_PASSANT = en_passant;
		BLACK_EN_PASSANT = 'z';
	}
	if (player == BLACK_PLAYER)
	{
		//An en passant capture is being checked
		if (en_passant == 'k') Grid[j - 1][z] = EMPTY_SQUARE;

		check = Player_In_Check(Grid, player % 2 + 1);
		if (check == true)
		{
			if (en_passant == 'k') {
				Grid[j - 1][z] = WHITE_PAWN;
				}
			goto restore;
		}

		//update castle variables
		if (BLACK_CASTLE_KING == true) BLACK_CASTLE_KING = !King_Move;
		if (BLACK_CASTLE_LEFT == true) BLACK_CASTLE_LEFT = !Castle_Left;
		if (BLACK_CASTLE_RIGHT == true) BLACK_CASTLE_RIGHT = !Castle_Right;
		//update en passant column
		if (en_passant != 'z' && en_passant != 'k') {
			BLACK_EN_PASSANT = en_passant;
		}
		WHITE_EN_PASSANT = 'z';
	}
	//returns false if the move is not possible
	return true;
restore:
	// restore the chess board state when a move is found to be invalid. 
	Grid[x][y] = Grid[j][z];
	Grid[j][z] = aux_piece;
	return false;
}


bool validate_My_Own_Move(char Grid[][8], char x, char y, char j, char z, char player)
{
	char pos = Grid[j][z];

	//Check if destination is empty
	if (pos == EMPTY_SQUARE)
	{
		return Check_ADVANCED(Grid, x, y, j, z, player);
	}

	//Check if destination is one of your pieces
	if (player == WHITE_PLAYER)
	{
		if (pos == WHITE_BISHOP || pos == WHITE_HORSE || pos == WHITE_ROOK || pos == WHITE_KING || pos == WHITE_QUEEN || pos == WHITE_PAWN)
			return false;
	}
	else
	{
		if (pos == BLACK_BISHOP || pos == BLACK_HORSE || pos == BLACK_ROOK || pos == BLACK_KING || pos == BLACK_QUEEN || pos == BLACK_PAWN)
			return false;
	}
	return Check_ADVANCED(Grid, x, y, j, z, player);
}

bool Check_Tie(char Grid[][8], char player)
{
	// checks draw if one player has only a king and other player has a king and a bishop
	// Here in this function i did is that if curr player is in checkmate, do a specific move such that the player gets out of checkmate else reset the grid as it is because theres no need of updated grid

	char piece, aux, obj1, obj2;
	//Check all the pieces of the player until one can move
	if (Player_In_Check(Grid, player) == true)
	{
		return false;
	}
	if (player == BLACK_PLAYER)
	{
		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				piece = Grid[x][y];
				if (piece == WHITE_PAWN)
				{
					//check normal movement then  finally check if en passant is posible
					if (Grid[x - 1][y] == EMPTY_SQUARE)
					{
						Grid[x][y] = EMPTY_SQUARE;
						Grid[x - 1][y] = piece;
						if (Player_In_Check(Grid, player) == false)
						{
							Grid[x - 1][y] = EMPTY_SQUARE;
							Grid[x][y] = piece;
							return false;
						}
						Grid[x - 1][y] = EMPTY_SQUARE;
						Grid[x][y] = piece;
					}
					//check capture right + en passant right
					if (y + 1 < 8)
					{
						obj1 = Grid[x - 1][y + 1];
						if (obj1 == BLACK_PAWN || obj1 == BLACK_ROOK || obj1 == BLACK_HORSE || obj1 == BLACK_BISHOP || obj1 == BLACK_QUEEN)
						{
							Grid[x - 1][y + 1] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x][y] = piece;
								Grid[x - 1][y + 1] = obj1;
								return false;
							}
							Grid[x][y] = piece;
							Grid[x - 1][y + 1] = obj1;
						}
						//check en passant
						if (obj1 == EMPTY_SQUARE && x == 3 && (Grid[x][y + 1] == BLACK_PAWN && BLACK_EN_PASSANT == y + 1))
						{
							aux = Grid[x][y + 1];
							Grid[x - 1][y + 1] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							Grid[x][y + 1] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x - 1][y + 1] = EMPTY_SQUARE;
								Grid[x][y] = piece;
								Grid[x][y + 1] = aux;
								return false;
							}
							Grid[x - 1][y + 1] = EMPTY_SQUARE;
							Grid[x][y] = piece;
							Grid[x][y + 1] = aux;
						}
					}
					//check capture left + en passant left
					if (y - 1 >= 0)
					{
						obj2 = Grid[x - 1][y - 1];
						if (obj2 == BLACK_PAWN || obj2 == BLACK_ROOK || obj2 == BLACK_HORSE || obj2 == BLACK_BISHOP || obj2 == BLACK_QUEEN)
						{
							Grid[x - 1][y - 1] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x][y] = piece;
								Grid[x - 1][y - 1] = obj2;
								return false;
							}
							Grid[x][y] = piece;
							Grid[x - 1][y - 1] = obj2;
						}
						//check en passant
						if (obj2 == EMPTY_SQUARE && x == 3 && (Grid[x][y - 1] == BLACK_PAWN && BLACK_EN_PASSANT == y - 1))
						{
							aux = Grid[x][y - 1];
							Grid[x - 1][y - 1] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							Grid[x][y - 1] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x - 1][y - 1] = EMPTY_SQUARE;
								Grid[x][y] = piece;
								Grid[x][y - 1] = aux;
								return false;
							}
							Grid[x - 1][y - 1] = EMPTY_SQUARE;
							Grid[x][y] = piece;
							Grid[x][y - 1] = aux;
						}
					}
				}
				if (piece == WHITE_HORSE)
				{
					//Check all its moves until one can be done
					if (x + 2 < 8 && y + 1 < 8)
					{
						obj1 = Grid[x + 2][y + 1];
						if (obj1 == EMPTY_SQUARE || obj1 == BLACK_PAWN || obj1 == BLACK_ROOK || obj1 == BLACK_HORSE || obj1 == BLACK_BISHOP || obj1 == BLACK_QUEEN)
						{
							Grid[x + 2][y + 1] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x + 2][y + 1] = obj1;
								Grid[x][y] = piece;
								return false;
							}
							Grid[x + 2][y + 1] = obj1;
							Grid[x][y] = piece;
						}
					}
					if (x + 2 < 8 && y - 1 >= 0)
					{
						obj1 = Grid[x + 2][y - 1];
						if (obj1 == EMPTY_SQUARE || obj1 == BLACK_PAWN || obj1 == BLACK_ROOK || obj1 == BLACK_HORSE || obj1 == BLACK_BISHOP || obj1 == BLACK_QUEEN)
						{
							Grid[x + 2][y - 1] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x + 2][y - 1] = obj1;
								Grid[x][y] = piece;
								return false;
							}
							Grid[x + 2][y - 1] = obj1;
							Grid[x][y] = piece;
						}
					}
					if (x - 2 >= 0 && y + 1 < 8)
					{
						obj1 = Grid[x - 2][y + 1];
						if (obj1 == EMPTY_SQUARE || obj1 == BLACK_PAWN || obj1 == BLACK_ROOK || obj1 == BLACK_HORSE || obj1 == BLACK_BISHOP || obj1 == BLACK_QUEEN)
						{
							Grid[x - 2][y + 1] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x - 2][y + 1] = obj1;
								Grid[x][y] = piece;
								return false;
							}
							Grid[x - 2][y + 1] = obj1;
							Grid[x][y] = piece;
						}
					}
					if (x - 2 >= 0 && y - 1 >= 0)
					{
						obj1 = Grid[x - 2][y - 1];
						if (obj1 == EMPTY_SQUARE || obj1 == BLACK_PAWN || obj1 == BLACK_ROOK || obj1 == BLACK_HORSE || obj1 == BLACK_BISHOP || obj1 == BLACK_QUEEN)
						{
							Grid[x - 2][y - 1] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x - 2][y - 1] = obj1;
								Grid[x][y] = piece;
								return false;
							}
							Grid[x - 2][y - 1] = obj1;
							Grid[x][y] = piece;
						}
					}
					if (x + 1 < 8 && y + 2 < 8)
					{
						obj1 = Grid[x + 1][y + 2];
						if (obj1 == EMPTY_SQUARE || obj1 == BLACK_PAWN || obj1 == BLACK_ROOK || obj1 == BLACK_HORSE || obj1 == BLACK_BISHOP || obj1 == BLACK_QUEEN)
						{
							Grid[x + 1][y + 2] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x + 1][y + 2] = obj1;
								Grid[x][y] = piece;
								return false;
							}
							Grid[x + 1][y + 2] = obj1;
							Grid[x][y] = piece;
						}
					}
					if (x + 1 < 8 && y - 2 >= 0)
					{
						obj1 = Grid[x + 1][y - 2];
						if (obj1 == EMPTY_SQUARE || obj1 == BLACK_PAWN || obj1 == BLACK_ROOK || obj1 == BLACK_HORSE || obj1 == BLACK_BISHOP || obj1 == BLACK_QUEEN)
						{
							Grid[x + 1][y - 2] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x + 1][y - 2] = obj1;
								Grid[x][y] = piece;
								return false;
							}
							Grid[x + 1][y - 2] = obj1;
							Grid[x][y] = piece;
						}
					}
					if (x - 1 >= 0 && y + 2 < 8)
					{
						obj1 = Grid[x - 1][y + 2];
						if (obj1 == EMPTY_SQUARE || obj1 == BLACK_PAWN || obj1 == BLACK_ROOK || obj1 == BLACK_HORSE || obj1 == BLACK_BISHOP || obj1 == BLACK_QUEEN)
						{
							Grid[x - 1][y + 2] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x - 1][y + 2] = obj1;
								Grid[x][y] = piece;
								return false;
							}
							Grid[x - 1][y + 2] = obj1;
							Grid[x][y] = piece;
						}
					}
					if (x - 1 >= 0 && y - 2 >= 0)
					{
						obj1 = Grid[x - 1][y - 2];
						if (obj1 == EMPTY_SQUARE || obj1 == BLACK_PAWN || obj1 == BLACK_ROOK || obj1 == BLACK_HORSE || obj1 == BLACK_BISHOP || obj1 == BLACK_QUEEN)
						{
							Grid[x - 1][y - 2] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x - 1][y - 2] = obj1;
								Grid[x][y] = piece;
								return false;
							}
							Grid[x - 1][y - 2] = obj1;
							Grid[x][y] = piece;
						}
					}
				}
				if (piece == WHITE_BISHOP || piece == WHITE_QUEEN || piece == WHITE_KING)
				{
					//Check one square diagonal distance if any of these is allowed stop looking
					if (x + 1 < 8 && y + 1 < 8)
					{
						obj1 = Grid[x + 1][y + 1];
						if (obj1 == EMPTY_SQUARE || obj1 == BLACK_PAWN || obj1 == BLACK_ROOK || obj1 == BLACK_HORSE || obj1 == BLACK_BISHOP || obj1 == BLACK_QUEEN)
						{
							Grid[x + 1][y + 1] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x + 1][y + 1] = obj1;
								Grid[x][y] = piece;
								return false;
							}
							Grid[x + 1][y + 1] = obj1;
							Grid[x][y] = piece;
						}
					}
					if (x + 1 < 8 && y - 1 >= 0)
					{
						obj1 = Grid[x + 1][y - 1];
						if (obj1 == EMPTY_SQUARE || obj1 == BLACK_PAWN || obj1 == BLACK_ROOK || obj1 == BLACK_HORSE || obj1 == BLACK_BISHOP || obj1 == BLACK_QUEEN)
						{
							Grid[x + 1][y - 1] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x + 1][y - 1] = obj1;
								Grid[x][y] = piece;
								return false;
							}
							Grid[x + 1][y - 1] = obj1;
							Grid[x][y] = piece;
						}
					}
					if (x - 1 >= 0 && y + 1 < 8)
					{
						obj1 = Grid[x - 1][y + 1];
						if (obj1 == EMPTY_SQUARE || obj1 == BLACK_PAWN || obj1 == BLACK_ROOK || obj1 == BLACK_HORSE || obj1 == BLACK_BISHOP || obj1 == BLACK_QUEEN)
						{
							Grid[x - 1][y + 1] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x - 1][y + 1] = obj1;
								Grid[x][y] = piece;
								return false;
							}
							Grid[x - 1][y + 1] = obj1;
							Grid[x][y] = piece;
						}
					}
					if (x - 1 >= 0 && y - 1 >= 0)
					{
						obj1 = Grid[x - 1][y - 1];
						if (obj1 == EMPTY_SQUARE || obj1 == BLACK_PAWN || obj1 == BLACK_ROOK || obj1 == BLACK_HORSE || obj1 == BLACK_BISHOP || obj1 == BLACK_QUEEN)
						{
							Grid[x - 1][y - 1] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x - 1][y - 1] = obj1;
								Grid[x][y] = piece;
								return false;
							}
							Grid[x - 1][y - 1] = obj1;
							Grid[x][y] = piece;
						}
					}
				}
				if (piece == WHITE_ROOK || piece == WHITE_QUEEN || piece == WHITE_KING)
				{
					//Check one square distance both vertically and horizontally if the move is allowed stop looking
					if (y + 1 < 8)
					{
						obj1 = Grid[x][y + 1];
						if (obj1 == EMPTY_SQUARE || obj1 == BLACK_PAWN || obj1 == BLACK_ROOK || obj1 == BLACK_HORSE || obj1 == BLACK_BISHOP || obj1 == BLACK_QUEEN)
						{
							Grid[x][y] = EMPTY_SQUARE;
							Grid[x][y + 1] = piece;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x][y] = piece;
								Grid[x][y + 1] = obj1;
								return false;
							}
							Grid[x][y] = piece;
							Grid[x][y + 1] = obj1;
						}
					}
					if (y - 1 >= 0)
					{
						obj1 = Grid[x][y - 1];
						if (obj1 == EMPTY_SQUARE || obj1 == BLACK_PAWN || obj1 == BLACK_ROOK || obj1 == BLACK_HORSE || obj1 == BLACK_BISHOP || obj1 == BLACK_QUEEN)
						{
							Grid[x][y] = EMPTY_SQUARE;
							Grid[x][y - 1] = piece;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x][y] = piece;
								Grid[x][y - 1] = obj1;
								return false;
							}
							Grid[x][y] = piece;
							Grid[x][y - 1] = obj1;
						}
					}
					if (x + 1 < 8)
					{
						obj1 = Grid[x + 1][y];
						if (obj1 == EMPTY_SQUARE || obj1 == BLACK_PAWN || obj1 == BLACK_ROOK || obj1 == BLACK_HORSE || obj1 == BLACK_BISHOP || obj1 == BLACK_QUEEN)
						{
							Grid[x][y] = EMPTY_SQUARE;
							Grid[x + 1][y] = piece;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x][y] = piece;
								Grid[x + 1][y] = obj1;
								return false;
							}
							Grid[x][y] = piece;
							Grid[x + 1][y] = obj1;
						}
					}
					if (x - 1 >= 0)
					{
						obj1 = Grid[x - 1][y];
						if (obj1 == EMPTY_SQUARE || obj1 == BLACK_PAWN || obj1 == BLACK_ROOK || obj1 == BLACK_HORSE || obj1 == BLACK_BISHOP || obj1 == BLACK_QUEEN)
						{
							Grid[x][y] = EMPTY_SQUARE;
							Grid[x - 1][y] = piece;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x][y] = piece;
								Grid[x - 1][y] = obj1;
								return false;
							}
							Grid[x][y] = piece;
							Grid[x - 1][y] = obj1;
						}
					}
				}
			}
		}
	}
	else
	{
		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				piece = Grid[x][y];
				if (piece == BLACK_PAWN)
				{
					//check normal movement then  finally check if en passant is posible
					if (Grid[x + 1][y] == EMPTY_SQUARE)
					{
						Grid[x][y] = EMPTY_SQUARE;
						Grid[x + 1][y] = piece;
						if (Player_In_Check(Grid, player) == false)
						{
							Grid[x + 1][y] = EMPTY_SQUARE;
							Grid[x][y] = piece;
							return false;
						}
						Grid[x + 1][y] = EMPTY_SQUARE;
						Grid[x][y] = piece;
					}
					//check capture right + en passant right
					if (y + 1 < 8)
					{
						obj1 = Grid[x + 1][y + 1];
						if (obj1 == WHITE_PAWN || obj1 == WHITE_ROOK || obj1 == WHITE_HORSE || obj1 == WHITE_BISHOP || obj1 == WHITE_QUEEN)
						{
							Grid[x + 1][y + 1] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x][y] = piece;
								Grid[x + 1][y + 1] = obj1;
								return false;
							}
							Grid[x][y] = piece;
							Grid[x + 1][y + 1] = obj1;
						}
						//check en passant
						if (obj1 == EMPTY_SQUARE && x == 4 && (Grid[x][y + 1] == WHITE_PAWN && WHITE_EN_PASSANT == y + 1))
						{
							aux = Grid[x][y + 1];
							Grid[x + 1][y + 1] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							Grid[x][y + 1] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x + 1][y + 1] = EMPTY_SQUARE;
								Grid[x][y] = piece;
								Grid[x][y + 1] = aux;
								return false;
							}
							Grid[x + 1][y + 1] = EMPTY_SQUARE;
							Grid[x][y] = piece;
							Grid[x][y + 1] = aux;
						}
					}
					//check capture left + en passant left
					if (y - 1 > 0)
					{
						obj2 = Grid[x + 1][y - 1];
						if (obj2 == WHITE_PAWN || obj1 == WHITE_ROOK || obj1 == WHITE_HORSE || obj1 == WHITE_BISHOP || obj1 == WHITE_QUEEN)
						{
							Grid[x + 1][y - 1] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x][y] = piece;
								Grid[x + 1][y - 1] = obj2;
								return false;
							}
							Grid[x][y] = piece;
							Grid[x + 1][y - 1] = obj2;
						}
						//check en passant
						if (obj2 == EMPTY_SQUARE && x == 4 && (Grid[x][y - 1] == WHITE_PAWN && WHITE_EN_PASSANT == y - 1))
						{
							aux = Grid[x][y - 1];
							Grid[x + 1][y - 1] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							Grid[x][y - 1] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x + 1][y - 1] = EMPTY_SQUARE;
								Grid[x][y] = piece;
								Grid[x][y - 1] = aux;
								return false;
							}
							Grid[x + 1][y - 1] = EMPTY_SQUARE;
							Grid[x][y] = piece;
							Grid[x][y - 1] = aux;
						}
					}
				}
				if (piece == BLACK_HORSE)
				{
					if (x + 2 < 8 && y + 1 < 8)
					{
						obj1 = Grid[x + 2][y + 1];
						if (obj1 == EMPTY_SQUARE || obj1 == WHITE_PAWN || obj1 == WHITE_ROOK || obj1 == WHITE_HORSE || obj1 == WHITE_BISHOP || obj1 == WHITE_QUEEN)
						{
							Grid[x + 2][y + 1] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x + 2][y + 1] = obj1;
								Grid[x][y] = piece;
								return false;
							}
							Grid[x + 2][y + 1] = obj1;
							Grid[x][y] = piece;
						}
					}
					if (x + 2 < 8 && y - 1 >= 0)
					{
						obj1 = Grid[x + 2][y - 1];
						if (obj1 == EMPTY_SQUARE || obj1 == WHITE_PAWN || obj1 == WHITE_ROOK || obj1 == WHITE_HORSE || obj1 == WHITE_BISHOP || obj1 == WHITE_QUEEN)
						{
							Grid[x + 2][y - 1] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x + 2][y - 1] = obj1;
								Grid[x][y] = piece;
								return false;
							}
							Grid[x + 2][y - 1] = obj1;
							Grid[x][y] = piece;
						}
					}
					if (x - 2 >= 0 && y + 1 < 8)
					{
						obj1 = Grid[x - 2][y + 1];
						if (obj1 == EMPTY_SQUARE || obj1 == WHITE_PAWN || obj1 == WHITE_ROOK || obj1 == WHITE_HORSE || obj1 == WHITE_BISHOP || obj1 == WHITE_QUEEN)
						{
							Grid[x - 2][y + 1] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x - 2][y + 1] = obj1;
								Grid[x][y] = piece;
								return false;
							}
							Grid[x - 2][y + 1] = obj1;
							Grid[x][y] = piece;
						}
					}
					if (x - 2 >= 0 && y - 1 >= 0)
					{
						obj1 = Grid[x - 2][y - 1];
						if (obj1 == EMPTY_SQUARE || obj1 == WHITE_PAWN || obj1 == WHITE_ROOK || obj1 == WHITE_HORSE || obj1 == WHITE_BISHOP || obj1 == WHITE_QUEEN)
						{
							Grid[x - 2][y - 1] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x - 2][y - 1] = obj1;
								Grid[x][y] = piece;
								return false;
							}
							Grid[x - 2][y - 1] = obj1;
							Grid[x][y] = piece;
						}
					}
					if (x + 1 < 8 && y + 2 < 8)
					{
						obj1 = Grid[x + 1][y + 2];
						if (obj1 == EMPTY_SQUARE || obj1 == WHITE_PAWN || obj1 == WHITE_ROOK || obj1 == WHITE_HORSE || obj1 == WHITE_BISHOP || obj1 == WHITE_QUEEN)
						{
							Grid[x + 1][y + 2] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x + 1][y + 2] = obj1;
								Grid[x][y] = piece;
								return false;
							}
							Grid[x + 1][y + 2] = obj1;
							Grid[x][y] = piece;
						}
					}
					if (x + 1 < 8 && y - 2 >= 0)
					{
						obj1 = Grid[x + 1][y - 2];
						if (obj1 == EMPTY_SQUARE || obj1 == WHITE_PAWN || obj1 == WHITE_ROOK || obj1 == WHITE_HORSE || obj1 == WHITE_BISHOP || obj1 == WHITE_QUEEN)
						{
							Grid[x + 1][y - 2] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x + 1][y - 2] = obj1;
								Grid[x][y] = piece;
								return false;
							}
							Grid[x + 1][y - 2] = obj1;
							Grid[x][y] = piece;
						}
					}
					if (x - 1 >= 0 && y + 2 < 8)
					{
						obj1 = Grid[x - 1][y + 2];
						if (obj1 == EMPTY_SQUARE || obj1 == WHITE_PAWN || obj1 == WHITE_ROOK || obj1 == WHITE_HORSE || obj1 == WHITE_BISHOP || obj1 == WHITE_QUEEN)
						{
							Grid[x - 1][y + 2] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x - 1][y + 2] = obj1;
								Grid[x][y] = piece;
								return false;
							}
							Grid[x - 1][y + 2] = obj1;
							Grid[x][y] = piece;
						}
					}
					if (x - 1 >= 0 && y - 2 >= 0)
					{
						obj1 = Grid[x - 1][y - 2];
						if (obj1 == EMPTY_SQUARE || obj1 == WHITE_PAWN || obj1 == WHITE_ROOK || obj1 == WHITE_HORSE || obj1 == WHITE_BISHOP || obj1 == WHITE_QUEEN)
						{
							Grid[x - 1][y - 2] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x - 1][y - 2] = obj1;
								Grid[x][y] = piece;
								return false;
							}
							Grid[x - 1][y - 2] = obj1;
							Grid[x][y] = piece;
						}
					}
				}
				if (piece == BLACK_BISHOP || piece == BLACK_QUEEN || piece == BLACK_KING)
				{
					//Check one square diagonal distance if any of these is allowed stop looking
					if (x + 1 < 8 && y + 1 < 8)
					{
						obj1 = Grid[x + 1][y + 1];
						if (obj1 == EMPTY_SQUARE || obj1 == WHITE_PAWN || obj1 == WHITE_ROOK || obj1 == WHITE_HORSE || obj1 == WHITE_BISHOP || obj1 == WHITE_QUEEN)
						{
							Grid[x + 1][y + 1] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x + 1][y + 1] = obj1;
								Grid[x][y] = piece;
								return false;
							}
							Grid[x + 1][y + 1] = obj1;
							Grid[x][y] = piece;
						}
					}
					if (x + 1 < 8 && y - 1 >= 0)
					{
						obj1 = Grid[x + 1][y - 1];
						if (obj1 == EMPTY_SQUARE || obj1 == WHITE_PAWN || obj1 == WHITE_ROOK || obj1 == WHITE_HORSE || obj1 == WHITE_BISHOP || obj1 == WHITE_QUEEN)
						{
							Grid[x + 1][y - 1] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x + 1][y - 1] = obj1;
								Grid[x][y] = piece;
								return false;
							}
							Grid[x + 1][y - 1] = obj1;
							Grid[x][y] = piece;
						}
					}
					if (x - 1 >= 0 && y + 1 < 8)
					{
						obj1 = Grid[x - 1][y + 1];
						if (obj1 == EMPTY_SQUARE || obj1 == WHITE_PAWN || obj1 == WHITE_ROOK || obj1 == WHITE_HORSE || obj1 == WHITE_BISHOP || obj1 == WHITE_QUEEN)
						{
							Grid[x - 1][y + 1] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x - 1][y + 1] = obj1;
								Grid[x][y] = piece;
								return false;
							}
							Grid[x - 1][y + 1] = obj1;
							Grid[x][y] = piece;
						}
					}
					if (x - 1 >= 0 && y - 1 >= 0)
					{
						obj1 = Grid[x - 1][y - 1];
						if (obj1 == EMPTY_SQUARE || obj1 == WHITE_PAWN || obj1 == WHITE_ROOK || obj1 == WHITE_HORSE || obj1 == WHITE_BISHOP || obj1 == WHITE_QUEEN)
						{
							Grid[x - 1][y - 1] = piece;
							Grid[x][y] = EMPTY_SQUARE;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x - 1][y - 1] = obj1;
								Grid[x][y] = piece;
								return false;
							}
							Grid[x - 1][y - 1] = obj1;
							Grid[x][y] = piece;
						}
					}
				}
				if (piece == BLACK_ROOK || piece == BLACK_QUEEN || piece == BLACK_KING)
				{
					//Check one square distance both vertically and horizontally if the move is allowed stop looking
					if (y + 1 < 8)
					{
						obj1 = Grid[x][y + 1];
						if (obj1 == EMPTY_SQUARE || obj1 == WHITE_PAWN || obj1 == WHITE_ROOK || obj1 == WHITE_HORSE || obj1 == WHITE_BISHOP || obj1 == WHITE_QUEEN)
						{
							Grid[x][y] = EMPTY_SQUARE;
							Grid[x][y + 1] = piece;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x][y] = piece;
								Grid[x][y + 1] = obj1;
								return false;
							}
							Grid[x][y] = piece;
							Grid[x][y + 1] = obj1;
						}
					}
					if (y - 1 >= 0)
					{
						obj1 = Grid[x][y - 1];
						if (obj1 == EMPTY_SQUARE || obj1 == WHITE_PAWN || obj1 == WHITE_ROOK || obj1 == WHITE_HORSE || obj1 == WHITE_BISHOP || obj1 == WHITE_QUEEN)
						{
							Grid[x][y] = EMPTY_SQUARE;
							Grid[x][y - 1] = piece;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x][y] = piece;
								Grid[x][y - 1] = obj1;
								return false;
							}
							Grid[x][y] = piece;
							Grid[x][y - 1] = obj1;
						}
					}
					if (x + 1 < 8)
					{
						obj1 = Grid[x + 1][y];
						if (obj1 == EMPTY_SQUARE || obj1 == WHITE_PAWN || obj1 == WHITE_ROOK || obj1 == WHITE_HORSE || obj1 == WHITE_BISHOP || obj1 == WHITE_QUEEN)
						{
							Grid[x][y] = EMPTY_SQUARE;
							Grid[x + 1][y] = piece;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x][y] = piece;
								Grid[x + 1][y] = obj1;
								return false;
							}
							Grid[x][y] = piece;
							Grid[x + 1][y] = obj1;
						}
					}
					if (x - 1 >= 0)
					{
						obj1 = Grid[x - 1][y];
						if (obj1 == EMPTY_SQUARE || obj1 == WHITE_PAWN || obj1 == WHITE_ROOK || obj1 == WHITE_HORSE || obj1 == WHITE_BISHOP || obj1 == WHITE_QUEEN)
						{
							Grid[x][y] = EMPTY_SQUARE;
							Grid[x - 1][y] = piece;
							if (Player_In_Check(Grid, player) == false)
							{
								Grid[x][y] = piece;
								Grid[x - 1][y] = obj1;
								return false;
							}
							Grid[x][y] = piece;
							Grid[x - 1][y] = obj1;
						}
					}
				}
			}
		}
	}
	return true;
}

bool Check_Win(char Grid[][8], char player)
{
	// Make the opponent checkmate until king cant move
	string line;
	static int count_WHITE_CHECK = 0;
	static int count_BLACK_CHECK = 0;
	if (Player_In_Check(Grid, player) == true)
	{
        string line;

        ifstream myFile("Checkmates.txt");
        if (myFile.is_open()) {
            myFile >> count_WHITE_CHECK;
            myFile >> count_BLACK_CHECK;
            myFile.close();

            ofstream outFile("Checkmates.txt");
            if (player == WHITE_PLAYER) {
                count_WHITE_CHECK++;
                outFile << "White player (UPPERCASE/ALL CAPS) is in CHECK! -> Total Checks: " << count_WHITE_CHECK << endl;
                cout << "White player (UPPERCASE/ALL CAPS) is in CHECK! " << endl;
            } 
            else if (player == BLACK_PLAYER) {
                count_BLACK_CHECK++;
                outFile << "Black player (LOWERCASE/ALL CAPS) is in CHECK! -> Total Checks: " << count_BLACK_CHECK << endl;
                cout << "Black player (LOWERCASE/ALL CAPS) is in CHECK! " << endl;
            }
            outFile.close();
        } 
        else {
            cout << "Error: Unable to open file for reading." << endl;
        }

		//Anlaisis Checkmate
		//look all king moves and all the other pieces moves to see if they can cover the check
		int x, y, s, t;
		char pos, prev;
		if (player == WHITE_PLAYER)
		{
			//First locate the king
			for (x = 0; x < 8; x++)
				for (y = 0; y < 8; y++)
					if (Grid[x][y] == BLACK_KING)
						goto found;
		found:
			//Check King moves
			if (x + 1 < 8)  // Checks if moving one square to the right
			{
				pos = Grid[x + 1][y];
				if (pos != BLACK_BISHOP && pos != BLACK_HORSE && pos != BLACK_ROOK && pos != BLACK_QUEEN && pos != BLACK_PAWN)
				{
					Grid[x + 1][y] = BLACK_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x + 1][y] = pos;
						Grid[x][y] = BLACK_KING;
						return false;
					}
					Grid[x + 1][y] = pos;
					Grid[x][y] = BLACK_KING;
				}
			}
			if (x + 1 < 8 && y - 1 >= 0)  // Checks if moving one square diagonally to the bottom-right
			{
				pos = Grid[x + 1][y - 1];
				if (pos != BLACK_BISHOP && pos != BLACK_HORSE && pos != BLACK_ROOK && pos != BLACK_QUEEN && pos != BLACK_PAWN)
				{
					Grid[x + 1][y - 1] = BLACK_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x + 1][y - 1] = pos;
						Grid[x][y] = BLACK_KING;
						return false;
					}
					Grid[x + 1][y - 1] = pos;
					Grid[x][y] = BLACK_KING;
				}
			}
			if (x + 1 < 8 && y + 1 < 8)  // Checks if moving one square diagonally to the top-right
			{
				pos = Grid[x + 1][y + 1];
				if (pos != BLACK_BISHOP && pos != BLACK_HORSE && pos != BLACK_ROOK && pos != BLACK_QUEEN && pos != BLACK_PAWN)
				{
					Grid[x + 1][y + 1] = BLACK_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x + 1][y + 1] = pos;
						Grid[x][y] = BLACK_KING;
						return false;
					}
					Grid[x + 1][y + 1] = pos;
					Grid[x][y] = BLACK_KING;
				}
			}
			if (y + 1 < 8)  //  Checks if moving one square upwards
			{
				pos = Grid[x][y + 1];
				if (pos != BLACK_BISHOP && pos != BLACK_HORSE && pos != BLACK_ROOK && pos != BLACK_QUEEN && pos != BLACK_PAWN)
				{
					Grid[x][y + 1] = BLACK_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x][y + 1] = pos;
						Grid[x][y] = BLACK_KING;
						return false;
					}
					Grid[x][y + 1] = pos;
					Grid[x][y] = BLACK_KING;
				}
			}
			if (y - 1 >= 0)  // Checks if moving one square downwards
			{
				pos = Grid[x][y - 1];
				if (pos != BLACK_BISHOP && pos != BLACK_HORSE && pos != BLACK_ROOK && pos != BLACK_QUEEN && pos != BLACK_PAWN)
				{
					Grid[x][y - 1] = BLACK_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x][y - 1] = pos;
						Grid[x][y] = BLACK_KING;
						return false;
					}
					Grid[x][y - 1] = pos;
					Grid[x][y] = BLACK_KING;
				}
			}
			if (x - 1 >= 0)  //  Checks if moving one square to the left 
			{
				pos = Grid[x - 1][y];
				if (pos != BLACK_BISHOP && pos != BLACK_HORSE && pos != BLACK_ROOK && pos != BLACK_QUEEN && pos != BLACK_PAWN)
				{
					Grid[x - 1][y] = BLACK_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x - 1][y] = pos;
						Grid[x][y] = BLACK_KING;
						return false;
					}
					Grid[x - 1][y] = pos;
					Grid[x][y] = BLACK_KING;
				}
			}
			if (x - 1 >= 0 && y - 1 >= 0)  // Checks if moving one square diagonally to the bottom-left 
			{
				pos = Grid[x - 1][y - 1];
				if (pos != BLACK_BISHOP && pos != BLACK_HORSE && pos != BLACK_ROOK && pos != BLACK_QUEEN && pos != BLACK_PAWN)
				{
					Grid[x - 1][y - 1] = BLACK_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x - 1][y - 1] = pos;
						Grid[x][y] = BLACK_KING;
						return false;
					}
					Grid[x - 1][y - 1] = pos;
					Grid[x][y] = BLACK_KING;
				}
			}
			if (x - 1 >= 0 && y + 1 < 8)  // Checks if moving one square diagonally to the top-left
			{
				pos = Grid[x - 1][y + 1];
				if (pos != BLACK_BISHOP && pos != BLACK_HORSE && pos != BLACK_ROOK && pos != BLACK_QUEEN && pos != BLACK_PAWN)
				{
					Grid[x - 1][y + 1] = BLACK_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x - 1][y + 1] = pos;
						Grid[x][y] = BLACK_KING;
						return false;
					}
					Grid[x - 1][y + 1] = pos;
					Grid[x][y] = BLACK_KING;
				}
			}
			//Check the movement of the other pieces
			for (int j = 0; j < 8; j++)
			{
				for (int q = 0; q < 8; q++)
				{
					if (Grid[j][q] != EMPTY_SQUARE)
					{
						if (Grid[j][q] == BLACK_PAWN)
						{
							//Forward Pawn Move (haven t checked if double starting move works)
							if (j + 1 < 8 && Grid[j + 1][q] == EMPTY_SQUARE)
							{
								Grid[j + 1][q] = BLACK_PAWN;
								Grid[j][q] = EMPTY_SQUARE;
								if (Player_In_Check(Grid, player) == false)
								{
									Grid[j + 1][q] = EMPTY_SQUARE;
									Grid[j][q] = BLACK_PAWN;
									return false;
								}
								Grid[j + 1][q] = EMPTY_SQUARE;
								Grid[j][q] = BLACK_PAWN;
							}
							//Capture left
							if (j + 1 < 8 && q - 1 >= 0)
							{
								pos = Grid[j + 1][q - 1];
								if (pos == WHITE_BISHOP || pos == WHITE_HORSE || pos == WHITE_QUEEN || pos == WHITE_PAWN)
								{
									Grid[j + 1][q - 1] = BLACK_PAWN;
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j + 1][q - 1] = pos;
										Grid[j][q] = BLACK_PAWN;
										return false;
									}
									Grid[j + 1][q - 1] = pos;
									Grid[j][q] = BLACK_PAWN;
								}
							}
							//Capture right
							if (j + 1 < 8 && q + 1 < 8)
							{
								pos = Grid[j + 1][q + 1];
								if (pos == WHITE_BISHOP || pos == WHITE_HORSE || pos == WHITE_QUEEN || pos == WHITE_PAWN)
								{
									Grid[j + 1][q + 1] = BLACK_PAWN;
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j + 1][q + 1] = pos;
										Grid[j][q] = BLACK_PAWN;
										return false;
									}
									Grid[j + 1][q + 1] = pos;
									Grid[j][q] = BLACK_PAWN;
								}
							}

						}
						else if (Grid[j][q] == BLACK_HORSE)
						{
							if (j + 2 < 8 && q + 1 < 8)  // Checks if moving two squares vertically downwards and one square to the right
							{
								pos = Grid[j + 2][q + 1];
								if (pos != BLACK_BISHOP && pos != BLACK_HORSE && pos != BLACK_ROOK && pos != BLACK_QUEEN && pos != BLACK_PAWN && pos != BLACK_KING)
								{
									Grid[j + 2][q + 1] = BLACK_HORSE;
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j + 2][q + 1] = pos;
										Grid[j][q] = BLACK_HORSE;
										return false;
									}
									Grid[j + 2][q + 1] = pos;
									Grid[j][q] = BLACK_HORSE;
								}
							}
							if (j + 2 < 8 && q - 1 >= 0)  // Checks if moving two squares vertically downwards and one square to the left
							{
								pos = Grid[j + 2][q - 1];
								if (pos != BLACK_BISHOP && pos != BLACK_HORSE && pos != BLACK_ROOK && pos != BLACK_QUEEN && pos != BLACK_PAWN && pos != BLACK_KING)
								{
									Grid[j + 2][q - 1] = BLACK_HORSE;
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j + 2][q - 1] = pos;
										Grid[j][q] = BLACK_PAWN;
										return false;
									}
									Grid[j + 2][q - 1] = pos;
									Grid[j][q] = BLACK_PAWN;
								}
							}
							if (j - 2 >= 0 && q + 1 < 8)  // Checks if moving two squares vertically upwards and one square to the right
							{
								pos = Grid[j - 2][q + 1];
								if (pos != BLACK_BISHOP && pos != BLACK_HORSE && pos != BLACK_ROOK && pos != BLACK_QUEEN && pos != BLACK_PAWN && pos != BLACK_KING)
								{
									Grid[j - 2][q + 1] = BLACK_HORSE;
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j - 2][q + 1] = pos;
										Grid[j][q] = BLACK_HORSE;
										return false;
									}
									Grid[j - 2][q + 1] = pos;
									Grid[j][q] = BLACK_HORSE;
								}
							}
							if (j - 2 >= 0 && q - 1 >= 0)  // Checks if moving two squares vertically upwards and one square to the left
							{
								pos = Grid[j - 2][q - 1];
								if (pos != BLACK_BISHOP && pos != BLACK_HORSE && pos != BLACK_ROOK && pos != BLACK_QUEEN && pos != BLACK_PAWN && pos != BLACK_KING)
								{
									Grid[j - 2][q - 1] = BLACK_HORSE;
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j - 2][q - 1] = pos;
										Grid[j][q] = BLACK_HORSE;
										return false;
									}
									Grid[j - 2][q - 1] = pos;
									Grid[j][q] = BLACK_HORSE;
								}
							}
							if (j + 1 < 8 && q + 2 < 8)  // Checks if moving one square vertically downwards and two squares to the right 
							{
								pos = Grid[j + 1][q + 2];
								if (pos != BLACK_BISHOP && pos != BLACK_HORSE && pos != BLACK_ROOK && pos != BLACK_QUEEN && pos != BLACK_PAWN && pos != BLACK_KING)
								{
									Grid[j + 1][q + 2] = BLACK_HORSE;
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j + 1][q + 2] = pos;
										Grid[j][q] = BLACK_HORSE;
										return false;
									}
									Grid[j + 1][q + 2] = pos;
									Grid[j][q] = BLACK_HORSE;
								}
							}
							if (j + 1 < 8 && q - 2 >= 0)  // Checks if moving one square vertically downwards and two squares to the left
							{
								pos = Grid[j + 1][q - 2];
								if (pos != BLACK_BISHOP && pos != BLACK_HORSE && pos != BLACK_ROOK && pos != BLACK_QUEEN && pos != BLACK_PAWN && pos != BLACK_KING)
								{
									Grid[j + 1][q - 2] = BLACK_HORSE;
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j + 1][q - 2] = pos;
										Grid[j][q] = BLACK_HORSE;
										return false;
									}
									Grid[j + 1][q - 2] = pos;
									Grid[j][q] = BLACK_HORSE;
								}
							}
							if (j - 1 >= 0 && q + 2 < 8)  //  Checks if moving one square vertically upwards and two squares to the right
							{
								pos = Grid[j - 1][q + 2];
								if (pos != BLACK_BISHOP && pos != BLACK_HORSE && pos != BLACK_ROOK && pos != BLACK_QUEEN && pos != BLACK_PAWN && pos != BLACK_KING)
								{
									Grid[j - 1][q + 2] = BLACK_HORSE;
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j - 1][q + 2] = pos;
										Grid[j][q] = BLACK_HORSE;
										return false;
									}
									Grid[j - 1][q + 2] = pos;
									Grid[j][q] = BLACK_HORSE;
								}
							}
							if (j - 1 >= 0 && q - 2 >= 0)   // Checks if moving one square vertically upwards and two squares to the left
							{
								pos = Grid[j - 1][q - 2];
								if (pos != BLACK_BISHOP && pos != BLACK_HORSE && pos != BLACK_ROOK && pos != BLACK_QUEEN && pos != BLACK_PAWN && pos != BLACK_KING)
								{
									Grid[j - 1][q - 2] = BLACK_HORSE;
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j - 1][q - 2] = pos;
										Grid[j][q] = BLACK_HORSE;
										return false;
									}
									Grid[j - 1][q - 2] = pos;
									Grid[j][q] = BLACK_HORSE;
								}
							}
						}
						else if (Grid[j][q] == BLACK_BISHOP || Grid[j][q] == BLACK_QUEEN)
						{
							//Look on all directions
							//Search TOP Left x-- y--
							s = q - 1;
							t = j - 1;
							if (t >= 0 && s >= 0)
							{
								while (t >= 0 && s >= 0)
								{
									pos = Grid[t][s];
									prev = Grid[j][q];
									if (pos != EMPTY_SQUARE && ((abs(t - x) != abs(s - y)) && x != t && y != s))
										break;
									else if ((pos == EMPTY_SQUARE || pos == WHITE_BISHOP || pos == WHITE_HORSE || pos == WHITE_QUEEN || pos == WHITE_PAWN) && ((abs(t - x) == abs(s - y)) || x == t || y == s))
									{
										Grid[t][s] = Grid[j][q];
										Grid[j][q] = EMPTY_SQUARE;
										if (Player_In_Check(Grid, player) == false)
										{
											Grid[t][s] = pos;
											Grid[j][q] = prev;
											return false;
										}
										Grid[t][s] = pos;
										Grid[j][q] = prev;
									}
									s--;
									t--;
								}
							}
							//Search BOTTOM Right x++ y++
							s = q + 1;
							t = j + 1;
							if (t < 8 && s < 8)
							{
								while (t < 8 && s < 8)
								{
									pos = Grid[t][s];
									prev = Grid[j][q];
									if (pos != EMPTY_SQUARE && ((abs(t - x) != abs(s - y)) || x == t || y == s))
										break;
									else if ((pos == EMPTY_SQUARE || pos == WHITE_BISHOP || pos == WHITE_HORSE || pos == WHITE_QUEEN || pos == WHITE_PAWN) && ((abs(t - x) == abs(s - y)) || x == t || y == s))
									{
										Grid[t][s] = Grid[j][q];
										Grid[j][q] = EMPTY_SQUARE;
										if (Player_In_Check(Grid, player) == false)
										{
											Grid[t][s] = pos;
											Grid[j][q] = prev;
											return false;
										}
										Grid[t][s] = pos;
										Grid[j][q] = prev;
									}
									else break;
									s++;
									t++;
								}
							}
							//Search BOTTOM Left x++ y--
							s = q - 1;
							t = j + 1;
							if (s >= 0 && t < 8)
							{
								while (s >= 0 && t < 8)
								{
									pos = Grid[t][s];
									prev = Grid[j][q];
									if (pos != EMPTY_SQUARE && ((abs(t - x) != abs(s - y)) || x == t || y == s))
										break;
									else if ((pos == EMPTY_SQUARE || pos == WHITE_BISHOP || pos == WHITE_HORSE || pos == WHITE_QUEEN || pos == WHITE_PAWN) && ((abs(t - x) == abs(s - y)) || x == t || y == s))
									{
										Grid[t][s] = Grid[j][q];
										Grid[j][q] = EMPTY_SQUARE;
										if (Player_In_Check(Grid, player) == false)
										{
											Grid[t][s] = pos;
											Grid[j][q] = prev;
											return false;
										}
										Grid[t][s] = pos;
										Grid[j][q] = prev;
									}
									else break;
									s--;
									t++;
								}
							}
							//Search top Right x-- y++
							s = q + 1;
							t = j - 1;
							if (s < 8 && t >= 0)
							{
								while (s < 8 && t >= 0)
								{
									pos = Grid[t][s];
									prev = Grid[j][q];
									if (pos != EMPTY_SQUARE && ((abs(t - x) != abs(s - y)) || x == t || y == s))
										break;
									else if ((pos == EMPTY_SQUARE || pos == WHITE_BISHOP || pos == WHITE_HORSE || pos == WHITE_QUEEN || pos == WHITE_PAWN) && ((abs(t - x) == abs(s - y)) || x == t || y == s))
									{
										Grid[t][s] = Grid[j][q];
										Grid[j][q] = EMPTY_SQUARE;
										if (Player_In_Check(Grid, player) == false)
										{
											Grid[t][s] = pos;
											Grid[j][q] = prev;
											return false;
										}
										Grid[t][s] = pos;
										Grid[j][q] = prev;
									}
									else break;
									s++;
									t--;
								}
							}
						}
						if (Grid[j][q] == BLACK_ROOK || Grid[j][q] == BLACK_QUEEN)
						{
							//Look Right
							for (int t = q + 1; t < 8; t++)
							{
								pos = Grid[j][t];
								prev = Grid[j][q];
								if (pos != EMPTY_SQUARE && ((abs(j - x) != abs(t - y)) || x == j || y == t))
									break;
								else if ((pos == EMPTY_SQUARE || pos == WHITE_BISHOP || pos == WHITE_HORSE || pos == WHITE_QUEEN || pos == WHITE_PAWN) && ((abs(j - x) != abs(t - y)) || x == j || y == t))
								{
									Grid[j][t] = Grid[j][q];
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j][t] = pos;
										Grid[j][q] = prev;
										return false;
									}
									Grid[j][t] = pos;
									Grid[j][q] = prev;
								}
								else break;
							}
							//Look Left
							for (int t = q - 1; t >= 0; t--)
							{
								pos = Grid[j][t];
								prev = Grid[j][q];
								if (pos != EMPTY_SQUARE && ((abs(j - x) != abs(t - y)) || x == j || y == t))
									break;
								else if ((pos == EMPTY_SQUARE || pos == WHITE_BISHOP || pos == WHITE_HORSE || pos == WHITE_QUEEN || pos == WHITE_PAWN) && ((abs(j - x) != abs(t - y)) || x == j || y == t))
								{
									Grid[j][t] = Grid[j][q];
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j][t] = pos;
										Grid[j][q] = prev;
										return false;
									}
									Grid[j][t] = pos;
									Grid[j][q] = prev;
								}
								else break;
							}
							//Look Up
							for (int t = j + 1; t < 8; t++)
							{
								pos = Grid[t][q];
								prev = Grid[j][q];
								if (pos != EMPTY_SQUARE && ((abs(j - x) != abs(t - y)) || x == t || y == q))
									break;
								else if ((pos == EMPTY_SQUARE || pos == WHITE_BISHOP || pos == WHITE_HORSE || pos == WHITE_QUEEN || pos == WHITE_PAWN) && ((abs(j - x) != abs(t - y)) || x == t || y == q))
								{
									Grid[t][q] = Grid[j][q];
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[t][q] = pos;
										Grid[j][q] = prev;
										return false;
									}
									Grid[t][q] = pos;
									Grid[j][q] = prev;
								}
								else break;
							}
							//Look Down
							for (int t = j - 1; t >= 0; t--)
							{
								pos = Grid[t][q];
								prev = Grid[j][q];
								if (pos != EMPTY_SQUARE && ((abs(j - x) != abs(t - y)) || x == t || y == q))
									break;
								else if ((pos == EMPTY_SQUARE || pos == WHITE_BISHOP || pos == WHITE_HORSE || pos == WHITE_QUEEN || pos == WHITE_PAWN) && ((abs(j - x) != abs(t - y)) || x == t || y == q))
								{
									Grid[t][q] = Grid[j][q];
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[t][q] = pos;
										Grid[j][q] = prev;
										return false;
									}
									Grid[t][q] = pos;
									Grid[j][q] = prev;
								}
								else break;
							}
						}
					}
				}
			}
		}
		else if (player == BLACK_PLAYER)
		{
			for (x = 7; x >= 0; x--)
				for (y = 0; y < 8; y++)
					if (Grid[x][y] == WHITE_KING)
						goto found2;
		found2:
			//Check King moves
			if (x + 1 < 8)
			{
				pos = Grid[x + 1][y];
				if (pos != WHITE_BISHOP && pos != WHITE_HORSE && pos != WHITE_ROOK && pos != WHITE_QUEEN && pos != WHITE_PAWN)
				{
					Grid[x + 1][y] = WHITE_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x + 1][y] = pos;
						Grid[x][y] = WHITE_KING;
						return false;
					}
					Grid[x + 1][y] = pos;
					Grid[x][y] = WHITE_KING;
				}
			}
			if (x + 1 < 8 && y - 1 >= 0)
			{
				pos = Grid[x + 1][y - 1];
				if (pos != WHITE_BISHOP && pos != WHITE_HORSE && pos != WHITE_ROOK && pos != WHITE_QUEEN && pos != WHITE_PAWN)
				{
					Grid[x + 1][y - 1] = WHITE_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x + 1][y - 1] = pos;
						Grid[x][y] = WHITE_KING;
						return false;
					}
					Grid[x + 1][y - 1] = pos;
					Grid[x][y] = WHITE_KING;
				}
			}
			if (x + 1 < 8 && y + 1 < 8)
			{
				pos = Grid[x + 1][y + 1];
				if (pos != WHITE_BISHOP && pos != WHITE_HORSE && pos != WHITE_ROOK && pos != WHITE_QUEEN && pos != WHITE_PAWN)
				{
					Grid[x + 1][y + 1] = WHITE_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x + 1][y + 1] = pos;
						Grid[x][y] = WHITE_KING;
						return false;
					}
					Grid[x + 1][y + 1] = pos;
					Grid[x][y] = WHITE_KING;
				}
			}
			if (y + 1 < 8)
			{
				pos = Grid[x][y + 1];
				if (pos != WHITE_BISHOP && pos != WHITE_HORSE && pos != WHITE_ROOK && pos != WHITE_QUEEN && pos != WHITE_PAWN)
				{
					Grid[x][y + 1] = WHITE_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x][y + 1] = pos;
						Grid[x][y] = WHITE_KING;
						return false;
					}
					Grid[x][y + 1] = pos;
					Grid[x][y] = WHITE_KING;
				}
			}
			if (y - 1 >= 0)
			{
				pos = Grid[x][y - 1];
				if (pos != WHITE_BISHOP && pos != WHITE_HORSE && pos != WHITE_ROOK && pos != WHITE_QUEEN && pos != WHITE_PAWN)
				{
					Grid[x][y - 1] = WHITE_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x][y - 1] = pos;
						Grid[x][y] = WHITE_KING;
						return false;
					}
					Grid[x][y - 1] = pos;
					Grid[x][y] = WHITE_KING;
				}
			}
			if (x - 1 >= 0)
			{
				pos = Grid[x - 1][y];
				if (pos != WHITE_BISHOP && pos != WHITE_HORSE && pos != WHITE_ROOK && pos != WHITE_QUEEN && pos != WHITE_PAWN)
				{
					Grid[x - 1][y] = WHITE_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x - 1][y] = pos;
						Grid[x][y] = WHITE_KING;
						return false;
					}
					Grid[x - 1][y] = pos;
					Grid[x][y] = WHITE_KING;
				}
			}
			if (x - 1 >= 0 && y - 1 >= 0)
			{
				pos = Grid[x - 1][y - 1];
				if (pos != WHITE_BISHOP && pos != WHITE_HORSE && pos != WHITE_ROOK && pos != WHITE_QUEEN && pos != WHITE_PAWN)
				{
					Grid[x - 1][y - 1] = WHITE_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x - 1][y - 1] = pos;
						Grid[x][y] = WHITE_KING;
						return false;
					}
					Grid[x - 1][y - 1] = pos;
					Grid[x][y] = WHITE_KING;
				}
			}
			if (x - 1 >= 0 && y + 1 < 8)
			{
				pos = Grid[x - 1][y + 1];
				if (pos != WHITE_BISHOP && pos != WHITE_HORSE && pos != WHITE_ROOK && pos != WHITE_QUEEN && pos != WHITE_PAWN)
				{
					Grid[x - 1][y + 1] = WHITE_KING;
					Grid[x][y] = EMPTY_SQUARE;
					if (Player_In_Check(Grid, player) == false)
					{
						Grid[x - 1][y + 1] = pos;
						Grid[x][y] = WHITE_KING;
						return false;
					}
					Grid[x - 1][y + 1] = pos;
					Grid[x][y] = WHITE_KING;
				}
			}
			//Check the movement of the other pieces
			for (int j = 0; j < 8; j++)
			{
				for (int q = 0; q < 8; q++)
				{
					if (Grid[j][q] != EMPTY_SQUARE)
					{
						if (Grid[j][q] == WHITE_PAWN)
						{
							//Forward Pawn Move (haven t checked if double starting move works)
							if (j + 1 < 8 && Grid[j + 1][q] == EMPTY_SQUARE)
							{
								Grid[j + 1][q] = WHITE_PAWN;
								Grid[j][q] = EMPTY_SQUARE;
								if (Player_In_Check(Grid, player) == false)
								{
									Grid[j + 1][q] = EMPTY_SQUARE;
									Grid[j][q] = WHITE_PAWN;
									return false;
								}
								Grid[j + 1][q] = EMPTY_SQUARE;
								Grid[j][q] = WHITE_PAWN;
							}
							//Capture left
							if (j + 1 < 8 && q - 1 >= 0)
							{
								pos = Grid[j + 1][q - 1];
								if (pos == BLACK_BISHOP || pos == BLACK_HORSE || pos == BLACK_QUEEN || pos == BLACK_PAWN)
								{
									Grid[j + 1][q - 1] = WHITE_PAWN;
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j + 1][q - 1] = pos;
										Grid[j][q] = WHITE_PAWN;
										return false;
									}
									Grid[j + 1][q - 1] = pos;
									Grid[j][q] = WHITE_PAWN;
								}
							}
							//Capture right
							if (j + 1 < 8 && q + 1 < 8)
							{
								pos = Grid[j + 1][q + 1];
								if (pos == BLACK_BISHOP || pos == BLACK_HORSE || pos == BLACK_QUEEN || pos == BLACK_PAWN)
								{
									Grid[j + 1][q + 1] = WHITE_PAWN;
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j + 1][q + 1] = pos;
										Grid[j][q] = WHITE_PAWN;
										return false;
									}
									Grid[j + 1][q + 1] = pos;
									Grid[j][q] = WHITE_PAWN;
								}
							}
						}
						else if (Grid[j][q] == WHITE_HORSE)
						{
							if (j + 2 < 8 && q + 1 < 8)
							{
								pos = Grid[j + 2][q + 1];
								if (pos != WHITE_BISHOP && pos != WHITE_HORSE && pos != WHITE_ROOK && pos != WHITE_QUEEN && pos != WHITE_PAWN && pos != WHITE_KING)
								{
									Grid[j + 2][q + 1] = WHITE_HORSE;
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j + 2][q + 1] = pos;
										Grid[j][q] = WHITE_HORSE;
										return false;
									}
									Grid[j + 2][q + 1] = pos;
									Grid[j][q] = WHITE_HORSE;
								}
							}
							if (j + 2 < 8 && q - 1 >= 0)
							{
								pos = Grid[j + 2][q - 1];
								if (pos != WHITE_BISHOP && pos != WHITE_HORSE && pos != WHITE_ROOK && pos != WHITE_QUEEN && pos != WHITE_PAWN && pos != WHITE_KING)
								{
									Grid[j + 2][q - 1] = WHITE_HORSE;
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j + 2][q - 1] = pos;
										Grid[j][q] = WHITE_PAWN;
										return false;
									}
									Grid[j + 2][q - 1] = pos;
									Grid[j][q] = WHITE_PAWN;
								}
							}
							if (j - 2 >= 0 && q + 1 < 8)
							{
								pos = Grid[j - 2][q + 1];
								if (pos != WHITE_BISHOP && pos != WHITE_HORSE && pos != WHITE_ROOK && pos != WHITE_QUEEN && pos != WHITE_PAWN && pos != WHITE_KING)
								{
									Grid[j - 2][q + 1] = WHITE_HORSE;
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j - 2][q + 1] = pos;
										Grid[j][q] = WHITE_HORSE;
										return false;
									}
									Grid[j - 2][q + 1] = pos;
									Grid[j][q] = WHITE_HORSE;
								}
							}
							if (j - 2 >= 0 && q - 1 >= 0)
							{
								pos = Grid[j - 2][q - 1];
								if (pos != WHITE_BISHOP && pos != WHITE_HORSE && pos != WHITE_ROOK && pos != WHITE_QUEEN && pos != WHITE_PAWN && pos != WHITE_KING)
								{
									Grid[j - 2][q - 1] = WHITE_HORSE;
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j - 2][q - 1] = pos;
										Grid[j][q] = WHITE_HORSE;
										return false;
									}
									Grid[j - 2][q - 1] = pos;
									Grid[j][q] = WHITE_HORSE;
								}
							}
							if (j + 1 < 8 && q + 2 < 8)
							{
								pos = Grid[j + 1][q + 2];
								if (pos != WHITE_BISHOP && pos != WHITE_HORSE && pos != WHITE_ROOK && pos != WHITE_QUEEN && pos != WHITE_PAWN && pos != WHITE_KING)
								{
									Grid[j + 1][q + 2] = WHITE_HORSE;
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j + 1][q + 2] = pos;
										Grid[j][q] = WHITE_HORSE;
										return false;
									}
									Grid[j + 1][q + 2] = pos;
									Grid[j][q] = WHITE_HORSE;
								}
							}
							if (j + 1 < 8 && q - 2 >= 0)
							{
								pos = Grid[j + 1][q - 2];
								if (pos != WHITE_BISHOP && pos != WHITE_HORSE && pos != WHITE_ROOK && pos != WHITE_QUEEN && pos != WHITE_PAWN && pos != WHITE_KING)
								{
									Grid[j + 1][q - 2] = WHITE_HORSE;
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j + 1][q - 2] = pos;
										Grid[j][q] = WHITE_HORSE;
										return false;
									}
									Grid[j + 1][q - 2] = pos;
									Grid[j][q] = WHITE_HORSE;
								}
							}
							if (j - 1 >= 0 && q + 2 < 8)
							{
								pos = Grid[j - 1][q + 2];
								if (pos != WHITE_BISHOP && pos != WHITE_HORSE && pos != WHITE_ROOK && pos != WHITE_QUEEN && pos != WHITE_PAWN && pos != WHITE_KING)
								{
									Grid[j - 1][q + 2] = WHITE_HORSE;
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j - 1][q + 2] = pos;
										Grid[j][q] = WHITE_HORSE;
										return false;
									}
									Grid[j - 1][q + 2] = pos;
									Grid[j][q] = WHITE_HORSE;
								}
							}
							if (j - 1 >= 0 && q - 2 >= 0)
							{
								pos = Grid[j - 1][q - 2];
								if (pos != WHITE_BISHOP && pos != WHITE_HORSE && pos != WHITE_ROOK && pos != WHITE_QUEEN && pos != WHITE_PAWN && pos != WHITE_KING)
								{
									Grid[j - 1][q - 2] = WHITE_HORSE;
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j - 1][q - 2] = pos;
										Grid[j][q] = WHITE_HORSE;
										return false;
									}
									Grid[j - 1][q - 2] = pos;
									Grid[j][q] = WHITE_HORSE;
								}
							}
						}
						else if (Grid[j][q] == WHITE_BISHOP || Grid[j][q] == WHITE_QUEEN)
						{
							//Look on all directions
							//Search TOP Left x-- y--
							s = q - 1;
							t = j - 1;
							if (t >= 0 && s >= 0)
							{
								while (t >= 0 && s >= 0)
								{
									pos = Grid[t][s];
									prev = Grid[j][q];
									if (pos != EMPTY_SQUARE && ((abs(t - x) != abs(s - y)) && x != t && y != s))
										break;
									else if ((pos == EMPTY_SQUARE || pos == BLACK_BISHOP || pos == BLACK_HORSE || pos == BLACK_QUEEN || pos == BLACK_PAWN) && ((abs(t - x) == abs(s - y)) || x == t || y == s))
									{
										Grid[t][s] = Grid[j][q];
										Grid[j][q] = EMPTY_SQUARE;
										if (Player_In_Check(Grid, player) == false)
										{
											Grid[t][s] = pos;
											Grid[j][q] = prev;
											return false;
										}
										Grid[t][s] = pos;
										Grid[j][q] = prev;
									}
									else break;
									s--;
									t--;
								}
							}
							//Search BOTTOM Right x++ y++
							s = q + 1;
							t = j + 1;
							if (t < 8 && s < 8)
							{
								while (t < 8 && s < 8)
								{
									pos = Grid[t][s];
									prev = Grid[j][q];
									if (pos != EMPTY_SQUARE && ((abs(t - x) != abs(s - y)) || x == t || y == s))
										break;
									else if ((pos == EMPTY_SQUARE || pos == BLACK_BISHOP || pos == BLACK_HORSE || pos == BLACK_QUEEN || pos == BLACK_PAWN) && ((abs(t - x) == abs(s - y)) || x == t || y == s))
									{
										Grid[t][s] = Grid[j][q];
										Grid[j][q] = EMPTY_SQUARE;
										if (Player_In_Check(Grid, player) == false)
										{
											Grid[t][s] = pos;
											Grid[j][q] = prev;
											return false;
										}
										Grid[t][s] = pos;
										Grid[j][q] = prev;
									}
									else break;
									s++;
									t++;
								}
							}
							//Search BOTTOM Left x++ y--
							s = q - 1;
							t = j + 1;
							if (s >= 0 && t < 8)
							{
								while (s >= 0 && t < 8)
								{
									pos = Grid[t][s];
									prev = Grid[j][q];
									if (pos != EMPTY_SQUARE && ((abs(t - x) != abs(s - y)) || x == t || y == s))
										break;
									else if ((pos == EMPTY_SQUARE || pos == BLACK_BISHOP || pos == BLACK_HORSE || pos == BLACK_QUEEN || pos == BLACK_PAWN) && ((abs(t - x) == abs(s - y)) || x == t || y == s))
									{
										Grid[t][s] = Grid[j][q];
										Grid[j][q] = EMPTY_SQUARE;
										if (Player_In_Check(Grid, player) == false)
										{
											Grid[t][s] = pos;
											Grid[j][q] = prev;
											return false;
										}
										Grid[t][s] = pos;
										Grid[j][q] = prev;
									}
									else break;
									s--;
									t++;
								}
							}
							//Search top Right x-- y++
							s = q + 1;
							t = j - 1;
							if (s < 8 && t >= 0)
							{
								while (s < 8 && t >= 0)
								{
									pos = Grid[t][s];
									prev = Grid[j][q];
									if (pos != EMPTY_SQUARE && ((abs(t - x) != abs(s - y)) || x == t || y == s))
										break;
									else if ((pos == EMPTY_SQUARE || pos == BLACK_BISHOP || pos == BLACK_HORSE || pos == BLACK_QUEEN || pos == BLACK_PAWN) && ((abs(t - x) == abs(s - y)) || x == t || y == s))
									{
										Grid[t][s] = Grid[j][q];
										Grid[j][q] = EMPTY_SQUARE;
										if (Player_In_Check(Grid, player) == false)
										{
											Grid[t][s] = pos;
											Grid[j][q] = prev;
											return false;
										}
										Grid[t][s] = pos;
										Grid[j][q] = prev;
									}
									else break;
									s++;
									t--;
								}
							}
						}
						if (Grid[j][q] == WHITE_ROOK || Grid[j][q] == WHITE_QUEEN)
						{
							//Look Right
							for (int t = q + 1; t < 8; t++)
							{
								pos = Grid[j][t];
								prev = Grid[j][q];
								if (pos != EMPTY_SQUARE && ((abs(j - x) != abs(t - y)) || x == j || y == t))
									break;
								else if ((pos == EMPTY_SQUARE || pos == BLACK_BISHOP || pos == BLACK_HORSE || pos == BLACK_QUEEN || pos == BLACK_PAWN) && ((abs(j - x) != abs(t - y)) || x == j || y == t))
								{
									Grid[j][t] = Grid[j][q];
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j][t] = pos;
										Grid[j][q] = prev;
										return false;
									}
									Grid[j][t] = pos;
									Grid[j][q] = prev;
								}
								else break;
							}
							//Look Left
							for (int t = q - 1; t >= 0; t--)
							{
								pos = Grid[j][t];
								prev = Grid[j][q];
								if (pos != EMPTY_SQUARE && ((abs(j - x) != abs(t - y)) || x == j || y == t))
									break;
								else if ((pos == EMPTY_SQUARE || pos == BLACK_BISHOP || pos == BLACK_HORSE || pos == BLACK_QUEEN || pos == BLACK_PAWN) && ((abs(j - x) != abs(t - y)) || x == j || y == t))
								{
									Grid[j][t] = Grid[j][q];
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[j][t] = pos;
										Grid[j][q] = prev;
										return false;
									}
									Grid[j][t] = pos;
									Grid[j][q] = prev;
								}
								else break;
							}
							//Look Up
							for (int t = j + 1; t < 8; t++)
							{
								pos = Grid[t][q];
								prev = Grid[j][q];
								if (pos != EMPTY_SQUARE && ((abs(j - x) != abs(t - y)) || x == t || y == q))
									break;
								else if ((pos == EMPTY_SQUARE || pos == BLACK_BISHOP || pos == BLACK_HORSE || pos == BLACK_QUEEN || pos == BLACK_PAWN) && ((abs(j - x) != abs(t - y)) || x == t || y == q))
								{
									Grid[t][q] = Grid[j][q];
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[t][q] = pos;
										Grid[j][q] = prev;
										return false;
									}
									Grid[t][q] = pos;
									Grid[j][q] = prev;
								}
								else break;
							}
							//Look Down
							for (int t = j - 1; t >= 0; t--)
							{
								pos = Grid[t][q];
								prev = Grid[j][q];
								if (pos != EMPTY_SQUARE && ((abs(j - x) != abs(t - y)) || x == t || y == q))
									break;
								else if ((pos == EMPTY_SQUARE || pos == BLACK_BISHOP || pos == BLACK_HORSE || pos == BLACK_QUEEN || pos == BLACK_PAWN) && ((abs(j - x) != abs(t - y)) || x == t || y == q))
								{
									Grid[t][q] = Grid[j][q];
									Grid[j][q] = EMPTY_SQUARE;
									if (Player_In_Check(Grid, player) == false)
									{
										Grid[t][q] = pos;
										Grid[j][q] = prev;
										return false;
									}
									Grid[t][q] = pos;
									Grid[j][q] = prev;
								}
								else break;
							}
						}
					}
				}
			}
		}
		return true;
	}
	return false;
}

void Player_Choice(char Grid[][8], char PlayerX)
{
	char x, y;
	char j, z;
start:
	if (PlayerX == WHITE_PLAYER)
		cout << "----White to move(UPERCASE)----" << endl;
	else cout << "----Black to move(lowercase)----" << endl;
	cout << "Choose the piece you want to move:  " << endl;
	cout << "Column = ";
	cin >> y;
	cout << "Row = ";
	cin >> x;
	while (!cin.good() || x < 49 || x >(7 + 49) || y < 97 || y >= (8 + 97) || !Check_Start(Grid, 56 - x, y - 97, PlayerX))  // dealing with asciis
	{
		cin.clear();
		// cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Could have used this too to clean input buffer
		ClearInputBuffer();
        system("CLS");
		Display_Grid(Grid);
		Check_Win(Grid, PlayerX % 2 + 1);
		if (PlayerX == WHITE_PLAYER)
			cout << "----White to move(UPERCASE)----" << endl;
		else cout << "----Black to move(lowercase)----" << endl;
		cout << "Choose the piece you want to move:  " << endl;
		cout << "Insert a valid coordenate" << endl;
		cout << "Column = ";
		cin >> y;
		cout << "Row = ";
		cin >> x;
	}
	cout << "Choose where to go or write q if you messed up:  " << endl;
	cout << "Column = ";
	cin >> z;
	if (z == 'q')
	{
		system("CLS");
		Display_Grid(Grid);
		Check_Win(Grid, PlayerX % 2 + 1);
		goto start;
	}
	cout << "Row = ";
	cin >> j;
	if (j == 'q')
	{
		system("CLS");
		Display_Grid(Grid);
		Check_Win(Grid, PlayerX % 2 + 1);
		goto start;
	}
	while (!cin.good() || j < 49 || j >(49 + 7) || z < 97 || z >= (8 + 97) || !validate_My_Own_Move(Grid, 56 - x, y - 97, 56 - j, z - 97, PlayerX))
	{
		cin.clear();
		// cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Could have used this too to clean input buffer
		ClearInputBuffer();
        system("CLS");
		Display_Grid(Grid);
		Check_Win(Grid, PlayerX % 2 + 1);
		if (PlayerX == WHITE_PLAYER)
			cout << "----White to move(UPERCASE)----" << endl;
		else cout << "----Black to move(lowercase)----" << endl;
		cout << "Insert a valid move" << endl;
		cout << "Choose where to go or write q if you messed up:  " << endl;
		cout << "Column = ";
		cin >> z;
		if (z == 'q')
		{
			system("CLS");
			Display_Grid(Grid);
			Check_Win(Grid, PlayerX % 2 + 1);
			goto start;
		}
		cout << "Row = ";
		cin >> j;
		if (j == 'q')
		{
			system("CLS");
			Display_Grid(Grid);
			Check_Win(Grid, PlayerX % 2 + 1);
			goto start;
		}
	}
}

int main()
{
	char player, Grid[8][8];
	bool win, tie;
	int end;
start:
	win = false;
	tie = false;
	player = WHITE_PLAYER;
	end = StartUP_menu();
	if (end == 4) goto end;
	Create_Grid(Grid);
	Display_Grid(Grid);
	while (!win && !tie)
	{
		Player_Choice(Grid, player);
		Display_Grid(Grid);
		win = Check_Win(Grid, player);
		tie = Check_Tie(Grid, player);
		player = player % 2 + 1;
	}
	Display_Grid(Grid);
	if (tie == true)
		cout << "Tie" << endl;
	else
	{
		string winner;
        ofstream myFile("Results.txt", ios::app); // Open the file for appending
        if (myFile.is_open()) {
            if (player == WHITE_PLAYER) {
                winner = "White Player WON!!!! CHECKMATE!!!";
                myFile << winner << endl;
                cout << "White Player WON!!!! CHECKMATE!!!" << endl;
            } else if (player == BLACK_PLAYER) {
                winner = "Black Player WON!!!! CHECKMATE!!!";
                myFile << winner << endl;
                cout << "Black Player WON!!!! CHECKMATE!!!" << endl;
            }
            myFile.close();
        } 
        else {
            cout << "Error: Unable to open file." << endl;
        }
	}
	system("pause");
	//Restart some basic constants
	WHITE_CASTLE_LEFT = true;
	WHITE_CASTLE_RIGHT = true;
	WHITE_CASTLE_KING = true;
	BLACK_CASTLE_LEFT = true;
	BLACK_CASTLE_RIGHT = true;
	BLACK_CASTLE_KING = true;

	goto start;
end:
	return 0;
}
