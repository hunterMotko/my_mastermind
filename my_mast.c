#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

int stringLength(char guess[])
{
  int i = 0;

  while (guess[i] != '\n') {
    i++;
  }

  return i;
}

void readGuess(char guess[]) {
  read(0, guess, 5);
  guess[5] = '\0';
}

int my_putchar(char c) {
  return write(1, &c, 1);
}

void my_putstr(char *param_1) {
  int count = 0;

  while (param_1[count] != '\0') {
    my_putchar(param_1[count]);
    count++;
  }
}

int checkGuess(char guess[]) {
  int val = atoi(guess);
  int num = 0;

  if (val == 0 && (guess[0] != 0)) { return 1; }
  else {
    for (int i = 0; i < 4; i++) {
      num = val % 10;
      val = val / 10;
      if (num >= 8) {
        return 1;
      }
    }
  }
  return 0;
}

int checkMatches(char target[], char guess[]) {
  int correct = 0;
  int misplaced = 0;

  for (int i = 0; i < 4; i++) {
    if (target[i] == guess[i]) {
      correct++;
    } else {
      misplaced++;
    }
  }
  if (correct == 4) {
    return 0;
  } else {
    printf("Well placed pieces: %d\n", correct);
    printf("Misplaced pieces: %d\n", misplaced);
    return 1;
  }
}
int main(int argc, char **argv) {
  char target[5];
  char guess[5] = {0};
char openStr[] = "Will you find the secret code?\n";
  char wrongStr[] = "Wrong Input!";
  char winStr[] = "Congratz! You did it!";

  char *pOpen = openStr;
  char *pWrong = wrongStr;
  char *pWin = winStr;

  if (argc > 2 && argv[1][0] == '-' && argv[1][1] == 'c')
  {
    for (int i = 0; i < 4; i++)
    {
      target[i] = argv[2][i];
    }
  } else {
    srand(time(NULL));
    for (int i = 0; i < 4; i++) {
      int random = (rand() % 8);
      target[i] = (random + '0');
    }
  }
  target[4] = '\0';

  my_putstr(pOpen);
  my_putchar('\n');

  for (int round = 0; round < 10; round++) {
    printf("Round: %d\n", round);
    readGuess(guess);

    while (stringLength(guess) != 4 || checkGuess(guess) != 0) {
      my_putstr(pWrong);
      my_putchar('\n');
      readGuess(guess);
    }

    if (checkMatches(target, guess) == 0) {
      my_putstr(pWin);
      my_putchar('\n');
      return 0;
    }
  }

  return 0;
}