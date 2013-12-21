//
//  stack.h
//  miniForth
//
//  Created by Cao Li on 13-12-22.
//  Copyright (c) 2013年 Cao Li. All rights reserved.
//

#ifndef miniForth_stack_h
#define miniForth_stack_h

#include <stdbool.h>

typedef enum {
    fNullType = 0,
    fBooleanType = 1,
    fIntType,
    fDoubleType,
    fStringType,
    fNativePointerType
} ValueType;

typedef struct{
    ValueType type;
    union {
        bool boolean_value;
        int int_value;
        double double_value;
        char *string_value;
        void *native_pointer;
    } val;
} fValue;



fValue* alloc_fValue();

fValue* integer_to_fValue(int i);

fValue* stack_push(fValue *v);

fValue* stack_pop();

fValue* stack_peek();

void define_core_words();

#endif
