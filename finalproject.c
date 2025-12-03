#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VOTERS 100
#define CANDIDATE_COUNT 4

/* ----------------- Structures ----------------- */
// Structure to store voter information
struct Voter {
    int voterID;
    char name[50];
    char fatherName[50];
    char address[100];
    char gender[10];
    int age;
    int hasVoted;   // 0 = not voted, 1 = voted
};

// Structure object array
struct Voter voters[MAX_VOTERS];
int voterCount = 0;

// Candidate names
char candidateNames[CANDIDATE_COUNT][50] = {
    "Sambhav",
    "Jashan",
    "Chahat",
    "Raghav"
};

// Candidate vote counts
int votes[CANDIDATE_COUNT] = {0};


/* ---------------- Function Prototypes ---------------- */
void menu();
void registerVoter();
void showVoters();
void castVote();
int findVoter(int id);
void showTotalVotes();
void showWinner();


/* ---------------- Main Function ---------------- */
int main() {
    int choice;

    while (1) {
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: registerVoter(); break;
            case 2: showVoters(); break;
            case 3: castVote(); break;
            case 4: showTotalVotes(); break;
            case 5: showWinner(); break;
            case 0:
                printf("\nExiting... Thank you!\n");
                exit(0);

            default:
                printf("Invalid choice! Try again.\n");
        }

        printf("\nPress Enter to continue...");
        getchar();
        getchar();
    }

    return 0;
}


/* ---------------- Menu Function ---------------- */
void menu() {
    printf("\n==============================\n");
    printf("       VOTING SYSTEM\n");
    printf("==============================\n");
    printf("1. Register Voter\n");
    printf("2. Show All Voters\n");
    printf("3. Cast Vote\n");
    printf("4. Show Total Votes\n");
    printf("5. Show Winner\n");
    printf("0. Exit\n");
    printf("==============================\n");
}


/* ---------------- Register New Voter ---------------- */
void registerVoter() {
    if (voterCount >= MAX_VOTERS) {
        printf("Voter limit reached! Cannot register more.\n");
        return;
    }

    struct Voter v;

    printf("\nEnter Voter ID: ");
    scanf("%d", &v.voterID);

    printf("Enter Name: ");
    scanf("%s", v.name);

    printf("Enter Father's Name: ");
    scanf("%s", v.fatherName);

    printf("Enter Address: ");
    scanf("%s", v.address);

    printf("Enter Gender (Male/Female/Other): ");
    scanf("%s", v.gender);

    printf("Enter Age: ");
    scanf("%d", &v.age);

    if (v.age < 18) {
        printf("Voter must be 18 or above!\n");
        return;
    }

    v.hasVoted = 0;

    voters[voterCount++] = v;

    printf("\nVoter registered successfully!\n");
}


/* ---------------- Display All Voters ---------------- */
void showVoters() {
    if (voterCount == 0) {
        printf("No voters registered.\n");
        return;
    }

    printf("\n------ Voter List ------\n");
    for (int i = 0; i < voterCount; i++) {
        printf("\nVoter %d:\n", i + 1);
        printf("ID          : %d\n", voters[i].voterID);
        printf("Name        : %s\n", voters[i].name);
        printf("Father Name : %s\n", voters[i].fatherName);
        printf("Address     : %s\n", voters[i].address);
        printf("Gender      : %s\n", voters[i].gender);
        printf("Age         : %d\n", voters[i].age);
        printf("Voted       : %s\n", voters[i].hasVoted ? "YES" : "NO");
    }
}


/* ---------------- Cast Vote ---------------- */
void castVote() {
    int id;
    printf("\nEnter your Voter ID: ");
    scanf("%d", &id);

    int index = findVoter(id);

    if (index == -1) {
        printf("Voter not found! Please register first.\n");
        return;
    }

    if (voters[index].hasVoted == 1) {
        printf("You have already voted. Voting again is not allowed!\n");
        return;
    }

    printf("\nChoose your candidate:\n");
    for (int i = 0; i < CANDIDATE_COUNT; i++) {
        printf("%d. %s\n", i + 1, candidateNames[i]);
    }

    int choice;
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > CANDIDATE_COUNT) {
        printf("Invalid candidate choice!\n");
        return;
    }

    votes[choice - 1]++;   
    voters[index].hasVoted = 1; 

    printf("Your vote has been recorded. Thank you!\n");
}


/* ---------------- Find Voter by ID ---------------- */
int findVoter(int id) {
    for (int i = 0; i < voterCount; i++) {
        if (voters[i].voterID == id)
            return i;
    }
    return -1;
}


/* ---------------- Show Total Votes ---------------- */
void showTotalVotes() {
    printf("\n------ Vote Count ------\n");
    for (int i = 0; i < CANDIDATE_COUNT; i++) {
        printf("%s : %d votes\n", candidateNames[i], votes[i]);
    }
}


/* ---------------- Show Winner ---------------- */
void showWinner() {
    int max = -1, winner = -1, tie = 0;

    for (int i = 0; i < CANDIDATE_COUNT; i++) {
        if (votes[i] > max) {
            max = votes[i];
            winner = i;
            tie = 0;
        }
        else if (votes[i] == max) {
            tie = 1;
        }
    }

    printf("\n------ Election Result ------\n");

    if (tie == 1) {
        printf("It's a tie! No clear winner.\n");
    } else {
        printf("Winner: %s with %d votes.\n", candidateNames[winner], max);
    }
}
