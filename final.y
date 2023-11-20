%{
	#include <stdlib.h>
    #include <stdio.h>
    #include<string.h>
    #include<math.h>

    void yyerror(char *s);
    extern char* varType;

    int countVar=0;
    struct Symbol {
        char* name;
        char* datatype;
        int int_value;
        float float_value;
        char *string_value;
        struct Symbol* next;
    };

    struct Symbol* symbol_table = NULL;

    const char* keywords[] = {"int","float","string","ghorao_baccha","roko_jara","back","action","nothing","if","else","elif","fi","for","while","shonjog","khela shuru","khela sesh",NULL};
    //const char* datatype[] = {"int","float","char",NULL};

    int isReservedKeyword(const char* word) {
        for (int i = 0; keywords[i] != NULL; i++) {
            if (strcmp(keywords[i], word) == 0) {
                return 1;
            }
        }
        return 0;
    }

    void insertVariable(const char* name, const char* vType) {
        struct Symbol* symbol = malloc(sizeof(struct Symbol));
        symbol->name = strdup(name);
        symbol->datatype = strdup(vType);
        symbol->next = symbol_table;
        symbol_table = symbol;
        countVar++;
        printf("variable: %s, datatype: %s\n",symbol->name,symbol->datatype);
    } 

    void insertDatatype(const char* varName, const char* dType) {
        struct Symbol* current = symbol_table;

        while (current != NULL) {
            if (strcmp(current->name, varName) == 0) {
                //printf("datatype: %s var: %s\n",dType,varName);
                current->datatype = strdup(dType); // Update the value
                return ; 
            }
            current = current->next;
        }
    } 

    int isDuplicate(const char* name) {
        struct Symbol* current = symbol_table;
        while (current != NULL) {
            if (strcmp(current->name, name) == 0) {
                //printf("duplicate found %s\n",current->name);
                return 1; // Symbol is already declared
            }
            current = current->next;
        }
        return 0; // Symbol is not declared
    } 

    int updateVariableValue(const char* name, const char* value) {
        struct Symbol* current = symbol_table;
        while (current != NULL) {
           
            if (strcmp(current->name, name) == 0) {
                //printf("%s %s %s\n",name,value,current->datatype);
                if(strcmp(current->datatype,"int") == 0){
                    //printf("ok\n");
                    int x= atoi(value);
                    current->int_value = x;
                    printf("\nvalue of %s = %d\n",name,current->int_value);
                }
                else if(strcmp(current->datatype,"float") == 0){
                    float x= atof(value);
                    current->float_value = x;
                    printf("\nvalue of %s = %.4f\n",name,current->float_value);
                }
                else if(strcmp(current->datatype,"string") == 0){
                    //printf("%s\n",value);
                    current->string_value = value;
                    printf("\nvalue of %s = %s\n",name,current->string_value);
                }
                else {
                    printf("\n '%s' is invalid datatype\n",value,current->datatype);
                }
                return 1; 
            }
            current = current->next;
        }
        return 0;
        

    } 

    int checkValidity(const char* word){
        if(isReservedKeyword(word)){
            printf("\nReserved word '%s' can't be used as variable.\n",word);
            return 0;
        }
        else if(isDuplicate(word)){
            printf("\nvariable '%s' is already declared.\n",word);
            return 0;
        }
        //printf(word);
        return 1;
    }

    const char* getValue(const char* name){
        struct Symbol* current = symbol_table;
        while (current != NULL) {
           
            if (strcmp(current->name, name) == 0) {
                if(strcmp(current->datatype,"int") == 0){
                    char* str;
                    sprintf(str, "%d", current->int_value);
                    //printf("%s\n",str);
                    return str;
                }
                else if(strcmp(current->datatype,"float") == 0){
                    char* str;
                    sprintf(str, "%.4f", current->float_value);
                    //printf("%s\n",str);
                    return str;
                }
                else if(strcmp(current->datatype,"string") == 0){
                   return current->string_value;
                }
                printf("\nno value exist for '%s'\n",name);
                return "null"; 
            }
            current = current->next;
        }
        printf("\nvariable '%s' is not declared\n",name);
        return "null";
    }

     const char* getType(const char* name){
        struct Symbol* current = symbol_table;
        while (current != NULL) {
           
            if (strcmp(current->name, name) == 0) {
                return current->datatype; 
            }
            current = current->next;
        }
        printf("\nvariable '%s' is not declared\n",name);
        return "null";
    }

   

    typedef struct Parameter {
        char* name;
        char* paramType;
        char* paramValue;
        struct Parameter* next;
    } Parameter;
 

     struct FuncDeclaration {
        char* name;
        char* return_type; 
        Parameter* parameters;
        struct FuncDeclaration* next;
    };

    struct FuncDeclaration* func_table = NULL;

     void add_function_to_table(char* name, char* has_return_type, Parameter* parameters) {
        struct FuncDeclaration* new_func = malloc(sizeof(struct FuncDeclaration));
        new_func->name = strdup(name);
        new_func->return_type = has_return_type;
        new_func->parameters = parameters;
        new_func->next = func_table;
        func_table = new_func;

        printf("\nfuntion '%s' is declared. return type: '%s' ",new_func->name,new_func->return_type);
        printf("parametrs:");
        print_parameters(new_func->parameters);
    }

    int isFunctionDeclared(char* name) {
        struct FuncDeclaration* current = func_table;
        while (current != NULL) {
            if (strcmp(current->name, name) == 0) {
                return 1; // Function is declared
            }
            current = current->next;
        }
        return 0; // Function is not declared
    }

    Parameter* get_parameters_for_function(char* name) {
        struct FuncDeclaration* current = func_table;
        while (current != NULL) {
            if (strcmp(current->name, name) == 0) {
                return current->parameters; // Return the parameters for the function
            }
            current = current->next;
        }
        return NULL; // Function not found
    }

    int count_parameters(Parameter* params) {
        int count = 0;
        Parameter* current = params;
        while (current != NULL) {
            if(strcmp(params->paramType,"null")){
                count++;
            }
            //count++;
            
            current = current->next;
        }
        return count;
    }

    void print_parameters(Parameter* parameters) {
        Parameter* current = parameters;
        while (current != NULL) {
            printf(" %s (%s) ", current->name,current->paramType);
            current = current->next;
        }
        printf("\n");
    }
%}

