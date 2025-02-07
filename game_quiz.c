#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 256

const int question_count = 3;
const int score_bonus = 10;
const int score_decrease = 5;

typedef struct {
    char ques[MAX_LENGTH];
    char answer[4][MAX_LENGTH];
    char correct;
} Question;

Question question_pool[MAX_LENGTH];
int idx_question = 0;

void add_question(char question[], char ansA[], char ansB[], char ansC[], char ansD[], char correct)
{
    if (idx_question < MAX_LENGTH) {
        strcpy(question_pool[idx_question].ques, question);
        strcpy(question_pool[idx_question].answer[0], ansA);
        strcpy(question_pool[idx_question].answer[1], ansB);
        strcpy(question_pool[idx_question].answer[2], ansC);
        strcpy(question_pool[idx_question].answer[3], ansD);
        question_pool[idx_question].correct = correct;
        idx_question++;
    }
}

void read_question()
{
    FILE *f;
    f = fopen("question_pool.txt", "r");

    while (!feof(f))
    {
        char ques[MAX_LENGTH]; 
        //Get question
        fgets(ques, sizeof(ques), f);
        //Get ans A
        char ansA[MAX_LENGTH];
        fgets(ansA, sizeof(ansA), f);
        //Get ans B
        char ansB[MAX_LENGTH];
        fgets(ansB, sizeof(ansB), f);
        //Get ans C
        char ansC[MAX_LENGTH];
        fgets(ansC, sizeof(ansC), f);
        //Get ans D
        char ansD[MAX_LENGTH];
        fgets(ansD, sizeof(ansD), f);
        //Get correct
        char line[MAX_LENGTH];
        fgets(line, sizeof(line), f);
        char correct = line[0];
        add_question(ques, ansA, ansB, ansC, ansD, correct);
    }
}

char confirm_correct()
{
    do
    {
        char cor;
        scanf(" %c", &cor);
        cor = toupper(cor);
        if (cor == 'A' || cor == 'B' || cor == 'C' || cor == 'D')
        {
            return cor;
        }
        else 
        {
            printf("Please enter correct form: ");
        }
    } while (1);
    
}

void player_add_question()
{
    char q[MAX_LENGTH], ans1[MAX_LENGTH], ans2[MAX_LENGTH], ans3[MAX_LENGTH], ans4[MAX_LENGTH], cor;
    printf("Enter the question: "); gets(q);
    printf("Enter Answer A: "); gets(ans1);
    printf("Enter Answer B: "); gets(ans2);
    printf("Enter Answer C: "); gets(ans3);
    printf("Enter Answer D: "); gets(ans4);
    printf("Choose Correct answer (A/B/C/D): "); //scanf(" %c", &cor); cor = toupper(cor);
    cor = confirm_correct();
    add_question(q, ans1, ans2, ans3, ans4, cor);
    printf("Add question successfully!");
}

void swap_question(int a, int b)
{
    Question temp = question_pool[a];
    question_pool[a] = question_pool[b];
    question_pool[b] = temp;
}

void play_game()
{
    int score = 0;
    int i, j;
    srand(time(NULL));
    for (i=0; i<question_count; i++) 
    {
        int index = rand() % (idx_question-i) + i;
        Question current_question = question_pool[index];
        printf("\nQuestion %d: %s\n", i + 1, current_question.ques);
        for (j = 0; j < 4; j++) {
            printf("%c. %s\n", 'A' + j, current_question.answer[j]);
        }
        char ans;
        printf("Enter your answer: ");
        //scanf(" %c", &ans); ans = toupper(ans);
        ans = confirm_correct();

        if (ans == question_pool[index].correct) {
            score += score_bonus;
            printf("Correct Answer! You add %d points. Current Score: %d\n",score_bonus, score);
        } else {
            score -= score_decrease;
            printf("Wrong Answer! You remove %d points. Current Score: %d\n",score_decrease, score);
        }

        swap_question(i, index);
    }
    printf("\nEnd! Final score: %d\n\n", score);
}

int main()
{
    read_question();

    int choice;
    while (1) {
        printf("1. Play Game \n2. Add Question \n3. Quit \nChoose an option: ");
        scanf("%d", &choice);
        
        switch (choice)
        {
            case 1:
                play_game();
                break;
            case 2:
                player_add_question();
                break;
            case 3:
                printf("Sayonara!\n");
                break;
            default:
                printf("Wrong Input! Try again.\n");
                break;
        }
    }
    return 0;
}
