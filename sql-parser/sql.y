%{

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

void yyerror(char* s, ...);
void emit(char* s, ...);

%}

%union {
	int intval;
	double floatval;
	char* strval;
	int subtok;
}

%token <strval>   NAME
%token <intval>   INTNUM
%token <floatval> APPROXNUM
%token <strval>   STRING
%token <intval>   BOOL

%token <strval>   USERVAR

%right ASSIGN
%left OR
%left XOR
%left ANDOP
%nonassoc IN IS LIKE REGEXP
%left NOT '!'
%left BETWEEN
%left <subtok> COMPARISON // = <> < > <= >=
%left '|'
%left '&'
%left <subtok> SHIFT // << >>
%left '+' '-'
%left '*' '/' '%' MOD
%left '^'
%nonassoc UMINUS

%token ADD
%token ALL
%token ALTER
%token ANALYZE
%token AND
%token ANY
%token AS
%token ASC
%token AUTO_INCREMENT
%token BEFORE
%token BETWEEN
%token BIGINT
%token BINARY
%token BIT
%token BLOB
%token BOTH
%token BY
%token CALL
%token CASCADE
%token CASE
%token CHANGE
%token CHAR
%token CHECK
%token COLLATE
%token COLUMN
%token COMMENT
%token CONDITION
%token CONSTRAINT
%token CONTINUE
%token CONVERT
%token CREATE
%token CROSS
%token CURRENT_DATE
%token CURRENT_TIME
%token CURRENT_TIMESTAMP
%token CURRENT_USER
%token CURSOR
%token DATABASE
%token DATABASES
%token DATE
%token DATETIME
%token DAY_HOUR
%token DAY_MICROSECOND
%token DAY_MINUTE
%token DAY_SECOND
%token DECIMAL
%token DECLARE
%token DEFAULT
%token DELAYED
%token DELETE
%token DESC
%token DESCRIBE
%token DETERMINISTIC
%token DISTINCT
%token DISTINCTROW
%token DIV
%token DOUBLE
%token DROP
%token DUAL
%token EACH
%token ELSE
%token ELSEIF
%token ENCLOSED
%token END
%token ENUM
%token ESCAPED
%token <subtok> EXISTS
%token EXIT
%token EXPLAIN
%token FETCH
%token FLOAT
%token FOR
%token FORCE
%token FOREIGN
%token FROM
%token FULLTEXT
%token GRANT
%token GROUP
%token HAVING
%token HIGH_PRIORITY
%token HOUR_MICROSECOND
%token HOUR_MINUTE
%token HOUR_SECOND
%token IF
%token IGNORE
%token IN
%token INDEX
%token INFILE
%token INNER
%token INOUT
%token INSENSITIVE
%token INSERT
%token INT
%token INTEGER
%token INTERVAL
%token INTO
%token ITERATE
%token JOIN
%token KEY
%token KEYS
%token KILL
%token LEADING
%token LEAVE
%token LEFT
%token LIKE
%token LIMIT
%token LINES
%token LOAD
%token LOCALTIME
%token LOCALTIMESTAMP
%token LOCK
%token LONG
%token LONGBLOB
%token LONGTEXT
%token LOOP
%token LOW_PRIORITY
%token MATCH
%token MEDIUMBLOB
%token MEDIUMINT
%token MEDIUMTEXT
%token MINUTE_MICROSECOND
%token MINUTE_SECOND
%token MOD
%token MODIFIES
%token NATURAL
%token NOT
%token NO_WRITE_TO_BINLOG
%token NULLX
%token NUMBER
%token ON
%token ONDUPLICATE
%token OPTIMIZE
%token OPTION
%token OPTIONALLY
%token OR
%token ORDER
%token OUT
%token OUTER
%token OUTFILE
%token PRECISION
%token PRIMARY
%token PROCEDURE
%token PURGE
%token QUICK
%token READ
%token READS
%token REAL
%token REFERENCES
%token REGEXP
%token RELEASE
%token RENAME
%token REPEAT
%token REPLACE
%token REQUIRE
%token RESTRICT
%token RETURN
%token REVOKE
%token RIGHT
%token ROLLUP
%token SCHEMA
%token SCHEMAS
%token SECOND_MICROSECOND
%token SELECT
%token SENSITIVE
%token SEPARATOR
%token SET
%token SHOW
%token SMALLINT
%token SOME
%token SONAME
%token SPATIAL
%token SPECIFIC
%token SQL
%token SQLEXCEPTION
%token SQLSTATE
%token SQLWARNING
%token SQL_BIG_RESULT
%token SQL_CALC_FOUND_ROWS
%token SQL_SMALL_RESULT
%token SSL
%token STARTING
%token STRAIGHT_JOIN
%token TABLE
%token TEMPORARY
%token TEXT
%token TERMINATED
%token THEN
%token TIME
%token TIMESTAMP
%token TINYBLOB
%token TINYINT
%token TINYTEXT
%token TO
%token TRAILING
%token TRIGGER
%token UNDO
%token UNION
%token UNIQUE
%token UNLOCK
%token UNSIGNED
%token UPDATE
%token USAGE
%token USE
%token USING
%token UTC_DATE
%token UTC_TIME
%token UTC_TIMESTAMP
%token VALUES
%token VARBINARY
%token VARCHAR
%token VARYING
%token WHEN
%token WHERE
%token WHILE
%token WITH
%token WRITE
%token XOR
%token YEAR
%token YEAR_MONTH
%token ZEROFILL

    /* functions with special syntax */
