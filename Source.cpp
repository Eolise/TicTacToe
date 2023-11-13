#include <iostream>

using namespace std;

const int sizeGrid = 3;

// Fonction pour afficher la grille du Morpion
void showGrid(char grid[sizeGrid][sizeGrid]) {
	for (int i = 0; i < sizeGrid; i++) {
		for (int j = 0; j < sizeGrid; j++) {
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
}

// Fonction pour verifier s'il y a un gagnant ou non
bool checkWin(char grid[sizeGrid][sizeGrid], char pawn) {
	for (int i = 0; i < sizeGrid; i++) {
		if ((grid[i][0] == pawn && grid[i][1] == pawn && grid[i][2] == pawn) || //verifie si l'une des lignes a trois pions identiques
			(grid[0][i] == pawn && grid[1][i] == pawn && grid[2][i] == pawn)) { //verifie si l'une des colonnes a trois pions identiques
			return true;
		}
	}
	if ((grid[0][0] == pawn && grid[1][1] == pawn && grid[2][2] == pawn) || //verifie si la premiere diagonale a trois pions identiques
		(grid[0][2] == pawn && grid[1][1] == pawn && grid[2][0] == pawn)) { //verifie si la deuxieme diagonale a trois pions identiques
		return true;
	}
	return false; //pas de condition de victoire trouvee
}

// Fonction pour demander aux joueurs s'ils veulent recommencer une partie
bool askRestart() {
	char restart;
	cout << "Voulez-vous recommencer une partie ? (O/N) : ";
	cin >> restart;
	return (restart == 'O');
}

// Fonction principale du jeu
void playTicTacToe() {
    do {
        system("cls"); //on nettoie la console
        char grid[sizeGrid][sizeGrid] = { {' ',' ',' '},{' ',' ',' '},{' ',' ',' '} }; //on cree une grille avec des espaces vides qu'on remplacera par le symbole des pions au fil des tours
        bool turnPlayer1 = true; //le joueur 1 commence
        int turn = 0; //on commence au tour 1 (donc 0 dans le code)

        while (turn < 9) {
            showGrid(grid);

            int raw, column;
            //on determine si c'est au joueur 1 ou 2 de poser un pion
            if (turnPlayer1) {
                cout << "Joueur 1, ";
            }
            else {
                cout << "Joueur 2, ";
            }
            //on demande à l'utilisateur dans quelle case veut-il poser son pion
            cout << "Entrez la ligne et la colonne (de 1 a 3) : ";
            cin >> raw >> column;
            //sans les deux lignes suivantes, si l'utilisateur rentre autre chose qu'un entier, le programme tourne a l'infini
            cin.clear(); // permet d'effacer le flux
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // supprime toutes les entrees en attente dans le flux

            raw--;
            column--; //on enleve 1 a ce qu'a entre l'utilisateur pour la ligne et la colonne, car la grille va de 0 a 2 et non pas de 1 a 3

           
            if (raw >= 0 && raw < sizeGrid && column >= 0 && column < sizeGrid && grid[raw][column] == ' ') {
                char pawn;
                if (turnPlayer1) {
                    pawn = 'X';
                }
                else {
                    pawn = 'O';
                }
                grid[raw][column] = pawn;

                if (turn >= 4) {
                    if (checkWin(grid, pawn)) {
                        showGrid(grid);
                        if (turnPlayer1) {
                            cout << "Joueur 1 gagne la manche !" << endl;
                        }
                        else {
                            cout << "Joueur 2 gagne la manche !" << endl;
                        }
                        break;
                    }
                }

                if (turnPlayer1) {
                    turnPlayer1 = false;
                }
                else {
                    turnPlayer1 = true;
                }
                turn++;
            }
            else {
                cout << "Entree invalide, reessayez !" << endl;
            }
        }

        if (turn == 9) {
            showGrid(grid);
            cout << "Match nul !" << endl;
        }
    } while (askRestart());
}

// Fonction main pour appeler la fonction qui permet de jouer au jeu
int main() {
	playTicTacToe();
	return 0;
}