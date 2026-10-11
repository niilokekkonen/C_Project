# StuGrade, A students helper in grade calculation.
- Basic C project to calculate total average of subjects from grade percentages

# Main functionality
- Asks user to enter name, how many grades to include in calculating the average
and of course each subjects grade. 
- Calculates Average, prints all grades individually, and finally writes a summary in to a file
- Check program_flow.png to see how the program operates when the input is correct
- Converts the grades based on the following table below. Expects user to enter a percentage in range
``` 
5: 90-100
4: 80-89
3: 70-79
2: 60-69
1: 50-59
0: Below 50 
```

# Usage
- To use the program, all you need to do is clone or download the project.
- Navigate to the project folder and compile it in your terminal using GCC:
  `gcc main.c funcs.c -o stugrade`
- Or use any C compiler of your choosing.
- The expected output should look like max_science.txt.
