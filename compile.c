#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler.h"
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>

#define ALLOC(t) (t*) calloc(1, sizeof(t))
#define DEBUG 1

struct VarNode{
    struct ValueNode *node;
    struct VarNode *next;
};

struct StatementNode * parse_generate_intermediate_representation(){
    struct StatementNode *program = NULL;
    struct StatementNode *programTail = NULL;
    struct VarNode *variables = NULL;

    //get variable body

    getToken();
    if(ttype != LBRACE) {
        //printf("%s", token);
        while (ttype != SEMICOLON) {
            if (ttype == COMMA) {
                getToken();
                continue;
            }
            struct VarNode *temp = ALLOC(struct VarNode);
            temp->node = ALLOC(struct ValueNode);
            temp->node->name = strdup(token);
            temp->node->value = 0;
            temp->next = variables;
            variables = temp;
            getToken();
        }

        if (DEBUG) {
            struct VarNode *current = variables;

            while (current != NULL) {
                printf("VARIABLE %s\n", current->node->name);
                current = current->next;
            }
        }

    }
    //printf("%s", token);
    if(getToken() == LBRACE)
        while(ttype != RBRACE) {
            if (ttype == PRINT) {//print statement
                getToken();
                //printf("%s\n", token );
                struct VarNode *current = variables;
                while (current != NULL) {
                    if (strcmp(token, current->node->name) == 0) {
                        printf("%s = %d\n",current->node->name, current->node->value);
                        struct StatementNode *temp = ALLOC(struct StatementNode);
                        temp->type = PRINT_STMT;
                        temp->print_stmt = ALLOC(struct PrintStatement);
                        temp->print_stmt->id = current->node;
                        temp->next = program;
                        program = temp;
                        getToken();
                        break;
                    }
                    current = current->next;
                }

            }
            else if(ttype == ID){//assignment statement

            }
            getToken();
            printf("%s\n", token);
        }

    struct StatementNode *current = program;
    while(current != NULL){
        struct StatementNode *temp = current;
        temp->next = programTail;
        programTail = temp;
        current = current->next;
    }

    return programTail;
}