%option noyywrap
%{
#include <stdio.h>
#include <string.h>
int line_no = 1;
int comment_lines = 0;
%}

%%
"int"|"float"|"char"|"main"|"return"|"if"|"else"|"while"|"for"|"void"|"bool"|"long"|"break"|"continue"|"case"|"switch"|"default"|"double"|"sizeof"|"auto"|"signed"|"goto"|"enum"|"short"|"static"|"scanf"|"printf" { printf("key-word: %s\n", yytext); }

[a-zA-Z_][a-zA-Z0-9_]*  { printf("identifier: %s\n", yytext); }

[0-9]+   { printf("Constant: %s\n", yytext); }

[+\-*/=]  { printf("Operators: %s\n", yytext); }

[(){};,] { printf("Special char: %s\n", yytext); }

"//".*  { comment_lines++; }

"/*"[^*]*"*/"  { comment_lines++; }

[\t ]+  { }

\n  { line_no++; }

.  { printf("Invalid token: %s\n", yytext); }
%%

int main()
{
    yyin = fopen("t3.c", "r");
    if (!yyin) {
        printf("Error opening file.\n");
        return 1;
    }
    yylex();
    fclose(yyin);
    
    printf("Total comment lines: %d\n", comment_lines);
    return 0;
}
