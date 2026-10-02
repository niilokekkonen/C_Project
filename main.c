#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "funcs.h"
#include "funcs.c"

#define NAME_LEN 50
#define SUBJECT_LEN 50
#define MAX_PRCNT 100
#define LOW_PRCNT 0

/*
Student grade calculator
Write a program that calculates and displays the final grades for a student based on their scores in
different subjects. The program should allow the user to input scores for multiple subjects and then
calculate the average grade and overall grade for the student.

Requirements:

• The program should start by asking the user for their name.

• Then, it should ask the user how many subjects they want to calculate grades for.

• For each subject, the program should prompt the user to enter the subject name and the score (as a percentage).

• Calculate the average grade based on the scores and display it.
• Determine and display the overall grade based on the following grading scale:
o 5: 90-100
o 4: 80-89
o 3: 70-79
o 2: 60-69
o 1: 50-59
o 0: Below 50
• The program must also write the same report to a file

# PLAN for execution
# Needed functions read_string, read_number, calc_avg, calc_grade from percentage, print_menu

# Vision for functionality.
1. Program starts and asks, the name with read string. (Validate input)
2. Then asks for amount of subjects(Validate input for int)
3. then starts prompting the user for subject name, and grade,
   as a percentage(valid int, and in range of 0 -> 100. if less than 50 grade = 0)'

4. Then program prints the calculated avg, and overall grade in a nice format
5. before program closes the data will be saved in a file(Ask filename from user)
*/


int main(void) 
{
    // Init string arrays
    char name[NAME_LEN] = {'\n'}; 
    int subject_cnt = 0;
    float avg_grade = 0;
    // Starting program
    print_start();
    read_string(name, NAME_LEN);
    if (name[0] == '\n') 
    {
        printf("Reading the name failed");
        return 1;
    }
    else 
    {
        printf("How many subjects you want to include in the average?");
        subject_cnt = read_number("\n");
        if (subject_cnt > 0) 
        {   
            subject sub_arr[subject_cnt]; // Creating struct_array for easy data management
            int read_subjects = 0; // The amount of asked subjects
            int read_num = 0;
            int *pread = &read_num;
            bool in_range = false;
            print_percentages();
            for (read_subjects; read_subjects < subject_cnt; read_subjects++) 
            {

                printf("Enter subject %d name\n", read_subjects + 1);
                read_string(sub_arr[read_subjects].name, SUBJECT_LEN);
                printf("Enter subject %d grade percentage\n",read_subjects + 1);
                in_range = read_range(LOW_PRCNT, MAX_PRCNT, pread);
                    if (in_range != false) 
                    {
                        sub_arr[read_subjects].grade_prcnt = *pread;
                    }          
                    else 
                    {
                        sub_arr[read_subjects].grade_prcnt = 0;
                        printf("Grade not in range(%d - %d)\nTry entering a valid number\n", LOW_PRCNT, MAX_PRCNT);
                        read_subjects--; // Not moving forward until a valid grade has been passed
                    }
              //  printf("Sub_name: %s, sub_gradePRCNT: %d\n", sub_arr[read_subjects].name, sub_arr[read_subjects].grade_prcnt);
            }
            // Now we have read all the grades
            // Going through the list of structures to convert grades, and save it back to
            for (int i = 0; i < read_subjects; i++) 
            {
                int prcnt = sub_arr[i].grade_prcnt;
                sub_arr[i].grade = convert_grade(prcnt);
            }
            avg_grade = calc_avg(sub_arr, subject_cnt);
            print_grades(sub_arr, subject_cnt, avg_grade, name);
            return 0;
        }
        else 
        {
            printf("Couldn't read subject count\nEnter a valid number");
            return 2;
        }

    }

}