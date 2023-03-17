
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// main function
// print and writing output file
int main(int argc, char **argv)
{
    // local variables for input values
    double grade;
    double avg_grade;
    double sum_grade;
    double zero;
    double *temp_grades;

    // Global variables for grades store and calculating
    // store variable for grades
    double *grades;
    // first address variable for malloc of grades
    unsigned long init_address;

    // storing count
    int count;

    // reallocated count
    int alloc_count;

    // allocated and free number of malloc
    int allocs;
    int frees;

    // used bytes (40,80,120,240,...)
    int nUsed;

    // double's sizeof
    int d_size;
    // init alloc count
    int n = 5;

    // initialize for all variables
    zero = 0;
    avg_grade = 0;
    count = 0;
    alloc_count = n;
    allocs = 1;
    frees = 1;
    d_size = sizeof(double);
    nUsed = alloc_count;

    // Arguments processing
    if (argc > 2)
    {
        printf("Too many arguments supplied. Exiting. \n");
        exit(0);
    }

    else if (argc == 2)
    {
        // In case for Running with input files

        FILE *input_file;
        input_file = fopen(argv[1], "r");

        if (input_file == NULL)
        {
            printf("Input file does not exist. Exiting. \n");
            exit(0);
        }

        printf("Enter a list of grades below where each grade is separated by a newline character. After the last grade is entered, enter a negative value to end the list.\n");

        // Create a Heap with malloc of double type
        grades = (double *)malloc(alloc_count * d_size);
        init_address = (unsigned long)grades;

        // input value of each line from input.txt files
        char line[20];
        // Read each line until end
        while (fscanf(input_file,"%s",line) == 1)
        {
            grade = (double)atof(line);
            if (grade < 0)
            {
                // In case work stop and print with negative value
                if (count == 0)
                {
                    allocs = 0;
                    frees = 0;
                    d_size = 0;
                    printf("The average of 0 grades is %lf.\n", zero);
                }
                else
                {
                    // equal operator estimating
                    // average value calculating with values
                    char *eq_operator;
                    for (int i = 0; i < count; i++)
                    {
                        sum_grade += grades[i];
                    }
                    avg_grade = sum_grade / count;

                    printf("The average of %d grades is %lf.\n", count, avg_grade);

                    // compare with average value for each grade
                    for (int i = 0; i < count; i++)
                    {
                        if (grades[i] >= avg_grade)
                            eq_operator = ">=";
                        else
                            eq_operator = "<";

                        printf("%d. The grade of %lf is %s the average.\n", i + 1, grades[i], eq_operator);
                    }
                    printf("Freed %d bytes from the heap at 0x%lx.\n", d_size * alloc_count, (unsigned long)grades);
                }

                // heap free for malloc when end input
                free(grades);
                // calculating used total bytes
                if (count >= alloc_count)
                {
                    alloc_count = alloc_count + n;
                    nUsed = nUsed + alloc_count;
                }

                printf("total heap usage: %d allocs, %d frees, %d bytes allocated.\n", allocs, frees, d_size * nUsed);
                exit(0);
            }
            else
            {
                if (count < alloc_count)
                {
                    // In case the inputted grades is small than allocated count
                    grades[count] = grade;

                    if (count == 0)
                    {
                        printf("Allocated %d bytes to the heap at 0x%lx.\n", d_size * alloc_count, (unsigned long)grades);
                    }
                    printf("Stored %lf in the heap at 0x%lx.\n", grade, (unsigned long)&grades[count]);

                    count++;
                    if (count >= alloc_count)
                    {
                        // In case the inputted grades is larger than allocated count

                        printf("Stored %d grades (%d bytes) to the heap at 0x%lx.\n", count, count * 8, (unsigned long)grades);
                        printf("Heap at %lx is full.\n", (unsigned long)grades);

                        // calculating allocated count and used bytes
                        alloc_count = alloc_count + n;
                        nUsed = nUsed + alloc_count;

                        // realloc with extended heap
                        temp_grades = (double *)malloc(alloc_count * d_size);
                        if (temp_grades == NULL)
                        {
                            printf("Memory can't be allocated.\n");
                            free(grades);
                            exit(0);
                        }

                        // All grades copy with new extended heap
                        for (int i = 0; i < count; i++)
                        {
                            temp_grades[i] = grades[i];
                        }

                        allocs++;
                        frees++;

                        // before heap free
                        free(grades);

                        // copy with new heap
                        grades = temp_grades;

                        printf("Allocated %d bytes to the heap at 0x%lx.\n", alloc_count * d_size, (unsigned long)grades);
                        printf("Copied %d grades from 0x%lx to 0x%lx.\n", count, init_address, (unsigned long)grades);
                        printf("Freed %d bytes from the heap at 0x%lx.\n", (alloc_count - n) * d_size, init_address);

                        init_address = (unsigned long)grades;
                    }
                }
            }
        }
    }
    else
    {
        // In case for Input with user typing
        printf("Enter a list of grades below where each grade is separated by a newline character. After the last grade is entered, enter a negative value to end the list.\n");

        grades = (double *)malloc(alloc_count * d_size);
        init_address = (unsigned long)grades;

        while (scanf("%lf", &grade))
        {
            if (grade < 0)
            {
                // In case work stop and print with negative value
                if (count == 0)
                {
                    allocs = 0;
                    frees = 0;
                    d_size = 0;
                    printf("The average of 0 grades is %lf.\n", zero);
                }
                else
                {
                    // equal operator estimating
                    // average value calculating with values
                    char *eq_operator;
                    for (int i = 0; i < count; i++)
                    {
                        sum_grade += grades[i];
                    }
                    avg_grade = sum_grade / count;

                    printf("The average of %d grades is %lf.\n", count, avg_grade);

                    // compare with average value for each grade
                    for (int i = 0; i < count; i++)
                    {
                        if (grades[i] >= avg_grade)
                            eq_operator = ">=";
                        else
                            eq_operator = "<";

                        printf("%d. The grade of %lf is %s the average.\n", i + 1, grades[i], eq_operator);
                    }
                    printf("Freed %d bytes from the heap at 0x%lx.\n", d_size * alloc_count, (unsigned long)grades);
                }

                // heap free for malloc when end input
                free(grades);
                // calculating used total bytes
                if (count >= alloc_count)
                {
                    alloc_count = alloc_count + n;
                    nUsed = nUsed + alloc_count;
                }

                printf("total heap usage: %d allocs, %d frees, %d bytes allocated.\n", allocs, frees, d_size * nUsed);
                exit(0);
            }
            else
            {
                if (count < alloc_count)
                {
                    // In case the inputted grades is small than allocated count
                    grades[count] = grade;

                    if (count == 0)
                    {
                        printf("Allocated %d bytes to the heap at 0x%lx.\n", d_size * alloc_count, (unsigned long)grades);
                    }
                    printf("Stored %lf in the heap at 0x%lx.\n", grade, (unsigned long)&grades[count]);

                    count++;
                    if (count >= alloc_count)
                    {
                        // In case the inputted grades is larger than allocated count

                        printf("Stored %d grades (%d bytes) to the heap at 0x%lx.\n", count, count * 8, (unsigned long)grades);
                        printf("Heap at %lx is full.\n", (unsigned long)grades);

                        // calculating allocated count and used bytes
                        alloc_count = alloc_count + n;
                        nUsed = nUsed + alloc_count;

                        // realloc with extended heap
                        temp_grades = (double *)malloc(alloc_count * d_size);
                        if (temp_grades == NULL)
                        {
                            printf("Memory can't be allocated.\n");
                            free(grades);
                            free(temp_grades);
                            exit(0);
                        }

                        // All grades copy with new extended heap
                        for (int i = 0; i < count; i++)
                        {
                            temp_grades[i] = grades[i];
                        }

                        allocs++;
                        frees++;

                        // before heap free
                        free(grades);

                        // copy with new heap
                        grades = temp_grades;

                        printf("Allocated %d bytes to the heap at 0x%lx.\n", alloc_count * d_size, (unsigned long)grades);
                        printf("Copied %d grades from 0x%lx to 0x%lx.\n", count, init_address, (unsigned long)grades);
                        printf("Freed %d bytes from the heap at 0x%lx.\n", (alloc_count - n) * d_size, init_address);

                        init_address = (unsigned long)grades;
                    }
                }
            }
        }
    }
    return 0;
}
