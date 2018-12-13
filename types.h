#ifndef types_h
#define types_h



typedef struct Card{
	char info[200];
	int index;
}Card;

typedef struct Hand{
	//struct Card hand[5];
	char hand[5][200];
}Hand;

typedef struct player{
	int score;
	char name[10];
	int choice;
	char hand[5][200];
	//struct Hand hand;
}player;

typedef struct GameDB{
	char Answers[1048];
	char Questions[275];
	int AnswersUsed[50];
	int QuestionsUsed[50];
	int round; 
}GameDB;

typedef struct Judge{
	int Choice;
	int P1Score;
	int P2Score;
}Judge;

enum GameStatus{Win, OnGoing, Lose};
typedef enum {True = 1, False = 0} boolean;
#endif