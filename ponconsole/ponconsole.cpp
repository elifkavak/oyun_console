#include<iostream>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>
#include <time.h>

using namespace std;

char l[] = "|||||";
int i;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y) {
  CursorPosition.X = x;
  CursorPosition.Y = y;
  SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size) // set bool visible = 0 - invisible, bool visible = 1 - visible
{
  if (size == 0) {
    size = 20; // default cursor size Changing to numbers from 1 to 20, decreases cursor width
  }
  CONSOLE_CURSOR_INFO lpCursor;
  lpCursor.bVisible = visible;
  lpCursor.dwSize = size;
  SetConsoleCursorInfo(console, & lpCursor);
}

void printBorder() {
  for (i = 2; i <= 79; i++) {
    gotoxy(i, 1);
    cout << '.';
    gotoxy(i, 25);
    cout << '.';
  }
  for (i = 2; i <= 25; i++) {
    gotoxy(2, i);
    cout << '.';
    gotoxy(79, i);
    cout << '.';
  }
  for (i = 3; i <= 78; i++) {
    gotoxy(i, 4);
    cout << '.';
  }
}
void setplayers() {
  system("cls");
  printBorder();
  gotoxy(4, 3);
  cout << "PLAYER 1 : 0";
  gotoxy(24, 2);
  cout << "Press Esc key to quit game";
  gotoxy(65, 3);
  cout << "PLAYER 2 : 0";
  
  for (i = 0; i <= strlen(l); i++) {
    gotoxy(5, 5 + i);
    cout << l[i];
  }
  for (i = 0; i <= strlen(l); i++) {
    gotoxy(76, 5 + i);
    cout << l[i];
  }
}

void gameplay() {
  setplayers();
  void displayMenu();
  
  int sc = 0, pp = 0, st = 1;
  int sc2 =0 ;
  int c = 5, k = 5, x = 32, y = 10;
  
  int d = rand() % 2, px, py;
  
  int op = 1, go = 1;
  
  int rld = 0, rlu = 0, lru = 0, lrd = 0;

  while (1) {
    if (go == 1) {
      while (!kbhit() && op) {
        px = x;
        py = y;
        gotoxy(x, y);
        cout << "O";
        Sleep(150);
        gotoxy(x, y);
        cout << " ";

        if (st == 1) {
          st = 0;
          if (d == 0) {
            x--;
            y++;
          } else {
            x--;
            y--;
          }
        }

        if (rld) {
          x--;
          y++;
        }
        if (rlu) {
          x--;
          y--;
        }
        if (lru) {
          x++;
          y--;
        }
        if (lrd) {
          x++;
          y++;
        }

        if (x < px && y > py) rld = 1;
        if (x < px && y < py) rlu = 1;
        if (y == 5 && rlu) {
          rld = 1;
          rlu = 0;
        }
        if (y == 24 && rld) {
          rlu = 1;
          rld = 0;
        }
        if (x == 6 && rlu) {
          lru = 1;
          rlu = 0;
        }
        if (x == 6 && rld) {
          lrd = 1;
          rld = 0;
        }
        if (y == 5 && lru) {
          lrd = 1;
          lru = 0;
        }
        if (y == 24 && lrd) {
          lru = 1;
          lrd = 0;
        }
        if (x == 75 && lrd) {
          rld = 1;
          lrd = 0;
        }
        if (x == 75 && lru) {
          rlu = 1;
          lru = 0;
        }

        if (x == 75 || x == 6) {
          Sleep(50);
        }
        if (y == 5 || y == 24) {
          Sleep(50);
        }
       
		

        if (x == 6 && (y < c || y > c + strlen(l) - 1)) {
          gotoxy(25, 10);
          cout << "Press ENTER to play again !";
          if(sc> sc2){
          	gotoxy(27, 12);
          	cout << "Player 1 won!";	
		  }else if (sc2> sc){
		  	gotoxy(27, 12);
          	cout << "Player 2 won!";	
		  } else{
		  	gotoxy(30, 12);
          	cout << "Deuce !";
		  }

          op = 0;
          break;
        }
		if (x == 75 && (y < k || y > k + strlen(l) - 1)) {
          gotoxy(20, 10);
          cout << "Press ENTER to play again !";
          if(sc> sc2){
          	gotoxy(27, 12);
          	cout << "Player 1 won!";	
		  }else if (sc2> sc){
		  	gotoxy(27, 12);
          	cout << "Player 2 won!";	
		  } else{
		  	gotoxy(30, 12);
          	cout << "Deuce !";
		  }
          
          op = 0;
          break;
        }

        if (x == 6 && op == 1) {
          gotoxy(4, 3);
          cout << "PLAYER 1 : " << ++sc;
        }
        
        if (x == 75 && op == 1) {
          gotoxy(65, 3);
          cout << "PLAYER 2 : " << ++sc2;
        }

      }
    }

    char ch = getch();

    if (ch == ' ' && op == 1) {
      pp = 1;
      go = 0;
      gotoxy(22, 12);
      cout << "GAME PAUSED ! PRESS ENTER to continue !";
    }
    if (ch == 13 && pp && op == 1) {
      pp = 0;
      go = 1;
      gotoxy(22, 12);
      cout << "                                       ";
    }
    
    
    if (ch == 13 && op == 0) {
      op = 1;
      gameplay();
      break;
    }
    if ((ch == 's' || ch == 'S') && c <= 19 && op) {
      gotoxy(5, c + strlen(l));
      cout << "|";
      gotoxy(5, c);
      cout << ' ';
      c++;
    }
    if ((ch == 'w' || ch == 'W' ) && c >= 6 && op) {
      gotoxy(5, c - 1);
      cout << "|";
      gotoxy(5, c + 4);
      cout << ' ';
      c--;
    }
    if (ch == 72 && k >= 6 && op) {
      gotoxy(76, k - 1);
      cout << "|";
      gotoxy(76, k + 4);
      cout << ' ';
      k--;
	}

	if (ch == 80 && k <= 19 && op){
      gotoxy(76, k + strlen(l));
      cout << "|";
      gotoxy(76, k);
      cout << ' ';
      k++;
	}
    
    if (ch == 27) {
      displayMenu();
      break;
    }
  }
}

void displayMenu() {
  system("cls");
  void howtogame();
  printBorder();
  int cp = 1;
  gotoxy(33, 3);
  cout << "PONG GAME";
  
  gotoxy(30, 8);
  cout << "1. PLAY THE GAME";
  gotoxy(30, 12);
  cout << "2. EXIT (ESC)";
  gotoxy(20, 16);
  cout << "Enter Option from Menu: (1-2) ";

  char op = getche();
  if (op == '1') gameplay();
  if (op == '2') exit(0);

}
/*void howtogame() {
  system("cls");
  printBorder();
  gotoxy(4, 3);
  cout << "INSTRUCTIONS";
  gotoxy(4, 4);
  cout << "-------------";
  gotoxy(4, 5);
  cout << "- Press w or Up Arrow to move up.";
  gotoxy(4, 7);
  cout << "- Press s or Down Arrow to move down.";
  gotoxy(4, 9);
  cout << "- Press Spacebar to pause the game.";
  gotoxy(4, 11);
  cout << "- Press Esc to quit the game.";
  gotoxy(4, 15);
  cout << "Press any key to go to menu ...";
  getch();
  displayMenu();
} */
int main() {
  setcursor(0, 0);
  srand((unsigned) time(NULL));
  system("cls");
  displayMenu();

  return 0;
}
