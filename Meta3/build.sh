#!/bin/sh
rm -f petit lex.yy.c y.tab.c y.tab.h
yacc -d -v -t -g --report=all jucompiler.y
lex jucompiler.l
cc -g -o petit lex.yy.c y.tab.c ast1.c semantics.c  -Wall -Wno-unused-function
