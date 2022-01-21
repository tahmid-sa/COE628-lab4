/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Tahmid Sajin, EE Username: tsajin, COE628 Section 2, 500 830 210
 *
 * Created on February 14, 2021, 8:30 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

char childProcess[100];
char childProcessOne[100];
char childProcessTwo[100];

int main(int argc, char** argv)
{
    int count;
    int tmp = 0;
    int iterationPointerOne;
    int iterationPointerTwo = 0;
    int iterationPointerThree = 0;
    
    /*Prompt user for the pipe command*/
    printf("Enter pipe command:\n");
    fgets(childProcess, 100, stdin);
    
    /*Iterate through the childProcess to check if the pipe symbol had occurred.*/
    count = strlen(childProcess) - 1;
    for (iterationPointerOne = 0; iterationPointerOne < count; iterationPointerOne++){
        if(childProcess[iterationPointerOne] == '|') {
            tmp = 1;
            iterationPointerOne++;
        } else if (childProcess[iterationPointerOne] != '|' && tmp == 0){
            childProcessOne[iterationPointerTwo] = childProcess[iterationPointerOne];
            iterationPointerTwo++;
        } else {
            childProcessTwo[iterationPointerThree] = childProcess[iterationPointerOne];
            iterationPointerThree++;
        }
    }
    
    int directory[2];
    pipe(directory);
    
    /*Locate the directories and the amount of files*/
    if (fork() == 0){
        dup2(directory[1], 1);
        close(directory[0]);
        system(childProcessOne);
        exit(0);
    }
    else{
        dup2(directory[0], 0);
        close(directory[1]);
        system(childProcessTwo);
    }
    
    return (EXIT_SUCCESS);
}

