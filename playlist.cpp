#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Song {
    char title[100];
    char artist[100];
    char genre[50];
    struct Song *next;
    struct Song *prev;
} Song;
typedef struct Playlist 
{
    Song *head;
    Song *tail;
    Song *current;
} Playlist;
Song* createSong(char *title, char *artist, char *genre) 
{
    Song *newSong = (Song *)malloc(sizeof(Song));
    strcpy(newSong->title, title);
    strcpy(newSong->artist, artist);
    strcpy(newSong->genre, genre);
    newSong->next = NULL;
    newSong->prev = NULL;
    return newSong;
}
void addSong(Playlist *playlist, char *title, char *artist, char *genre) 
{
    Song *newSong = createSong(title, artist, genre);
    if (playlist->tail == NULL) 
	{
        playlist->head = newSong;
        playlist->tail = newSong;
    } 
	else 
	{
        playlist->tail->next = newSong;
        newSong->prev = playlist->tail;
        playlist->tail = newSong;
    }
}
void playNext(Playlist *playlist) 
{
    if (playlist->current != NULL && playlist->current->next != NULL) 
	{
        playlist->current = playlist->current->next;
        printf("Playing: %s by %s\n", playlist->current->title, playlist->current->artist);
    } 
	else 
	{
        printf("You are at the end of the playlist.\n");
    }
}
void playPrevious(Playlist *playlist) 
{
    if (playlist->current != NULL && playlist->current->prev != NULL) 
	{
        playlist->current = playlist->current->prev;
        printf("Playing: %s by %s\n", playlist->current->title, playlist->current->artist);
    } 
	else 
	{
        printf("You are at the beginning of the playlist.\n");
    }
}
void switchToSong(Playlist *playlist, char *title) 
{
    Song *temp = playlist->head;
    while (temp != NULL) 
	{
        if (strcmp(temp->title, title) == 0) 
		{
            playlist->current = temp;
            printf("Switched to: %s by %s\n", playlist->current->title, playlist->current->artist);
            return;
        }
        temp = temp->next;
    }
    printf("Song not found in the playlist.\n");
}
void displayByGenre(Playlist *playlist, char *genre) 
{
    Song *temp = playlist->head;
    printf("Songs in genre '%s':\n", genre);
    while (temp != NULL) {
        if (strcmp(temp->genre, genre) == 0) 
		{
            printf("%s by %s\n", temp->title, temp->artist);
        }
        temp = temp->next;
    }
}
void initPlaylist(Playlist *playlist) 
{
    playlist->head = NULL;
    playlist->tail = NULL;
    playlist->current = NULL;
}
int main() 
{
    Playlist myPlaylist;
    initPlaylist(&myPlaylist);
    addSong(&myPlaylist, "Song A", "Artist A", "Rock");
    addSong(&myPlaylist, "Song B", "Artist B", "Pop");
    addSong(&myPlaylist, "Song C", "Artist C", "Rock");
    myPlaylist.current = myPlaylist.head;
    printf("Starting with: %s by %s\n", myPlaylist.current->title, myPlaylist.current->artist);
    playNext(&myPlaylist);
    playNext(&myPlaylist);
    playPrevious(&myPlaylist);
    switchToSong(&myPlaylist, "Song A");
    displayByGenre(&myPlaylist, "Rock");
    return 0;
}
