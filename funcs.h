// A simple school subject containing name, and grade in percentage
typedef struct subject
{
    char name[50];
    int grade_prcnt;
    int grade; 

} subject;

float calc_avg(subject *sub_arr, int len);
bool read_range(int low, int high, int *pnum);
bool parse_number(char *input, int *pnum);
bool read_number(const char *prompt, int *pnum);
void clear_ib(void);
bool remove_lf(char *str);
void read_string(char *str, int str_len);
void print_start(void);
int convert_grade(int percentage);
bool save_grades(subject *grade_arr, int arr_len, float avg_grade, const char *student_name, const char *output_file); 
void print_grades(subject *grade_arr, int arr_len, float avg_grade, const char *student_name); 
void print_percentages(void); 