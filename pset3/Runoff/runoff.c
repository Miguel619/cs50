#include <stdio.h>
#include <string.h>
#include <stdbool.h> 
#include <math.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    char name[20];
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, char *name);
void tabulate(int voter_count);
bool print_winner(int candidate_count, int voter_count);
int find_min(int candidate_count);
bool is_tie(int min, int candidate_count);
void eliminate(int min, int candidate_count);

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        strcpy(candidates[i].name, argv[i + 1]);
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    int voter_count;
    printf("Number of voters: ");
    scanf("%i", &voter_count);
    char names[voter_count * candidate_count][20];
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {
        printf("Ballot #%i\n", i + 1);
        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            printf("Rank %i: ", j + 1);
            scanf("%s", names[i+j]);

            // Record vote, unless it's invalid
            if (!vote(i, j, names[i+j]))
            {
                printf("Invalid vote.\n");
                return 4;
            }
            
        }
        
        printf("\n");
    }
    
    // Keep holding runoffs until winner exists
    while (true)
    {
        
        // Calculate votes given remaining candidates
        tabulate(voter_count);
        // Check if election has been won
        bool won = print_winner(candidate_count, voter_count);
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min(candidate_count);
        bool tie = is_tie(min, candidate_count);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min, candidate_count);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, char *name)
{
    for(int i = 0; i < candidate_count; i++){
        // if candidate 0 == name add 0 to pref array
        if(strcmp(candidates[i].name, name) == 0){
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(int voter_count)
{
    int j;
    for(int i = 0; i < voter_count; i++){
        j = 0;
        while(candidates[preferences[i][j]].eliminated == true){
            j++;
        }
        candidates[preferences[i][j]].votes++;
    }   
}

// Print the winner of the election, if there is one
bool print_winner(int candidate_count, int voter_count)
{
    int top = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if(candidates[i].votes > top){
            top = candidates[i].votes;
        }
    }
    if(top > round(voter_count/2)){
        for (int i = 0; i < candidate_count; i++)
        {
            if(candidates[i].votes == top){
                printf("%s\n", candidates[i].name);
            }
        }
        return true;
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(int candidate_count)
{
    int min = candidates[0].votes;
    for (int i = 0; i < candidate_count; i++)
    {
        if(candidates[i].votes < min){
            min = candidates[i].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min, int candidate_count)
{
    int loser = 0;
    int remain = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if(candidates[i].eliminated == false){
            remain++;
        }
        if(candidates[i].votes == min){
            loser++;
        }
    }
    if(loser == remain){
        
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min, int candidate_count)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if(candidates[i].votes == min){
            candidates[i].eliminated = true;
        }
    }
    return;
}
