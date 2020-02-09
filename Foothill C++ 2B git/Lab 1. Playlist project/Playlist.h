//
//  Playlist.hpp
//  C++ 2B Lab 1
//
//  Created by Niliang Lu on 6/30/19.
//  Copyright © 2019 Elaine. All rights reserved.
// Student ID: 20392734

#ifndef Playlist_h
#define Playlist_h


#include <string>
#include <stdio.h>

using namespace std;

class SongEntry {
private:
    int id;
    string name;

public:
    SongEntry(int theId = 0, string theName = "Unnamed") : id(theId), name(theName) {}  // test
    int get_id() const { return id; }
    string get_name() const { return name; }
    bool set_id(int id);
    bool set_name(string theName);
    friend class Tests; // Don't remove this line
};

class PlaylistNode {
private:
    SongEntry song;
    PlaylistNode *next;
public:
    PlaylistNode(const SongEntry& theSong=SongEntry()): song(theSong), next(nullptr) {}
    ~PlaylistNode(); // Do not free recursively
    const SongEntry& get_song() const { return song; }
    SongEntry* get_mutable_song() { return &song; }
    PlaylistNode *get_next() const { return next; }
    PlaylistNode *insert_next(PlaylistNode *p);
    PlaylistNode *remove_next();
    friend class Tests; // Don't remove this line
};

class Playlist {
private:
    PlaylistNode *head, *tail, *prevToCurr;
    int size;
    
public:
    Playlist();
    ~Playlist();
    int get_size() const { return size; }
    PlaylistNode *get_current_node() const;
    // The following return "this" on success, null on failure
    Playlist *clear();
    Playlist *rewind();
    Playlist *advance_curr_to_next();
    Playlist *circular_advance_curr_to_next();
    Playlist *push_back(PlaylistNode *p);
    Playlist *push_front(PlaylistNode *p);
    Playlist *insert_at_curr(PlaylistNode *p);
    Playlist *remove_at_curr();
    // The following return the target node on success, null on failure
    PlaylistNode *find_by_id(int id) const;
    PlaylistNode *find_by_song_name(string songName) const;
    string toString() const;
    friend class Tests; // Don't remove this line
};


#endif /* Playlist_h */
