#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

void shuffle_cases(int cases[], int cases_size);
void offer(int cases[], int cases_size, int initial_amount);
int remove_case_and_get_amount(int cases[], int index);
int pick_case_index(int cases[], int cases_size);
bool get_decision(void);
int cases_average(int cases[], int cases_size, int initial_amount);
int cases_remaining(int cases[], int cases_size);
int get_last_remaining_case(int cases[]);
void eliminate_cases(int cases[], int cases_size, int eliminated);

int main(void)
{
    int cases[] = {
        0,
        1,
        5,
        10,
        25,
        50,
        75,
        100,
        200,
        300,
        400,
        500,
        750,
        1000,
        5000,
        10000,
        25000,
        50000,
        75000,
        100000,
        200000,
        300000,
        400000,
        500000,
        750000,
        1000000,
    };
    int cases_size = ARRAY_SIZE(cases);

    shuffle_cases(cases, cases_size);

    printf("First, pick a case to keep.\n");
    int initial_index = pick_case_index(cases, cases_size);
    int initial_amount = remove_case_and_get_amount(cases, initial_index);
    printf("You picked %d, looks like a keeper.\n", initial_index + 1);

    for (int i = 6; i > 1; i--)
    {
        eliminate_cases(cases, cases_size, i);
        offer(cases, cases_size, initial_amount);
    }

    while (cases_remaining(cases, cases_size) > 1)
    {
        eliminate_cases(cases, cases_size, 1);
        offer(cases, cases_size, initial_amount);
    }

    int last_case = get_last_remaining_case(cases);
    int last_amount = cases[last_case];
    printf("\nDo you want to swap your case with case %d?\n", last_case + 1);
    bool decision = get_decision();
    if (decision)
    {
        printf("\nYour initial case had $%d.\n", initial_amount);
        printf("You won $%d.\n", last_amount);
    }
    else
    {
        printf("\nThe last case had $%d.\n", last_amount);
        printf("You won $%d.\n", initial_amount);
    }

    return 0;
}

void shuffle_cases(int cases[], int cases_size)
{
    srand(42);
    for (int shuffle = 0; shuffle < 100; ++shuffle)
    {
        for (int i = 0; i < cases_size; ++i)
        {
            int j = rand() % cases_size;
            int temp = cases[i];
            cases[i] = cases[j];
            cases[j] = temp;
        }
    }
}

void offer(int cases[], int cases_size, int initial_amount)
{
    int offer_amount = cases_average(cases, cases_size, initial_amount);
    printf("\nYour offer to quit now is $%d, deal or no deal?.\n", offer_amount);
    bool deal = get_decision();
    if (deal)
    {
        printf("\nYour case was worth: $%d\n", initial_amount);
        printf("You walked away with $%d.\n", offer_amount);
        exit(0);
    }
}

int remove_case_and_get_amount(int cases[], int index)
{
    int amount = cases[index];
    cases[index] = -1;
    return amount;
}

void eligible_cases(int cases[], int cases_size)
{
    printf("Eligible cases: ");
    for (int i = 0; i < cases_size; i++)
    {
        if (cases[i] != -1)
        {
            printf("%d ", (i + 1));
        }
    }
    printf("\n");
}

int pick_case_index(int cases[], int cases_size)
{
    int casePicked;
    eligible_cases(cases, cases_size);
    do
    {
        printf("Pick a case : ");
        scanf("%d", &casePicked);
    } while (casePicked < 1 || casePicked > cases_size || cases[casePicked - 1] == -1);
    return casePicked - 1;
}

bool get_decision(void)
{
    int decision;
    do
    {
        printf("Decide now (0 for no , 1 for yes): ");
        scanf("%d", &decision);
    }

    while (decision != 0 && decision != 1);

    if (decision == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int cases_average(int cases[], int cases_size, int initial_amount)
{
    int sum = initial_amount;
    int numCases = 1;
    for (int i = 0; i < cases_size; i++)
    {
        if (cases[i] != -1)
        {
            sum += cases[i];
            numCases++;
        }
    }
    return sum / numCases;
}

int cases_remaining(int cases[], int cases_size)
{
    int numRemaining = 0;
    for (int i = 0; i < cases_size; i++)
    {
        if (cases[i] != -1)
        {
            numRemaining++;
        }
    }
    return numRemaining;
}

int get_last_remaining_case(int cases[])
{
    int counter = 0;
    while (cases[counter] == -1)
    {
        counter++;
    }
    return counter;
}

void eliminate_cases(int cases[], int cases_size, int eliminated)
{
    int casePickedIndex;
    printf("\nOpen %d case ( s ) to eliminate\n", eliminated);
    for (int i = 0; i < eliminated; i++)
    {
        casePickedIndex = pick_case_index(cases, cases_size);
        printf("Case %d is worth $%d , it \' s gone now .\n", (casePickedIndex + 1), remove_case_and_get_amount(cases, casePickedIndex));
    }
}
