#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "types.h"

//char answers[1048][200];
//char questions[275][500];

GameDB db;

//char p1Deck[5][200];oof
//char p2Deck[5][200];

//loads in answers to db struct non child version
void createAnswers(){
  //char answers[1048][200];

  //GameDB tcards; 
  FILE *file = fopen("answers.txt" ,"r");
  char buff[200];
  int i = 0;
  while(fgets(buff, 200, file) != NULL){
    strcpy(db.Answers[i].info, buff);
    i++;
  }
  fclose(file);
  
}

//loads in questions to db struct
void createQuestions(){
  FILE *file = fopen("questions.txt" ,"r");
  char buff[500];
  int i = 0;
  while(fgets(buff, 500, file) != NULL){
    strcpy(db.Questions[i].info, buff);
    i++;
  }
  fclose(file);
  
}

//loads in non vulgar cards to db struct
void creatChild(){
  FILE *file = fopen("apples.txt" ,"r");
  char buff[500];
  int i = 0;
  while(fgets(buff, 500, file) != NULL){
    strcpy(db.Answers[i].info, buff);
    i++;
  }
  fclose(file);
  
}

//prints out the user's hand
void printHand(player playerHand){
    for(int count = 1; count <=5; count++){
      printf("%d.  %s", count, playerHand.hand.cards[count-1].info);
    }
}

//checks database to see if card has been chose already in the game
int questionDupeCheck(int number, GameDB db){
  for(int count = 0; count < db.round; count++){
    if(db.AnswersUsed[count] == number){
      return 0;
    }
  }
  return 1;
}

//the main game
void threePlayer(char * first, char * second){

  GameDB data;
  data.round = 0;
  player playerOne, playerTwo;
  playerOne.score = 0;
  playerTwo.score = 0; 
  
  strcpy(playerOne.name, first);
  strcpy(playerTwo.name, second);
	int duplicate =0;
  srand(time(NULL));

  //loads player hand and adds used card to database
  for(int count = 0; count < 5; count++){
    int rand1 = rand() % 1048;
    int rand2 = rand() % 1048;
    data.AnswersUsed[count] = rand1;
    data.AnswersUsed[count + 1] = rand2;
	duplicate++;
    strcpy(playerOne.hand.cards[count].info, db.Answers[rand1].info);
    strcpy(playerTwo.hand.cards[count].info, db.Answers[rand2].info);
  }
  system("clear");


  //loop suntil someone has a score of 5
  while(playerOne.score < 5 && playerTwo.score < 5){
      data.round++;
      int randomQuestion = rand() % 275;
      int player1Choice, player2Choice, judgeChoice;
      char choice = 'y'; 

        //allows user to choose a new question
        while(choice == 'y'){
          printf("Card: %s", db.Questions[randomQuestion].info);
          printf("Do you want to pick another card? y/n\n");
          scanf("%s", &choice);
          if(choice == 'y')
            randomQuestion = rand() % 275;
          system("clear");
        }
      //prints user deck and allows for card to be chosen for user 1
      printf("\n%s pick your card\n", first);
      printf("%s", db.Questions[randomQuestion].info);
      printHand(playerOne);
      scanf("%d", &player1Choice);
      system("clear");

      //prints user deck and allows for card to be chosen for user 2
      printf("\n%s pick your card\n", second);
      printf("%s", db.Questions[randomQuestion].info);
      printHand(playerTwo);
      scanf("%d", &player2Choice);
      system("clear");

      //prints out judges options to chose from
      printf("\n%s", db.Questions[randomQuestion].info);
      printf("1. %s", playerOne.hand.cards[player1Choice - 1].info);
      printf("2. %s", playerTwo.hand.cards[player2Choice - 1].info);

      scanf("%d", &judgeChoice);

      //updates the score for the players
      if(judgeChoice == 1)
        playerOne.score += 1;
      else if(judgeChoice == 2)
        playerTwo.score += 1;

      boolean again;
      int new1, new2;
      //checks if the new answers card has been drawn before
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

      //adds cards to duplicated list
	      data.AnswersUsed[duplicate + 1] = new1;
	      duplicate++;
	      data.AnswersUsed[duplicate + 1] = new2;
      	duplicate++;
      strcpy(playerOne.hand.cards[player1Choice - 1].info, db.Answers[new1].info);
      strcpy(playerTwo.hand.cards[player2Choice - 1].info, db.Answers[new2].info);

      system("clear");
  
}

//prints out who one the game
if(playerOne.score == 5)
  printf("Player 1 won the game.\n");
else
  printf("Player 2 won the game.\n");

printf("Player one score:  %d\n", playerOne.score);
printf("Player two score:  %d\n", playerTwo.score);






}
int main(){
//prints out welcoming page
system("clear");
printf("Cards Against Humanity is a party game for horrible people. \nUnlike most of the party games you have played before, Cards Against Humanity \nis as despicable and awkward as you and your friends.\n");
printf("\n");
printf("Instructions:  \n");
printf("Each round,  a random black card is chosen from the deck, and everyone \nelse answers with their funniest card.\n");
    printf("\nWould you like to enable children mode?  y/n \n");
    char pres;
    scanf("%c", &pres);

    //lets user choose what deck of cards they would prefer to be displayed 
    if(pres == 'y')
      creatChild();
    else
      createAnswers();
    createQuestions();
    //createAnswers();

    char name1[10];
    char name2[10];

	  system("clear");
    printf("Player 1 enter your name:  ");
    //scanf("%s", &name);  - deprecated
    scanf("%s", name1);
    printf("Player 2 enter your name:  ");
    scanf("%s", name2);

    //starts the game with the names of the players
    threePlayer(name1, name2);
    
	return 0;
}
