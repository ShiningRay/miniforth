//
//  stack.c
//  miniForth
//
//  Created by Cao Li on 13-12-22.
//  Copyright (c) 2013年 Cao Li. All rights reserved.
//

#include "stack.h"
#include "word.h"
#include <stdio.h>


//const int MaxStackSize = 128;
fValue* stack[128];
int sp=0;

int intval(fValue *v){
    return v->val.int_value;
}

bool is_int(fValue *v){
    return v->type == fIntType;
}

bool is_double(fValue *v){
    return v->type == fDoubleType;
}

bool is_string(fValue *v){
    return v->type == fStringType;
}

fValue* alloc_fValue(){
    return malloc(sizeof(fValue));
}

fValue* integer_to_fValue(int i){
    fValue* v = alloc_fValue();
    v->type = fIntType;
    v->val.int_value = i;
    return v;
}

fValue* stack_push(fValue *v){
    stack[sp++] = v;
    return v;
}

fValue* stack_pop(){
    if (sp > 0) {
        return stack[--sp];
    } else {
        printf("stack under flow");
        exit(1);
        return NULL;
    }
}

fValue* stack_peek(){
    return stack[sp];
}

void f_dup() {
    stack_push(stack_peek());
}

void f_drop() {
    stack_pop();
}

void f_swap() {
    fValue* a = stack_pop();
    fValue* b = stack_pop();
    stack_push(a);
    stack_push(b);
}

void f_add() {
    fValue* a = stack_pop();
    fValue* b = stack_pop();
    assert(is_int(a) && is_int(b));
    stack_push(integer_to_fValue(intval(a) + intval(b)));
}

void f_print(){
    fValue *a = stack_pop();
    switch (a->type) {
        case fIntType:
            printf("%d", intval(a));
            break;
            
        default:
            break;
    }

}


void define_core_words(){
    define_native_word("dup", f_dup);
    define_native_word("swap", f_swap);
    define_native_word("drop", f_drop);
    define_native_word("+", f_add);
    define_native_word(".", f_print);
}
