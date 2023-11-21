%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "final.tab.h"

char* varType;
%}

ConditionalOperator "=="|"!="|"<"|"<="|">"|">="|"&&"|"||"
Varibale [a-zA-Z_][a-zA-Z0-9_]*
ArithmeticOperator "jog"|"biyog"|"gun"|"vag"


%%
"shonjog"[ ][a-z]+.[h] {
        //printf("header file\n"); 
        return HEADER;
    }
"khela shuru" {return MAIN_START;}
"khela sesh" {return MAIN_END;}

"int" {
        varType=strdup("int");
        //strcpy(varType,"int");
        return DATATYPE;
    }
"float" {
        varType=strdup("float");
        //strcpy(varType,"float");
        return DATATYPE;
    }
"string" {
        varType=strdup("string");
        //strcpy(varType,"string");
        return DATATYPE;
    }

"jog" {return PLUS;}
"biyog" {return MINUS;}
"gun" {return MULTI;}
"vag" {return DIV;}
"vagshesh" {return MOD;}

"<" {return LT;}
"<=" {return LTE;}
">" {return GT;}
">=" {return GTE;}
"==" {return E;}
"!=" {return NE;}
"ebong" {return AND;}
"othoba" {return OR;}

"if" {return IF;}
"elif" {return ELSE_IF;}
"else" {return ELSE;}

"while" {return WHILE;}
"ghorao_baccha" {return START;}
"roko_jara" {return END;}

"action" {return FUN;}
"nothing" {return VOID;}
"back" {return BACK;}

"input_dao" {return INPUT;}
"dekhao" {return OUTPUT;}

"sin" {return SIN;}
"cos" {return COS;}
"tan" {return TAN;}

[-]?[0-9]+ {
    yylval.stringValue = strdup(yytext);
    return NUM;
}

[-]?[0-9]+[.][0-9]+ {
    yylval.stringValue = strdup(yytext);
    return NUM;
}

["].*["] {
    yylval.stringValue = strdup(yytext);
    return STRING;
}



{Varibale} {
    yylval.stringValue = strdup(yytext);
    return VARIABLE;}

[,=(){}] {yylval.stringValue = strdup(yytext);
        return *yytext;
    }

\/\/[^\n]* {printf("\nsingle line comment\n");}
\/\*([^*]|\*[^\/])*\*\/ {printf("\nmultiline comment\n");}

[\n]*       {}
[\t]*       {}
[ ]*	    {}

.           {yyerror("Unknown Character.\n");}

%%

int yywrap()
{
    return 1;
}

// int main()
// {
//     freopen("final_input.txt","r",stdin);
// 	freopen("output.txt","w",stdout);
// 	yyparse();
    
// 	return 0;
// }
