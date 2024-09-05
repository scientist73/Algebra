%skeleton "Bison_Parser.cpp"
%require "3.4"
%language "c++"

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
#include <string>
class driver;
}

%param { driver& drv }


%define parse.trace
%define parse.error verbose
%define api.namespace {alg::calc::pars::bison}

%code {
#include "driver.hh"
}

%define api.token.prefix {TOK_}
%token
  END 0 "end of input"
  MINUS "-"
  PLUS "+"
  MULT "*"
  DIV "/"
  LPAREN "("
  RPAREN ")"
;
%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"
%type <int> exp

%printer { yyo << $$; } <*>

%%

%start unit;
unit: assignments exp { drv.result = $2; }
  ;

assignments: %empty {}
  | assignments assignment {}
  ;

assignment:
  "identifier" ":=" exp { drv.variables[$1] = $3; }
  ;

%left "+" "-";
%left "*" "/";

exp: "number"
  | "identifier" { $$ = drv.variables[$1]; }
  | exp "+" exp { $$ = $1 + $3; }
  | exp "-" exp { $$ = $1 - $3; }
  | exp "*" exp { $$ = $1 * $3; }
  | exp "/" exp { $$ = $1 / $3; }
  | "(" exp ")" { $$ = $2; }
  ;

%%

void yy::parser::error(const location_type& loc, const std::string& m) {
  std::cerr << loc << ": " << m << std::endl;
}