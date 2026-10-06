#include <stdio.h>
#include <string.h>
#include "funcs.h"

// Prints grade, grade percentage, and average grade
void print_grades(subject *grade_arr, int arr_len, float avg_grade, const char *student_name) 
{
    if (grade_arr != NULL) 
    {
        printf("*****************************************\n");
        printf("Student: %s\n", student_name);
        printf("-----------------------------------------\n");
        printf("%-20s %7s %12s\n", "Subject", "Grade", "Percentage");
        printf("-----------------------------------------\n");  
        for (int i = 0; i < arr_len; i++) 
        {
            printf("%-20s %7d %12d\n", grade_arr[i].name, grade_arr[i].grade, grade_arr[i].grade_prcnt);
        }
        printf("\nAverage grade: %5.2f\n", avg_grade); 
        printf("-----------------------------------------\n"); 
    }

}


// Writes the calculated + individual grades into const char *output file
// Returns true if succeeds
// Returns false if out file == NULL or *grade_arr == NULL
bool save_grades(subject *grade_arr, int arr_len, float avg_grade, const char *student_name, const char *output_file) 
{
    FILE *out_file = NULL; 
    out_file = fopen(output_file, "w");
    if (out_file == NULL || grade_arr == NULL) 
    {
        // Couldn't open file specified
        return false;
    }
    else 
    {
        fprintf(out_file, "*****************************************\n");
        fprintf(out_file, "Student: %s\n", student_name);
        fprintf(out_file, "-----------------------------------------\n");
        fprintf(out_file, "%-20s %7s %12s\n", "Subject", "Grade", "Percentage");
        fprintf(out_file, "-----------------------------------------\n");  
        for (int i = 0; i < arr_len; i++) 
        {
            fprintf(out_file, "%-20s %7d %12d\n", grade_arr[i].name, grade_arr[i].grade, grade_arr[i].grade_prcnt);
        }
        fprintf(out_file, "\nAverage grade:%5.2f\n", avg_grade); 
        fprintf(out_file, "-----------------------------------------\n"); 
        fclose(out_file);
        return true;
    }
}

void print_percentages(void) 
{
    printf("grade: percentages\n");
    printf("o 5: 90-100\no 4: 80-89\no 3: 70-79\no 2: 60-69\no 1: 50-59\no 0: Below 50\n");
}
void print_start(void) 
{
    printf("Welcome to StuGrade\nThe calculator for your grades\n");
    printf("Please enter your name!\n");
}

// 'Converts' the grades from percentage to decimal
/* Uses the following convertion table
o 5 <= 90-100
o 4 <= 80-89
o 3 <= 70-79
o 2 <= 60-69
o 1 <= 50-59
o 0: Below 50
*/
// Returns the grade if succesfull, else 0
int convert_grade(int percentage)
{
    int rows = 5;
    int cols = 11;
    int grade_table[5][11] = {
                             {50, 51, 52, 53, 54, 55, 56, 57, 58, 59},     // 1st index = grade 1
                             {60, 61, 62, 63, 64, 65, 66, 67, 68, 69},     // 2nd index = grade 2
                             {70, 71, 72, 73, 74, 75, 76 ,77,78, 79},      // 3rd index = grade 3
                             {80, 81, 82, 83, 84, 85, 86, 87, 88, 89},     // 4th index = grade 4
                             {90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100} // 5th index = grade 5
                             };
    int grade = 0;
    if (percentage < 50) 
    {
        grade = 0;
        return grade;
    }
    else 
    {
        for (int i = 0; i < rows; i++) 
        {
            for (int j = 0; j < cols; j++)
            {
                if(percentage == grade_table[i][j]) 
                {
                    grade = i + 1;
                }
            }
        }
        return grade;
    }
}

// Reads a string with fgets which gets saved to *str 
//*str is the variable where the read string is placed, max_str_len
void read_string(char *str, int str_len) 
{
    fgets(str, str_len, stdin);
    // Removing linefeed from string
    bool removed = remove_lf(str);
    if (removed == false)
    {
        printf("Clearing input buffer...\nToo many characters were entered\n");
        clear_ib();
    }
}

// Returns true if succesfully removes newline char
// Returns false if pointer is NULL, 
// Also returns false if fgets can't read the whole str
bool remove_lf(char *str) 
{
    if (str != NULL && strlen(str) != 0) 
    {   // Replacing newline with linefeed
        if (str[strlen(str) - 1] == '\n') 
        {
            str[strlen(str) - 1 ] = '\0';
            return true;
        }
        else 
        {
            return false;
        }
    }
    else 
    {
        return false;
    }
}


// clears the input buffer
void clear_ib(void) 
{
    while (getchar() != '\n');
}

// Reads a number from stdinput
// Returns the number if read else returns 0 
int read_number(const char *prompt)
{
    int number = 0;
    int *pnum = &number;
    char input[32];
    printf("%s", prompt);
    fgets(input, 32, stdin);
    bool parsed = parse_number(input, pnum);
    if (parsed) 
    {
      //printf("Parsed(%d) input %d\n", parsed, number);
      return number;  
    }
    else if (!parsed)
    {
        //printf("Parsed(%d) input %d\n", parsed, number);
        return -1;
    }
    else 
    {
        return -2;
    }
}   

// parses a number from char to int
// Returns the number if parsed else returns 0
bool parse_number(char *input, int *pnum) 
{
    if (sscanf(input, "%d", pnum) == 1) 
    {
        return true;    
    } else 
    {
        printf("Parsing failed\n");
        return false;
    }
}

// Function that reads a number, and checks if its in range of int low, int high
// Returns false if number out of range
// Else returns number 
// Saves the read number to *pnum
bool read_range(int low, int high, int *pnum)
{
    printf("Enter a number between (%d - %d)", low, high);
    int number = read_number("\n");
    if (number < low || number > high) 
    {
        *pnum = number; // 'returns' read value anyway
        return false;
    }
    else if (number >= low && number <= high)
    {
        //printf("Number is in range\n");
        *pnum = number;
        return true;
    }
}

// Calculates average from array of subject structs
float calc_avg(subject *sub_arr, int len)
{
    if (len != 0) 
    {
        int sum = 0;
        for (int i = 0; i < len; i++) 
        {
            sum += sub_arr[i].grade; 
        }
        return (float) sum / len;
    }
    else 
    {
        return 0;
    }
    
}