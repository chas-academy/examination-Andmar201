#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUM_STUDENTS 5
#define NUM_TESTS 13
#define NAME_LEN 11 


void Capitalize(char* name) {
    if (name[0] != '\0') {
        name[0] = toupper(name[0]);
        for (int i = 1; name[i] != '\0'; i++) {
            name[i] = tolower(name[i]);
        }
    }
}


int IsAllLetters(const char* s) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (!isalpha((unsigned char)s[i]))
            return 0;
    }
    return 1;
}

int main() {
    char names[NUM_STUDENTS][NAME_LEN];
    int scores[NUM_STUDENTS][NUM_TESTS];
    double averages[NUM_STUDENTS];
    double totalSum = 0;

  
    for (int i = 0; i < NUM_STUDENTS; i++) {
        
        while (1) {
            printf("Enter name for student %d (max 10 letters, a-z): ", i + 1);
            fgets(names[i], NAME_LEN, stdin);
            // Remove newline
            names[i][strcspn(names[i], "\n")] = '\0';
            if (strlen(names[i]) > 0 && strlen(names[i]) <= 10 && IsAllLetters(names[i])) {
              
                for (int k = 0; names[i][k]; k++)
                    names[i][k] = tolower(names[i][k]);
                break;
            } else {
                printf("Invalid name. Please use only letters (a-z) and max 10 characters.\n");
            }
        }

        for (int j = 0; j < NUM_TESTS; j++) {
            while (1) {
                printf("Enter result %d for %s (0-100): ", j + 1, names[i]);
                char buf[16];
                int score;
                if (fgets(buf, sizeof(buf), stdin) && sscanf(buf, "%d", &score) == 1 && score >= 0 && score <= 100) {
                    scores[i][j] = score;
                    break;
                } else {
                    printf("Invalid score. Please enter an integer between 0 and 100.\n");
                }
            }
        }
    }


    for (int i = 0; i < NUM_STUDENTS; i++) {
        int sum = 0;
        for (int j = 0; j < NUM_TESTS; j++) {
            sum += scores[i][j];
        }
        averages[i] = sum / (double)NUM_TESTS;
        totalSum += averages[i];
    }

    int maxIdx = 0;
    for (int i = 1; i < NUM_STUDENTS; i++) {
        if (averages[i] > averages[maxIdx])
            maxIdx = i;
    }

  
    Capitalize(names[maxIdx]);
    printf("\nStudent with highest average: %s\n", names[maxIdx]);

    
    double groupAvg = totalSum / NUM_STUDENTS;

   
    int anyBelow = 0;
    printf("\nStudents with average below group average:\n");
    for (int i = 0; i < NUM_STUDENTS; i++) {
        if (averages[i] < groupAvg) {
            Capitalize(names[i]);
            printf("%s\n", names[i]);
            anyBelow = 1;
        }
    }
    if (!anyBelow) {
        printf("None\n");
    }

    return 0;
}