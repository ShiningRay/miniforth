//
//  word.h
//  miniForth
//
//  Created by Cao Li on 13-12-22.
//  Copyright (c) 2013年 Cao Li. All rights reserved.
//

#ifndef miniForth_word_h
#define miniForth_word_h

#include <uthash.h>
#include <stdbool.h>
#include <assert.h>
struct word {
    char name[32];
    char content[64];
    bool immediate;
    bool native;
    void (*func)();
    UT_hash_handle hh;
};

typedef struct word Word;



void define_word(char *name, char *content);
void define_native_word(char *name, void (*word)());
Word* find_word(char *name);
void call_word_name(char *name);
void call_word(Word *word);
#endif
