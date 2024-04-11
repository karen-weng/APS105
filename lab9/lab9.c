#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

bool checkSameName(LinkedList *, char labelName[STRING_MAX]);
double calcCurrent(LinkedList *, int);
void handleInsert(LinkedList *);
void handleRemove(LinkedList *);
void handleCurrentCal(LinkedList *, int);
void handleVoltage(LinkedList *, int);
void handlePrint(LinkedList *);
void handleQuit(LinkedList *);

int main(void)
{
  LinkedList circuit;
  initList(&circuit);
  char command = '\0';
  printf("Welcome to our circuit simulator\n");
  printf("What is the source of the voltage?\n");
  int voltage;
  readInputNumber(&voltage);

  while (command != 'Q')
  {
    command = getCommand();

    switch (command)
    {
    case 'I':
      handleInsert(&circuit);
      break;
    case 'R':
      handleRemove(&circuit);
      break;
    case 'C':
      handleCurrentCal(&circuit, voltage);
      break;
    case 'V':
      handleVoltage(&circuit, voltage);
      break;
    case 'P':
      handlePrint(&circuit);
      break;
    case 'Q':
      handleQuit(&circuit);
      break;
    }
  }
  return 0;
}

bool checkSameName(LinkedList *circuit, char labelName[STRING_MAX])
{
  Node *anotherCurrentNode = circuit->head;
  while (anotherCurrentNode != NULL)
  {
    if (strcmp(labelName, anotherCurrentNode->name) == 0)
    {
      return true;
      break;
    }
    anotherCurrentNode = anotherCurrentNode->next;
  }
  return false;
}

double calcCurrent(LinkedList *circuit, int voltage)
{
  double current = 0;
  Node *counter = circuit->head;
  while (counter != NULL)
  {
    current += counter->value;
    counter = counter->next;
  }
  current = voltage / current;
  return current;
}

void handleInsert(LinkedList *circuit)
{
  int resistance = 0;
  printf("What's the value of the resistor: ");
  readInputNumber(&resistance);
  printf("What's the label of the resistor: ");
  char labelName[STRING_MAX];
  readInputString(labelName, STRING_MAX);

  if (checkSameName(circuit, labelName))
  { // check repeats names
    printf("A resistor with %s label already exists.\n", labelName);
  }
  else
  {
    if (circuit->head == NULL)
    {
      circuit->head = malloc(sizeof(Node));
      Node *newResistor = malloc(sizeof(Node));
      if (newResistor != NULL)
      {
        newResistor = circuit->head;
        newResistor->value = resistance;
        strcpy(newResistor->name, labelName);
        newResistor->next = NULL;
      }
    }
    else
    {
      Node *currentNode = circuit->head;
      Node *newResistor = malloc(sizeof(Node));
      if (newResistor != NULL)
      {
        newResistor->value = resistance;
        strcpy(newResistor->name, labelName);
      }

      if (strcmp(labelName, currentNode->name) < 0)
      { // put at front
        if (newResistor != NULL)
        {
          newResistor->next = circuit->head;
          circuit->head = newResistor;
        }
      }
      else
      {
        while ((currentNode->next) != NULL)
        {
          if (strcmp(labelName, (currentNode->next)->name) > 0)
          {
            currentNode = currentNode->next;
          }
          else
          {
            break;
          }
        }

        newResistor->next = currentNode->next;
        currentNode->next = newResistor;
      }
    }
  }
}

void handleRemove(LinkedList *circuit)
{
  printf("What's the label of the resistor you want to remove: ");
  char labelName[STRING_MAX];
  readInputString(labelName, STRING_MAX);
  if (!checkSameName(circuit, labelName))
  {
    printf("The resistor with %s label does not exist.\n", labelName);
  }
  else
  {
    Node *anotherCurrentNode = circuit->head;
    if (strcmp(labelName, anotherCurrentNode->name) == 0)
    { // delete first
      circuit->head = anotherCurrentNode->next;
      free(anotherCurrentNode);
    }
    else
    { // not first
      while ((anotherCurrentNode->next) != NULL)
      {
        if (strcmp(labelName, (anotherCurrentNode->next)->name) == 0)
        {
          anotherCurrentNode->next = (anotherCurrentNode->next)->next;
        }
        else
        {
          anotherCurrentNode = anotherCurrentNode->next;
        }
      }

      // free(anotherCurrentNode);
    }
    // TODO: Implement the remove function
  }
}

void handleCurrentCal(LinkedList *circuit, int voltage)
{
  printf("The current in the circuit is %.6lfA\n", calcCurrent(circuit, voltage));
}

void handleVoltage(LinkedList *circuit, int voltage)
{
  printf("What's the label of the resistor you want to find the voltage across: ");
  char labelName[STRING_MAX];
  readInputString(labelName, STRING_MAX);
  Node *counter = circuit->head;

  if (checkSameName(circuit, labelName))
  {
    while (counter != NULL)
    {
      if (strcmp(labelName, counter->name) == 0)
      {
        printf("Voltage across resistor is %.6lfV", calcCurrent(circuit, voltage) * counter->value);
        break;
      }
      counter = counter->next;
    }
  }
  else
  {
    printf("The resistor with %s label does not exist.\n", labelName);
  }
}

void handlePrint(LinkedList *circuit)
{
  Node *current = circuit->head;
  while (current != NULL)
  {
    printf("%s  %d Ohms\n", current->name, current->value);
    current = current->next;
  }
}

void handleQuit(LinkedList *circuit)
{
  printf("Removing all resistors in the circuit...\n");
  handlePrint(circuit);

  if (circuit->head != NULL)
  {
    while ((circuit->head)->next != NULL)
    {
      Node *currentNode = circuit->head;
      circuit->head = currentNode->next;
      free(currentNode);
    }
  }
  circuit->head = NULL;
}