%token FSUBSTRING
%token FTRIM
%token FDATE_ADD FDATE_SUB
%token FCOUNT

%type <intval> opt_if_not_exists
%type <intval> insert_vals_list insert_vals
%type <intval> select_opts select_expr_list
%type <intval> group_by_list opt_asc_desc 
%type <intval> table_references

%start stmt_list

%%

stmt_list:
	  stmt ';'
	| stmt_list stmt ';'
	
stmt:
	  create_database_stmt { emit("STMT"); }
    | drop_database_stmt { emit("STMT"); }
    | create_table_stmt { emit("STMT"); }
    | drop_table_stmt { emit("STMT"); }
    | insert_stmt { emit("STMT"); }
    | delete_stmt { emit("STMT"); }
    | select_stmt { emit("STMT"); }
    | update_stmt { emit("STMT"); }
	;

create_database_stmt:
      CREATE DATABASE opt_if_not_exists NAME { emit("CREATE DATABASE: %s", $4); free($4); }
    ;

opt_if_not_exists:
      /* nil */ { $$ = 0; }
    | IF NOT EXISTS { $$ = 1; }
    ;

drop_database_stmt:
      DROP DATABASE NAME { emit("DROP DATABASE: %s", $3); free($3); }
    ;
    
create_table_stmt:
      CREATE TABLE NAME { emit("CREATE DATABASE: %s", $3); free($3); }
    ;

drop_table_stmt:
      DROP TABLE NAME { emit("DROP TABLE: %s", $3); free($3); }
    ;

insert_stmt:
      INSERT opt_into NAME
      VALUES insert_vals_list
    ;

delete_stmt:
      DELETE FROM NAME
      opt_where opt_orderby opt_limit
    | DELETE delete_list
      FROM table_references
      opt_where
    ;

select_stmt:
	  SELECT select_opts select_expr_list { emit("SELECTNODATA %d %d", $2, $3); } 
	| SELECT select_opts select_expr_list
	  FROM table_references
	  opt_where opt_groupby opt_having opt_orderby opt_limit { emit("SELECT %d %d %d", $2, $3, $5); }
	;

update_stmt:
      UPDATE table_references
      SET update_asgn_list
      opt_where
      opt_orderby
      opt_limit
    ;

insert_vals_list:
      '(' insert_vals ')' { emit("VALUES %d", $2); $$ = 1; }
    | insert_vals_list ',' '(' insert_vals ')' { emit("VALUES %d", $4); $$ = $1 + 1; }
    ;

insert_vals:
      expr { $$ = 1; }
    | DEFAULT { emit("DEFAULT"); $$ = 1; }
    | insert_vals ',' expr
    | insert_vals ',' DEFAULT
    ;

opt_into:
      /* nil */
    | INTO
    ;

delete_list:
      NAME opt_dot_star
    | delete_list ',' NAME opt_dot_star
    ;

opt_dot_star:
      /* nil */
    | '.' '*'
    ;

update_asgn_list:
      NAME COMPARISON expr
    | NAME '.' NAME COMPARISON expr
    | update_asgn_list ',' NAME COMPARISON expr
    | update_asgn_list ',' NAME '.' NAME COMPARISON expr
    ;

select_opts:
	  /* nil */ { $$ = 0; }
    | select_opts ALL { if ($$ & 01) { yyerror("duplicate ALL option."); $$ = $1 | 01; }}
    | select_opts DISTINCT { if ($$ & 02) { yyerror("duplicate DISTINCT option"); $$ = $1 | 02; }}
	;

