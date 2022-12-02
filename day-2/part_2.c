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

enum RoundOutcome getDesiredRoundOutcome(char c) {
  switch (c) {
  case 'X':
    return Loss;
  case 'Y':
    return Draw;
  case 'Z':
    return Win;
  }
  printf("invalid input for getDesiredRoundOutcome: %c", c);
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
  size_t lineLengthLimit = 10;
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
    roundOutcome = getDesiredRoundOutcome(line[2]);
    if (opponentPlayed == Rock) {
      if (roundOutcome == Win) {
        playerPlayed = Paper;
      } else if (roundOutcome == Loss) {
        playerPlayed = Scissors;
      } else {
        playerPlayed = Rock;
      }
    } else if (opponentPlayed == Paper) {
      if (roundOutcome == Win) {
        playerPlayed = Scissors;
      } else if (roundOutcome == Loss) {
        playerPlayed = Rock;
      } else {
        playerPlayed = Paper;
      }
    } else if (opponentPlayed == Scissors) {
      if (roundOutcome == Win) {
        playerPlayed = Rock;
      } else if (roundOutcome == Loss) {
        playerPlayed = Paper;
      } else {
        playerPlayed = Scissors;
      }
    }
    totalScore +=
        scoreFromPlayedHand(playerPlayed) + scoreFromRoundOutcome(roundOutcome);
  }
  printf("%d\n", totalScore);
  return 0;
}