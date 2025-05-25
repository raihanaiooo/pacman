#define MAX_NAME_LENGTH 50
#define MAX_ENTRIES 5
typedef struct 
{
    char name[MAX_NAME_LENGTH];
    int score;
} Leaderboard;

void loadLeaderboard(Leaderboard entries[], int *count);
void saveLeaderboard(Leaderboard entries[], int count);
void updateLeaderboard(const char *playerName, int score);
void displayLeaderboard();