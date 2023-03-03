#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};

typedef struct node node;

node *newNode(int value){
    node *newNode = malloc(sizeof(node));
    newNode->data = value;
    newNode->next = NULL;

    return newNode;
}

void reverse(node** head){
    node *prev = NULL;
    node *curr = *head;
    node *next = NULL;

    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *head = prev;
}

void printLinkedList(node *curr) {
    reverse(&curr);

    while(curr != NULL ){
        printf("%d", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

void multiplication(node *headOfNumb1,node *headOfNumb2, node **headOfResult,int base){
    node *currNum1 = headOfNumb1;
    node *currNum2 = headOfNumb2;
    node *currResult = NULL;
    node *head = NULL;
    node *prevNode = NULL;

    while(currNum2 != NULL){
        while(currNum1 != NULL){
            int result = *headOfResult == NULL ? (currNum1->data * currNum2->data)%base : ((currNum1->data * currNum2->data)  + currResult->data)%base;
            int carry = *headOfResult == NULL ? (currNum1->data * currNum2->data)/base : ((currNum1->data * currNum2->data)  + currResult->data)/base;

            if(*headOfResult == NULL){
                prevNode = currResult = head = *headOfResult = newNode(result);
                currResult->next = newNode(carry);
            }
            else{
                if(currResult->next ==NULL){
                    currResult->next = newNode(0);
                }
                currResult->data = result;
                currResult->next->data = currResult->next->data + carry;
                prevNode = currResult;
            }
            currResult = currResult->next;
            currNum1 = currNum1->next;
        }
        currNum2 = currNum2->next;
        currNum1 = headOfNumb1;
        currResult = head = head->next;
    }
    if(prevNode->next->data == 0){
        prevNode->next = NULL;
    }
}

void readDigits(node **head, FILE **ptr) {
    node *currNode = *head;
    char digit = fgetc(*ptr);

    while (digit != '\n') {
        if (*head == NULL) {
            currNode = *head = newNode(digit - 48);
        } else {
            currNode->next = newNode(digit - 48);
            currNode = currNode->next;
        }
        digit = fgetc(*ptr);
    }
}

void conversionToDec(node *headOfNmb, node **headOfDec, int base){
    node *currNmb = headOfNmb;
    node *currResult= NULL;
    node* baseNode = newNode(base);
    node* tempPtr = NULL;
    node* headOfBase = newNode(1);
    node *currBase = headOfBase;
    node *prevNode = NULL;

    while(currNmb != NULL){
        while(currBase != NULL){
            int result = currResult == NULL ? (currNmb->data * currBase->data)%10 : ((currNmb->data * currBase->data) + currResult->data)%10;
            int carry = currResult == NULL ? (currNmb->data * currBase->data)/10 : (currNmb->data * currBase->data + currResult->data)/10;

            if(*headOfDec == NULL){
                prevNode = currResult = *headOfDec = newNode(result);
                currResult->next = newNode(carry);
            }
            else{
                if(currResult->next == NULL){
                    currResult->next = newNode(0);
                }
                currResult->data = result;
                currResult->next->data = currResult->next->data +carry;
                prevNode = currResult;
            }
            currResult  = currResult->next;
            currBase = currBase->next;
        }
        if(prevNode->next->data == 0){
            prevNode->next = NULL;
        }
        currResult = *headOfDec;
        currNmb = currNmb->next;

        tempPtr = NULL;
        multiplication(headOfBase, baseNode, &tempPtr, 10);
        headOfBase = tempPtr;
        currBase = headOfBase;
    }
}

int main() {
    node *headOfNumber1 = NULL;
    node *headOfNumber2 = NULL;
    node *headOfResult = NULL;

    node *headOfDecimalNmb1 = NULL;
    node *headOfDecimalNmb2 = NULL;
    node *headOfDecimalResult = NULL;

    FILE* input_file = fopen("input.txt", "r");

    readDigits(&headOfNumber1, &input_file);
    readDigits(&headOfNumber2, &input_file);

    int base;
    int base1 = fgetc(input_file);
    int base2 = fgetc(input_file);

    if(base2 == '\n'){
        base = base1 - 48;
    }else if (base1 == '1' && base2 == '0') {
        base = 10;
    }else{
        printf("The base value is not in the proper range.");
        exit(1);
    }
    fclose(input_file);

    reverse(&headOfNumber1);
    reverse(&headOfNumber2);
    multiplication(headOfNumber1, headOfNumber2, &headOfResult, base);

    conversionToDec(headOfNumber1, &headOfDecimalNmb1, base);
    conversionToDec(headOfNumber2, &headOfDecimalNmb2, base);
    conversionToDec(headOfResult, &headOfDecimalResult, base);

    printLinkedList(headOfNumber1);
    printLinkedList(headOfNumber2);
    printLinkedList(headOfResult);
    printLinkedList(headOfDecimalNmb1);
    printLinkedList(headOfDecimalNmb2);
    printLinkedList(headOfDecimalResult);
}