select_expr_list:
	  select_expr_list ',' select_expr { $$ = $1 + 1; }
	| select_expr { $$ = 1 ;}
	| '*' { emit("SELECTALL"); $$ = 1; }
	;

select_expr:
	  expr opt_as_alias
	;

opt_groupby:
      /* nil */
    | GROUP BY group_by_list { emit("GROUPBYLIST %d", $3); }
    ;

group_by_list:
      expr opt_asc_desc { emit("GROUPBY %d", $2); $$ = 1; }
    | group_by_list ',' expr opt_asc_desc { emit("GROUPBY %d", $4); $$ = $1 + 1; }
    ;

opt_asc_desc:
      /* nil */ { $$ = 0; }
    | ASC { $$ = 0; }
    | DESC { $$ = 1; }
    ;

opt_having:
      /* nil */
    | HAVING expr { emit("HAVING"); }
    ;

opt_orderby:
      /* nil */
    | ORDER BY group_by_list { emit("ORDERBY %d", $3); }
    ;

opt_limit:
      /* nil */
    | LIMIT expr { emit("LIMIT 1"); }
    | LIMIT expr ',' expr { emit("LIMIT 2"); }
    ;

expr:
	  NAME { emit("NAME %s", $1); free($1); }
	| NAME '.' NAME { emit("FIELDNAME %s.%s", $1, $3); free($1); free($3); }
	| USERVAR { emit("USERVAR %s", $1); free($1); }
	| STRING { emit("STRING %s", $1); free($1); }
	| INTNUM { emit("NUMBER %d", $1); }
	| APPROXNUM { emit("FLOAT %g", $1); }
	| BOOL { emit("BOOL %d", $1); }
	;

expr:
	  expr '+' expr { emit("ADD"); }
	| expr '-' expr { emit("SUB"); }
	| expr '*' expr { emit("MUL"); }
	| expr '/' expr { emit("DIV"); }
	| expr '%' expr { emit("MOD"); }
    | expr ANDOP expr { emit("AND"); }
	| expr COMPARISON expr { emit("CMP %d", $2); }
	;

expr:
	  expr IS NULLX { emit("ISNULL"); }
	| expr IS NOT NULLX { emit("ISNULL"); emit("NOT"); }
	| expr IS BOOL { emit("ISBOOL %d", $3); }
	| expr IS NOT BOOL { emit("ISBOOL %d", $4); emit("NOT"); }
	;

expr:
      expr BETWEEN expr AND expr %prec BETWEEN { emit("BETWEEN"); }
    ;

opt_as_alias:
	  AS NAME { emit("ALIAS %s", $2); free($2); }
	| NAME { emit("ALIAS %s", $1); free($1); }
	| /* nil */
	;

table_references:
	  table_reference { $$ = 1; }
	| table_references ',' table_reference { $$ = $1 + 1; }
	;

table_reference:
	  table_factor
	;

table_factor:
	  NAME { emit("TABLE %s", $1); free($1); }
	| NAME '.' NAME { emit("TABLE %s.%s", $1, $3); free($1); free($3); }
	| table_subquery opt_as NAME { emit("SUBQUERY %s", $3); free($3); }
	| '(' table_references ')' { emit("TABLEREFERENCES %d", $2); }
	;

table_subquery:
      '(' select_stmt ')' { emit("SUBQUERY"); }
    ;

opt_as:
      /* nil */
    | AS
    ;
    
opt_where:
	  /* nil */
	| WHERE expr { emit("WHERE"); }
	;

%%

void emit(char* s, ...)
{
	extern int yylineno;

	va_list ap;
	va_start(ap, s);

	printf("rpn: ");
	vfprintf(stdout, s, ap);
	printf("\n");
}

void yyerror(char* s, ...)
{
	extern int yylineno;

	va_list ap;
	va_start(ap, s);

	fprintf(stderr, "%d: error: ", yylineno);
	vfprintf(stderr, s, ap);
	fprintf(stderr, "\n");
}

int main(int argc, char** argv)
{
	extern FILE* yyin;

	if (argc > 1 && !strcmp(argv[1], "-d")) {
		yydebug = 1;
		--argc;
		++argv;
	}

	if (argc > 1 && (yyin = fopen(argv[1], "r")) == NULL) {
		perror(argv[1]);
		exit(1);
	}

	if (!yyparse()) {
		printf("SQL parse worked.\n");
	} else {
		printf("SQL parse failed.\n");
	}
}

int yywrap() { return 1; }
