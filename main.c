#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "types.h"

char answers[1048][200];
char questions[275][500];


char p1Deck[5][200];
char p2Deck[5][200];
void createAnswers(){
  //char answers[1048][200];

  //GameDB tcards; 
  FILE *file = fopen("answers.txt" ,"r");
  char buff[200];
  int i = 0;
  while(fgets(buff, 200, file) != NULL){
    strcpy(answers[i], buff);
    i++;
  }
  fclose(file);
  
}

void createQuestions(){
  FILE *file = fopen("questions.txt" ,"r");
  char buff[500];
  int i = 0;
  while(fgets(buff, 500, file) != NULL){
    strcpy(questions[i], buff);
    i++;
  }
  fclose(file);
  
}

void removeCard(int index){

      //for (int c = index - 1; c < n - 1; c++)
        // answers[c] = answers[c+1];
}

void printHand(player playerHand){
    for(int count = 1; count <=5; count++){
      printf("%d.  %s", count, playerHand.hand[count-1]);
    }
}

boolean questionDupeCheck(int number, GameDB db){
  for(int count = 0; count < db.round; count++){
    if(db.AnswersUsed[count] == number){
      return 0;
    }
  }
  return 1;
}

void threePlayer(char * first, char * second){

  GameDB data;
  data.round = 0;
  player playerOne, playerTwo;
  playerOne.score = 0;
  playerTwo.score = 0; 
  //playerOne.name = name1;
  strcpy(playerOne.name, first);
  strcpy(playerTwo.name, second);

  srand(time(NULL));
  for(int count = 0; count < 5; count++){
    int rand1 = rand() % 1048;
    int rand2 = rand() % 1048;
    data.AnswersUsed[count] = rand1;
    data.AnswersUsed[count + 1] = rand2;
    strcpy(playerOne.hand[count], answers[rand1]);
    strcpy(playerTwo.hand[count], answers[rand2]);
  }
  system("clear");

  while(playerOne.score < 5 && playerTwo.score < 5){
      data.round++;
      int randomQuestion = rand() % 275;
      int player1Choice, player2Choice, judgeChoice;


      printf("\n%s pick your card\n", first);
      printf("%s", questions[randomQuestion]);
      printHand(playerOne);
      scanf("%d", &player1Choice);
      system("clear");

      printf("\n%s pick your card\n", second);
      printf("%s", questions[randomQuestion]);
      printHand(playerTwo);
      scanf("%d", &player2Choice);
      system("clear");


      printf("\n%s", questions[randomQuestion]);
      printf("1. %s", playerOne.hand[player1Choice - 1]);
      printf("2. %s", playerTwo.hand[player2Choice - 1]);

      scanf("%d", &judgeChoice);

      if(judgeChoice == 1)
        playerOne.score += 1;
      else if(judgeChoice == 2)
        playerTwo.score += 1;

      boolean again;
      int new1, new2;

        do{
        new1 = rand() % 1048;
        new2 = rand() % 1048;
        again = False;

        if(questionDupeCheck(new1, data) == 0){
          new1 = rand() % 1048;
          again = True;
        }
        else if(questionDupeCheck(new2, data) == 0){
            new2 = rand() % 1048;
            again = True;
        }

      }while(again == True);

      
      strcpy(playerOne.hand[player1Choice- 1], answers[new1]);
      strcpy(playerTwo.hand[player2Choice-1], answers[new2]);

      system("clear");
  
}

if(playerOne.score == 5)
  printf("Player 1 won the game.\n");
else
  printf("Player 2 won the game.\n");

printf("Player one score:  %d\n", playerOne.score);
printf("Player two score:  %d\n", playerTwo.score);






}
int main(){
    createQuestions();
    createAnswers();

    char name1[10];
    char name2[10];

    //GameData cards = createAnswers();
    //strcpy(cards.Answers, createAnswers());
    


    printf("Player 1 enter your name:  ");
    //scanf("%s", &name);  - deprecated
    scanf("%s", name1);
    printf("Player 2 enter your name:  ");
    scanf("%s", name2);

    threePlayer(name1, name2);
    
	return 0;
}