%union{
    int intVal;
	double val;
	char* stringValue;
    struct Parameter* parameters;
}

%token MAIN_START MAIN_END DATATYPE VARIABLE INT FLOAT STRING NUM PLUS MINUS MULTI DIV MOD LT LTE GT GTE E NE AND OR IF ELSE_IF ELSE
%token WHILE START END FUN VOID BACK
%type<stringValue> VARIABLE STRING NUM
%type<stringValue> var expression term
%type <parameters> parameter_list argument_list


%left PLUS MINUS
%left MULTI DIV MOD
%nonassoc HIGH

%%
start: function_declarations MAIN_START statement MAIN_END{printf("\nvalid structure\n");}

statement:
    | declaration statement 
    | assignment statement
    | if_statement statement
    | while_statement statement
    | function_call statement
    | expression
    ;

declaration: DATATYPE var ;

var: VARIABLE {
        //printf("variable: %s\n",$1);
        int x=checkValidity($1);
        if(x){
            insertVariable($1,varType);
            //strcpy($$,$1);
            //$$=$1;
        }
        // else{
        //     //strcpy($$,"null");
        //     $$="null";
        // }
        
    }
    | var ',' VARIABLE {
        //printf("variable: %s\n",$3);
        int x=checkValidity($3);
        if(x){
            insertVariable($3,varType);
            //strcpy($$,$3);
            //$$=$3;
        }
        // else{
        //     printf("not ok\n");
        //     //$$="null";
        //     //strcpy($$,"null");
        // }
    }
    ;


assignment: VARIABLE '=' expression {
        //printf("ass: var %s val %s\n",$1,$3);
        if(isDuplicate($1)){

            updateVariableValue($1,$3);
            //printf("value of %s = %s",$1,$3);
        }
        else{
            printf("\n%s is not declared before\n",$1);
        }
    }
    | VARIABLE '=' STRING {
       if(isDuplicate($1)){
            updateVariableValue($1,$3);
            //printf("value of %s = %s",$1,$3);
        }
        else{
            printf("\n%s is not declared before\n",$1);
        }
    }
    ;

