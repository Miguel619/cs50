#include <stdio.h>
#include <stdbool.h> 
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
char candidates[MAX][20];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, char *name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool check_lock(int origin, int loser);

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        strcpy(candidates[i], argv[i + 1]);
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count;
    printf("Number of voters: ");
    scanf("%i", &voter_count);
    char names[voter_count * candidate_count][20];
    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            printf("Rank %i: ", j + 1);
            scanf("%s", names[i+j]);

            if (!vote(j, names[i+j], ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, char *name, int ranks[])
{
    //for every candidate
    for(int i = 0; i < candidate_count; i++){
        // if candidate 0 == name add 0 to pref array
        if(strcmp(candidates[i], name) == 0){
            // store in ranks array
            ranks[rank] = i;
            return true;
        }
    }
    return false;
    
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // record i over j
    // store size of ranks
    int pyr = candidate_count;
    for(int i = 0; i < candidate_count; i++){
        for(int j = i + 1; j < pyr; j++){
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // compare [i, j] to [j, i]
    
    for(int i = 0; i < candidate_count; i++){
        for(int j = 0; j < candidate_count; j++){
            if(preferences[i][j] > preferences[j][i]){
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // sort in decreasing strength of victory
    // bubble sort
    bool sw = true;
    int least = 0;
    int ta;
    int tb;
    while(sw){
        sw = false;
        least = preferences[pairs[0].winner][pairs[0].loser] - preferences[pairs[0].loser][pairs[0].winner];
        for(int i = 0; i < pair_count - 1; i++){
            if(preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner] < preferences[pairs[i+1].winner][pairs[i+1].loser] - preferences[pairs[i+1].loser][pairs[i+1].winner]){
                ta = pairs[i+1].winner;
                tb = pairs[i+1].loser;
                pairs[i+1].winner = pairs[i].winner;
                pairs[i+1].loser = pairs[i].loser;
                pairs[i].winner = ta;
                pairs[i].loser = tb;
                sw = true;
            }
        }
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for(int i = 0; i < pair_count; i++){
        if(check_lock(pairs[i].winner, pairs[i].loser) == true){
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}
// check if loser creates loop
bool check_lock(int origin, int loser){
    // check for cycle
    if(origin == loser){
        return false;
    }
    //check if loser is a winner somewhere else
    for(int i = 0; i < pair_count; i++){
            if(locked[loser][i] == true){
                return check_lock(origin, i);
            }
    }
    return true;

}

// Print the winner of the election
void print_winner(void)
{
    bool win = true;
    for(int i = 0; i < pair_count; i++){
        for(int j = 0; j < pair_count; j++){
            if(locked[j][i] == true){
                win = false;
            }
        }
        if(win == true){
            printf("%s\n", candidates[i]);
        }
        win = true;
    }
    return;
}

