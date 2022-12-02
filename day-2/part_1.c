#include <stdio.h>
#include <stdlib.h>

enum PlayedHand { Rock, Paper, Scissors };
enum RoundOutcome { Win, Loss, Draw };

enum PlayedHand getOpponentMove(char c) {
  switch (c) {
  case 'A':
    return Rock;
  case 'B':
    return Paper;
  case 'C':
    return Scissors;
  default:
    printf("invalid input for getOpponentMove: %c", c);
    exit(1);
  }
}

enum PlayedHand getPlayerMove(char c) {
  switch (c) {
  case 'X':
    return Rock;
  case 'Y':
    return Paper;
  case 'Z':
    return Scissors;
  }
  printf("invalid input for getPlayerMove: %c", c);
  exit(1);
}

int scoreFromPlayedHand(enum PlayedHand playedHand) {
  switch (playedHand) {
  case Rock:
    return 1;
  case Paper:
    return 2;
  case Scissors:
    return 3;
  }
  printf("invalid input for scoreFromPlayedHand: %c", playedHand);
  exit(1);
}

int scoreFromRoundOutcome(enum RoundOutcome roundOutcome) {
  switch (roundOutcome) {
  case Win:
    return 6;
  case Draw:
    return 3;
  case Loss:
    return 0;
  }
  printf("invalid input for scoreFromRoundOutcome: %c", roundOutcome);
  exit(1);
}

int main(int argc, char **arv) {
  char *line = NULL;
  size_t lineLengthLimit = 0;
  int numCharsRead;
  enum PlayedHand opponentPlayed, playerPlayed;
  enum RoundOutcome roundOutcome;
  int totalScore = 0;
  while ((numCharsRead = getline(&line, &lineLengthLimit, stdin)) != EOF) {
    if (numCharsRead < 3) {
      printf("invalid line length: %c", numCharsRead);
      exit(1);
    }
    opponentPlayed = getOpponentMove(line[0]);
    playerPlayed = getPlayerMove(line[2]);
    if (opponentPlayed == Rock) {
      if (playerPlayed == Scissors) {
        roundOutcome = Loss;
      } else if (playerPlayed == Paper) {
        roundOutcome = Win;
      } else {
        roundOutcome = Draw;
      }
    } else if (opponentPlayed == Paper) {
      if (playerPlayed == Scissors) {
        roundOutcome = Win;
      } else if (playerPlayed == Rock) {
        roundOutcome = Loss;
      } else {
        roundOutcome = Draw;
      }
    } else if (opponentPlayed == Scissors) {
      if (playerPlayed == Rock) {
        roundOutcome = Win;
      } else if (playerPlayed == Paper) {
        roundOutcome = Loss;
      } else {
        roundOutcome = Draw;
      }
    }
    totalScore +=
        scoreFromPlayedHand(playerPlayed) + scoreFromRoundOutcome(roundOutcome);
  }
  printf("%d\n", totalScore);
  return 0;
}