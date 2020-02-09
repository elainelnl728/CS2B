//
//  Playlist.cpp
//  Extra_credit_Project
//
//  Created by Niliang Lu on 6/30/19.
//  Copyright © 2019 Elaine. All rights reserved.
// id: 20392734

#include <iomanip>
#include <iostream>
using namespace std;

#include "Playlist.h"

bool SongEntry::set_id(int id) {
    if (id < 0) {
        return false;
    }
    this->id = id;
    return true;
}

bool SongEntry::set_name(string theName) {
    if (theName == "") {
        return false;
    }
    this->name = theName;
    return true;
}

PlaylistNode::~PlaylistNode() {}

PlaylistNode *PlaylistNode::insert_next(PlaylistNode *p) {
    if(p == nullptr) {
        return nullptr;
    }
    p->next = this->next;
    this->next = p;
    return this;
}

PlaylistNode *PlaylistNode::remove_next() {
    if(this->next == nullptr) {
        return nullptr;
    }
    PlaylistNode* temp = this->next->next;
    delete this->next;
    this->next = temp;
    return this;
}


Playlist::Playlist() {
    SongEntry songEntry(0, "Header");
    this->head = new PlaylistNode(songEntry);
    this->tail = this->head;
    this->prevToCurr = this->head;
    this->size = 0;
}

Playlist::~Playlist() {
    while (head->remove_next() != nullptr) {}
    delete head;
}

Playlist *Playlist::clear() {
    while (this->head->remove_next() != nullptr) {}
    this->tail = this->head;
    this->prevToCurr = this->head;
    this->size = 0;
    return this;
}

PlaylistNode *Playlist::get_current_node() const {
    if (head->get_next() == nullptr) {
        return nullptr;
    }
    return prevToCurr->get_next();
}

Playlist *Playlist::rewind() {
    prevToCurr = head;
    return this;
}

// State of ​prevToCurr​ is ​undefined​ if ​advance​ returns a null pointer.
Playlist *Playlist::advance_curr_to_next() {
   if (prevToCurr == nullptr ||
       prevToCurr->get_next() == nullptr ||
       prevToCurr->get_next()->get_next() == nullptr) {
       return nullptr;
   }
   prevToCurr = prevToCurr->get_next();
   return this;
}

Playlist *Playlist::circular_advance_curr_to_next() {
    // Empty playlist.
    if (head->get_next() == nullptr) {
        return nullptr;
    }
    if (prevToCurr->get_next() == nullptr || prevToCurr->get_next()->get_next() == nullptr) {
        return rewind();
    }
    prevToCurr = prevToCurr->get_next();

    return this;
}

Playlist *Playlist::push_back(PlaylistNode *p) {
    if (p == nullptr) {
        return nullptr;
    }
    
    if (tail->insert_next(p) == nullptr) {
        return nullptr;
    }
    
    tail = tail->get_next();
 
    size++;
    return this;
}

Playlist *Playlist::push_front(PlaylistNode *p) {
    if (p == nullptr) {
        return nullptr;
    }
    
    
    if (head->insert_next(p) == nullptr) {
        return nullptr;
    }
    if (p->get_next() == nullptr) {
        tail = p;
    }
    
    size++;
    return this;
}

Playlist *Playlist::insert_at_curr(PlaylistNode *p) {
    if (p == nullptr) {
        return nullptr;
    }
 
    prevToCurr->insert_next(p);
    if (p->get_next() == nullptr) {
        tail = p;
    }
    size++;
    return this;
}

Playlist *Playlist::remove_at_curr() {
    if (prevToCurr->get_next() == nullptr) {
        return nullptr;
    }
    
    prevToCurr->remove_next();
    if (prevToCurr->get_next() == nullptr) {
        tail = prevToCurr;
    }
    
    size--;
    return this;
}

PlaylistNode *Playlist::find_by_id(int id) const {
    PlaylistNode *currNode = head->get_next();
    while (currNode != nullptr) {
        if (currNode->get_song().get_id() == id) {
            return currNode;
        }
        currNode = currNode->get_next();
    }
    // Not found.
    return nullptr;
}

PlaylistNode *Playlist::find_by_song_name(string songName) const {
    PlaylistNode *currNode = head->get_next();
    while (currNode != nullptr) {
        if (currNode->get_song().get_name() == songName) {
            return currNode;
        }
        currNode = currNode->get_next();
    }
    // Not found.
    return nullptr;
}

string Playlist::toString() const {
    string output = "Playlist:​​ " + to_string(size) + "​ entries.";
    if (head == nullptr) {
        return output;
    }
    PlaylistNode *currNode = head->get_next();
    while (currNode != nullptr) {
        string id_str = to_string(currNode->get_song().get_id());
        int num_digits = id_str.size();
        int pad_digits = 5 - num_digits;
        if (pad_digits > 0) {
            id_str.insert(0, string(pad_digits, '0'));
        }
        output = output + "\nID​ ​" + id_str + ":​ " + currNode->get_song().get_name();
        currNode = currNode->get_next();
    }
    output = output + "\n";
    unsigned int i = 0;
    while (i < output.size()) {
        if (output[i] < 0) {
            output.erase(i, 1);
        } else {
            i++;
        }
    }
    return output;
}