expression: expression PLUS expression {
       printf("%s jog %s\n",$1,$3);
        char *ptr1,*ptr2;
        double num1 = strtod($1, &ptr1);
        double num2 = strtod($3, &ptr2);
        sprintf($$, "%.4lf", num1+num2);
        //printf("%lf %lf\n",num1,num2);
        //printf("%s jog %s = %s\n",$1,$3,$$);
    }
    | expression MINUS expression {
        printf("%s biyog %s\n",$1,$3);
        char *ptr1,*ptr2;
        double num1 = strtod($1, &ptr1);
        double num2 = strtod($3, &ptr2);
        sprintf($$, "%.4lf", num1-num2);
        //printf("%s biyog %s = %s\n",$1,$3,$$);
    }
    | expression MULTI expression {
        printf("%s gun %s\n",$1,$3);
        char *ptr1,*ptr2;
        double num1 = strtod($1, &ptr1);
        double num2 = strtod($3, &ptr2);
        sprintf($$, "%.4lf", num1*num2);
        //printf("%s gun %s = %s\n",$1,$3,$$);
    }
    | expression DIV expression {
        printf("%s vag %s\n",$1,$3);
        char *ptr1,*ptr2;
        double num1 = strtod($1, &ptr1);
        double num2 = strtod($3, &ptr2);
        sprintf($$, "%.4lf", num1/num2);
        //printf("%s vag %s = %s\n",$1,$3,$$);
    }
    | expression MOD expression {
        printf("%s vagshesh %s\n",$1,$3);
        int num1=atoi($1);
        int num2=atoi($3);
        sprintf($$, "%d", num1%num2);
        //printf("%s vagshesh %s = %s\n",$1,$3,$$);
    }
    | expression LT expression {
        printf("%s less than %s\n",$1,$3); 
        char *ptr1,*ptr2;
        double num1 = strtod($1, &ptr1);
        double num2 = strtod($3, &ptr2);
        int x= num1<num2;
        sprintf($$, "%d", x);
        //printf("%s less than %s = %s\n",$1,$3,$$);
    }
    | expression GT expression { 
        printf("%s greater than %s\n",$1,$3);
        char *ptr1,*ptr2;
        double num1 = strtod($1, &ptr1);
        double num2 = strtod($3, &ptr2);
        int x= num1>num2;
        sprintf($$, "%d", x);
        //printf("%s greater than %s = %s\n",$1,$3,$$);
    }
    | expression LTE expression { 
        printf("%s less than equal %s\n",$1,$3);
        char *ptr1,*ptr2;
        double num1 = strtod($1, &ptr1);
        double num2 = strtod($3, &ptr2);
        int x= num1<=num2;
        sprintf($$, "%d", x);
        //printf("%s less than equal %s = %s\n",$1,$3,$$);
    }
    | expression GTE expression { 
        printf("%s greater than equal %s\n",$1,$3);
        char *ptr1,*ptr2;
        double num1 = strtod($1, &ptr1);
        double num2 = strtod($3, &ptr2);
        int x= num1>=num2;
        sprintf($$, "%d", x);
        //printf("%s greater than equal %s = %s\n",$1,$3,$$);
    }
    | expression E expression { 
        printf("%s equal %s\n",$1,$3);
        char *ptr1,*ptr2;
        double num1 = strtod($1, &ptr1);
        double num2 = strtod($3, &ptr2);
        int x= num1 == num2;
        sprintf($$, "%d", x);
        //printf("%s equal %s = %s\n",$1,$3,$$);
    }
    | expression NE expression { 
        printf("%s not equal %s\n",$1,$3);
        char *ptr1,*ptr2;
        double num1 = strtod($1, &ptr1);
        double num2 = strtod($3, &ptr2);
        int x= num1 != num2;
        sprintf($$, "%d", x);
        //printf("%s not equal %s = \n",$1,$3,$$);
    }
    | expression AND expression { 
        printf("%s ebong %s\n",$1,$3);
        char *ptr1,*ptr2;
        double num1 = strtod($1, &ptr1);
        double num2 = strtod($3, &ptr2);
        int x= num1 && num2;
        sprintf($$, "%d", x);
        //printf("%s ebong %s = %s\n",$1,$3,$$);
    }
    | expression OR expression { 
        printf("%s othoba %s\n",$1,$3);
        char *ptr1,*ptr2;
        double num1 = strtod($1, &ptr1);
        double num2 = strtod($3, &ptr2);
        int x= num1||num2;
        sprintf($$, "%d", x);
        //printf("%s othoba %s = %s\n",$1,$3,$$);
    }
    | '(' expression ')' %prec HIGH {
        $$=$2;
        //printf("matched\n");
    }
    | term {
        //printf("term: %s \n",$1);
        $$=$1;
    } 
    ;

term: VARIABLE {
        const char* value=getValue($1);
       // const char* dType=getType($1);
       printf("var: %s val: %s\n",$1,value);

        if(strcmp(value,"null")){
            strcpy($$,value);
        }
    }
    | NUM {
        //printf("num: %s\n",$1);
        $$=$1;
    }
    ; 

