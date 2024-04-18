#pragma once
//define tokens
/* Special Chars */

#define TOKEN_NIL 0

//SINGLE
#define TOKEN_CARET 1 //^, POW
#define TOKEN_AMPERSAND 2 //&, AND
#define TOKEN_ASTERISK 3 //*, MUL
#define TOKEN_PLUS 4 //+, ADD/CONCAT
#define TOKEN_MINUS 5 //-, SUB
#define TOKEN_FORWARDSLASH 6 // /, DIV
#define TOKEN_OPENPARENTHESIS 7//(, OPEN PARENTHESIS
#define TOKEN_CLOSEPARENTHESIS 8 //), CLOSE PARANTHESIS
#define TOKEN_OPENCURLY 9//{, OPEN CURLY 
#define TOKEN_CLOSECURLY 10//}, CLOSE CURLY
#define TOKEN_COMMA 11 //, ,COMMA
#define TOKEN_GREATER 12 // >
#define TOKEN_LESSER 13 // <
#define TOKEN_EQUALS 14 // =
#define TOKEN_QUOTE 15 // " or ', STRING
#define TOKEN_EXCLAMATIONMARK 16 //!, NOT
#define TOKEN_TILDE 17 // ~, TILDE, solely used for peek clause in scanner (only does rounding with an extra +-)
#define TOKEN_BACKSLASH 18 // \

//DUAL
#define TOKEN_INCREMENT 31 // ++
#define TOKEN_DECREMENT 32 //--
#define TOKEN_PLUSEQUAL 33 // +=
#define TOKEN_MINEQUAL 34 // -=
#define TOKEN_MULEQUAL 35 // *=
#define TOKEN_DIVEQUAL 36 // /=
#define TOKEN_ROUND 37 // ~~, 5.03~~ equates to 5
#define TOKEN_ROUNDDOWN 38 // ~-, 5.50~- equates to 5
#define TOKEN_ROUNDUP 39 // ~+, 5.50~+ equates to 6
#define TOKEN_GREATEREQUAL 40 // >=
#define TOKEN_LESSEREQUAL 41 // <=
#define TOKEN_EQUALEQUAL 42


/* Regular Chars */

//NON-FUNCTIONS
#define TOKEN_IF 100
#define TOKEN_ELSEIF 101
#define TOKEN_ELSE 102
#define TOKEN_FOR 103
#define TOKEN_BREAK 104
#define TOKEN_WHILE 105

//VALUES
#define TOKEN_TRUE 200
#define TOKEN_FALSE 201
#define TOKEN_PI 202

//TYPEDEF
#define TOKEN_TNUMBER 120 //number, int, float, double
#define TOKEN_TSTRING 121 //string
#define TOKEN_TFUNCTION 122 //function
#define TOKEN_CONST 123 //constant value 

//TYPES
#define TOKEN_NUMBER 125
#define TOKEN_STRING 126

//FUNCTIONS
#define TOKEN_PRINT 500
#define TOKEN_RETURN 501

//OTHER
#define TOKEN_IDENTIFIER 550
