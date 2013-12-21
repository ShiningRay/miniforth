//
//  main.c
//  miniForth
//
//  Created by Cao Li on 13-12-21.
//  Copyright (c) 2013年 Cao Li. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include <uthash.h>
#include <utstring.h>
#include <assert.h>

#include "stack.h"
#include "word.h"
FILE* source;
int pos=0;
int line=0;
int col=0;

char* scan_token(char* token){
    char ch;
    int consumed = 0;
    for(;;) {
        ch = fgetc(source);
        if (ch == EOF) {
            if(consumed > 0){
                pos += consumed;
                return token;
            } else {
                return NULL;
            }
        }
        if (ch == ' ' || ch == '\r' || ch == '\t' || ch == '\n') {
            if (consumed > 0) {
                pos += consumed;
                return token;
            }
        } else {
            if (consumed < 32) {
                token[consumed] = ch;
            }
            consumed++;
        }
    }
    
    return token;
}

bool str_is_integer(char *str){
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] < '0' || str[i] > '9') {
            return false;
        }
    }
    return true;
}

int main(int argc, const char * argv[])
{
    if (argc < 2) {
        printf("require filename");
        return 0;
    }
    
    if((source = fopen(argv[1], "r")) == NULL){
        printf(("open file \"%s\" error"), argv[1]);
        return 0;
    }
    
    define_core_words();
    
    char token[32] = "";
    //memset(token, 0, sizeof(char) * 32);
    while (scan_token(token)) {
        //printf("token %s\n", token);
        if (str_is_integer(token)) {
            stack_push(integer_to_fValue(atoi(token)));
        } else {
            call_word_name(token);
        }
        memset(token, 0, sizeof(char) * 32);
    }
    
    fclose(source);
    return 0;
}