if_statement: IF expression '{' statement '}' {
        printf("\nif statement\n");
        //printf("exp: %s\n",$2);
        if(!strcmp($2,"1")){
            printf("\nif statement\n");
        }
        else{
            printf("\ncondition false\n");
        }
    }
    | IF expression '{' statement '}' ELSE '{' statement '}' { 
        printf("\nif-else statement\n");
        if(!strcmp($2,"1")){
            printf("\nif statement is executed\n");
        }
        else{
            printf("\nelse statement is executed\n");
        }
    }
    | IF expression '{' statement '}' ELSE_IF expression '{' statement '}'{ 
        printf("\nif-elif statement\n");
        if(!strcmp($2,"1")){
            printf("\nif codition is true\n");
        }
        else if(!strcmp($7,"1")){
            printf("\nelif statement is executed\n");
        }
    }
    | IF expression '{' statement '}' ELSE_IF expression '{' statement '}' ELSE '{' statement '}' { 
        printf("\nif-else ladder statement\n");
        if(!strcmp($2,"1")){
            printf("\nif statement is executed\n");
        }
        else if(!strcmp($7,"1")){
            printf("\nelif statement is executed\n");
        }
        else{
            printf("\nelse statement is executed\n");
        }
    }
    ;

while_statement: WHILE expression START statement END { 
        printf("\nwhile loop\n");
        if(strcpy($2,"1")){
            printf("\n condition is true\n");
        }
        else{
            printf("\n condition is true\n");
        }
    }

function_declarations: function_declaration
    | function_declaration function_declarations
    ;
function_declaration: FUN DATATYPE VARIABLE '(' parameter_list ')' '{' statement '}' {
        //printf("\nfun declared\n");
        //printf("\npar: %s\n",$5->name);
        //print_parameters($5);
        if(!isFunctionDeclared($3)){
            add_function_to_table($3,varType,$5);
        }
        else {
            printf("\nfunction '%s' is already declared\n",$3);
        }
        
    }
    | FUN VOID VARIABLE '(' parameter_list ')' '{' statement '}' {
        //printf("\nfun declared\n");
        //printf("\npar: %s\n",$5->name);
        //print_parameters($5);

        if(!isFunctionDeclared($3)){
            add_function_to_table($3,varType,$5);
        }
        else {
            printf("\nfunction '%s' is already declared\n",$3);
        }
    }
    |
    ;

parameter_list: { 
        $$ = (Parameter*)malloc(sizeof(Parameter));
        $$->name = strdup("null");
        $$->paramType = strdup("null");
        $$->next = NULL;
    }
    | DATATYPE VARIABLE { 
        $$ = (Parameter*)malloc(sizeof(Parameter));
        $$->name = strdup($2);
        $$->paramType = strdup(varType);
        $$->next = NULL;
        //$$=$2;

    }
    | parameter_list ',' DATATYPE VARIABLE { 
        Parameter* new_param = (Parameter*)malloc(sizeof(Parameter));
        new_param->name = strdup($4);
        new_param->paramType = strdup(varType);
        new_param->next = $$;
        $$ = new_param;
    }
    ;

function_call: VARIABLE '(' argument_list ')' {
        if (!isFunctionDeclared($1)) {
            printf("\nFunction '%s' not declared before use\n",$1);
        }
        else{
            Parameter* declared_params = get_parameters_for_function($1);
            Parameter* provided_params = $3;

            int param_count=0;
            Parameter* temp = provided_params;

            while (temp != NULL) {
                if(strcmp(temp->paramValue,"null")){
                    param_count++;
                }
                //param_count++;
                temp = temp->next;
            }

            if (param_count != 0 && param_count != count_parameters(declared_params)) {
                printf("\nIncorrect number of arguments in calling function '%s'\n",$1);
            } 
            else {
                printf("\nFunction call to '%s' is valid\n", $1);
            }
        }
    }
    ;

argument_list: { 
        $$ = (Parameter*)malloc(sizeof(Parameter));
        $$->paramValue = strdup("null");
        $$->next = NULL;

    }
    | expression { 
        $$ = (Parameter*)malloc(sizeof(Parameter));
        $$->paramValue = strdup($1);
        $$->next = NULL;
    }
    | argument_list ',' expression {
        Parameter* new_param = (Parameter*)malloc(sizeof(Parameter));
        new_param->paramValue = strdup($3); 
        new_param->next = $$;
        $$ = new_param;
    }
    ;

%%

yyerror(char *s){  
	printf( "%s\n", s);
}

int main(){
	freopen("final_input.txt", "r",stdin);
	freopen("output.txt", "w",stdout);
	yyparse();
    printf("total variable= %d",countVar);
	return 0;
}