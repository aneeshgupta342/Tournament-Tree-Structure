#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node* next;
    struct Node* down;
    int p1Skill;
    int p2Skill;
} Node;

int max(int a, int b) {
    return a > b ? a : b;
}

Node* createNode(int p1Skill, int p2Skill) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->next = NULL;
    node->down = NULL;
    node->p1Skill = p1Skill;
    node->p2Skill = p2Skill;
    return node;
}

Node* createNextRound(Node* currentRound) {
    Node* nextRoundHead = NULL;
    Node* previousMatch = NULL;
    Node* currentMatch = currentRound;

    while (currentMatch != NULL) {
        Node* newMatch = NULL;

        if (currentMatch->next == NULL) {
            newMatch = createNode(max(currentMatch->p1Skill, currentMatch->p2Skill), -1000000000);
        } else {
            int w1 = max(currentMatch->p1Skill, currentMatch->p2Skill);
            int w2 = max(currentMatch->next->p1Skill, currentMatch->next->p2Skill);
            newMatch = createNode(w1, w2);
        }

        currentMatch->down = newMatch;
        if (currentMatch->next) {
            currentMatch->next->down = newMatch;
        }

        if (previousMatch) {
            previousMatch->next = newMatch;
        }
        previousMatch = newMatch;

        currentMatch = currentMatch->next ? currentMatch->next->next : NULL;

        if (nextRoundHead == NULL) {
            nextRoundHead = newMatch;
        }
    }

    return nextRoundHead;
}

Node* createFirstRound(int totalPlayers, int skills[]) {
    Node* head = NULL;
    Node* previousMatch = NULL;

    for (int i = 0; i < totalPlayers; i += 2) {
        Node* match = NULL;

        if (i == totalPlayers - 1) {
            match = createNode(skills[i], -1000000000);
        } else {
            match = createNode(skills[i], skills[i + 1]);
        }

        if (previousMatch) {
            previousMatch->next = match;
        }

        if (i == 0) {
            head = match;
        }

        previousMatch = match;
    }

    return head;
}

void simulateTournamentRounds(Node* round) {
    if (round == NULL || round->next == NULL) {
        return;
    }

    Node* nextRound = createNextRound(round);
    simulateTournamentRounds(nextRound);
}

int simulateTournament(int totalPlayers, int skills[]) {
    Node* firstRound = createFirstRound(totalPlayers, skills);
    simulateTournamentRounds(firstRound);

    Node* finalMatch = firstRound;
    while (finalMatch->down != NULL) {
        finalMatch = finalMatch->down;
    }

    printTournamentRounds(firstRound);
    return max(finalMatch->p1Skill, finalMatch->p2Skill);
}

void printTournamentRounds(Node* round) {
    int roundNumber = 1;
    while (round) {
        printf("Round %d:\n", roundNumber);
        Node* match = round;
        int matchNumber = 1;
        while (match != NULL) {
            printf("Match %d = ", matchNumber);
            if (match->p1Skill != -1000000000)
                printf("%d ", match->p1Skill);
            if (match->p2Skill != -1000000000)
                printf("%d ", match->p2Skill);
            printf("\n");
            match = match->next;
            matchNumber++;
        }
        printf("\n");
        round = round->down;
        roundNumber++;
    }
}

int main() {
    int totalPlayers;
    scanf("%d", &totalPlayers);
    int skills[totalPlayers];

    for (int i = 0; i < totalPlayers; i++) {
        scanf("%d", &skills[i]);
    }

    int winnerSkill = simulateTournament(totalPlayers, skills);
    printf("Winner(skill level) = %d\n", winnerSkill);

    return 0;
}
