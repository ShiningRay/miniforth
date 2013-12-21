//
//  word.c
//  miniForth
//
//  Created by Cao Li on 13-12-22.
//  Copyright (c) 2013年 Cao Li. All rights reserved.
//

#include <stdio.h>
#include "word.h"

struct word *dict = NULL;

void define_word(char *name, char *content){
    Word *word=malloc(sizeof(Word));
    strcpy(name, word->name);
    
}

Word* alloc_word(){
    return malloc(sizeof(Word));
}

void define_native_word(char *name, void (*func)()){
    Word *word;
    HASH_FIND_STR(dict, name, word);
    assert(word == NULL);
    word = alloc_word();
    strcpy(word->name, name);
    word->native = true;
    word->func = func;
    HASH_ADD_STR(dict, name, word);
}

Word* find_word(char *name){
    Word *word;
    HASH_FIND_STR(dict, name, word);
    return word;
}

void call_word_name(char *name){
    Word *word;
    HASH_FIND_STR(dict, name, word);
    assert(word);
    if(word->native){
        word->func();
    }
}

void call_word(Word *word){
    if(word->native){
        word->func();
    }
}