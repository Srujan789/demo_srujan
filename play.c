#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song {
    char title[50];
    char artist[50];
    int duration; // Duration in seconds
} Song;

typedef struct SongNode {
    Song song;
    struct SongNode* next;
    struct SongNode* prev;
} SongNode;

typedef struct Playlist {
    SongNode* head;
    SongNode* tail;
    SongNode* current; // Pointer to the current song
} Playlist;

// Function to create a new song node
SongNode* createSongNode(const char* title, const char* artist, int duration) {
    SongNode* newNode = (SongNode*)malloc(sizeof(SongNode));
    if (!newNode) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    strcpy(newNode->song.title, title);
    strcpy(newNode->song.artist, artist);
    newNode->song.duration = duration;
    newNode->next = newNode->prev = NULL;
    return newNode;
}

// Function to initialize the playlist
void initializePlaylist(Playlist* playlist) {
    playlist->head = playlist->tail = playlist->current = NULL;
}

// Function to add a song to the playlist
void addSong(Playlist* playlist, const char* title, const char* artist, int duration) {
    SongNode* newNode = createSongNode(title, artist, duration);
    if (playlist->head == NULL) {
        playlist->head = playlist->tail = playlist->current = newNode;
    } else {
        playlist->tail->next = newNode;
        newNode->prev = playlist->tail;
        playlist->tail = newNode;
    }
    printf("Added: %s by %s (%ds)\n", title, artist, duration);
}

// Function to display all songs in the playlist
void displayPlaylist(const Playlist* playlist) {
    printf("Playlist:\n");
    SongNode* temp = playlist->head;
    while (temp != NULL) {
        printf("%s by %s (%ds)\n", temp->song.title, temp->song.artist, temp->song.duration);
        temp = temp->next;
    }
}

// Function to play the current song
void playCurrentSong(const Playlist* playlist) {
    if (playlist->current != NULL) {
        printf("Now playing: %s by %s (%ds)\n", playlist->current->song.title, 
                                                 playlist->current->song.artist, 
                                                 playlist->current->song.duration);
    } else {
        printf("The playlist is empty.\n");
    }
}

// Function to play the next song
void playNextSong(Playlist* playlist) {
    if (playlist->current != NULL && playlist->current->next != NULL) {
        playlist->current = playlist->current->next;
        playCurrentSong(playlist);
    } else {
        printf("No next song. End of playlist.\n");
    }
}

// Function to play the previous song
void playPreviousSong(Playlist* playlist) {
    if (playlist->current != NULL && playlist->current->prev != NULL) {
        playlist->current = playlist->current->prev;
        playCurrentSong(playlist);
    } else {
        printf("No previous song. Start of playlist.\n");
    }
}

// Function to remove a song by title
void removeSong(Playlist* playlist, const char* title) {
    SongNode* temp = playlist->head;
    while (temp != NULL) {
        if (strcmp(temp->song.title, title) == 0) {
            if (temp->prev != NULL) temp->prev->next = temp->next;
            if (temp->next != NULL) temp->next->prev = temp->prev;

            if (temp == playlist->head) playlist->head = temp->next;
            if (temp == playlist->tail) playlist->tail = temp->prev;
            if (temp == playlist->current) playlist->current = temp->next ? temp->next : temp->prev;

            free(temp);
            printf("Removed: %s\n", title);
            return;
        }
        temp = temp->next;
    }
    printf("Song with title '%s' not found.\n", title);
}

// Function to free the entire playlist
void freePlaylist(Playlist* playlist) {
    SongNode* temp = playlist->head;
    while (temp != NULL) {
        SongNode* next = temp->next;
        free(temp);
        temp = next;
    }
    playlist->head = playlist->tail = playlist->current = NULL;
    printf("Playlist cleared and its empty.\n");
}

int main() {
    Playlist playlist;
    initializePlaylist(&playlist);

    int choice;
    char title[50], artist[50];
    int duration;

    do {
        printf("\nPlaylist Menu:\n");
        printf("1. Add Song\n");
        printf("2. Display Playlist\n");
        printf("3. Play Current Song\n");
        printf("4. Play Next Song\n");
        printf("5. Play Previous Song\n");
        printf("6. Remove Song\n");
        printf("7. Clear Playlist\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter song title: ");
                scanf(" %[^\n]", title);  // Read until newline
                printf("Enter artist name: ");
                scanf(" %[^\n]", artist);
                printf("Enter duration (in seconds): ");
                scanf("%d", &duration);
                addSong(&playlist, title, artist, duration);
                break;

            case 2:
                displayPlaylist(&playlist);
                break;

            case 3:
                playCurrentSong(&playlist);
                break;

            case 4:
                playNextSong(&playlist);
                break;

            case 5:
                playPreviousSong(&playlist);
                break;

            case 6:
                printf("Enter the title of the song to remove: ");
                scanf(" %[^\n]", title);
                removeSong(&playlist, title);
                break;

            case 7:
                freePlaylist(&playlist);
                break;

            case 8:
                printf("Exiting...\n");
                freePlaylist(&playlist);
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 8);

    return 0;
}

