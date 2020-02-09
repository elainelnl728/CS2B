//
//  main.cpp
//  Extra_credit_Project
//
//  Created by Niliang Lu on 6/30/19.
//  Copyright © 2019 Elaine. All rights reserved.
//

#include <iostream>

#include "Playlist.h"

int main(int argc, const char * argv[]) {
    Playlist *playList = new Playlist();
    SongEntry song1(1, "one");
    PlaylistNode *node1 = new PlaylistNode(song1);
    SongEntry song2(2, "two");
    PlaylistNode *node2 = new PlaylistNode(song2);
    SongEntry song3(3, "three");
    PlaylistNode *node3 = new PlaylistNode(song3);
    SongEntry song4(4, "four");
    PlaylistNode *node4 = new PlaylistNode(song4);
    SongEntry song5(5, "five");
    PlaylistNode *node5 = new PlaylistNode(song5);
    
    playList->push_back(node1);
    playList->push_back(node2);
    playList->push_back(node3);
    string output = playList->toString();
    std::cout << output;
    
    playList->clear();
    
    
    
    output = playList->toString();
    std::cout << output;
    return 0;
}
