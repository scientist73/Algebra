// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "BisonParserGenerated.h"




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 30 "/home/scientist73/projects/Algebra/calc/pars/Parser/src/impl/bison/Bison_Parser.y"
namespace alg { namespace calc { namespace pars { namespace impl { namespace bison {
#line 118 "/home/scientist73/projects/Algebra/calc/pars/Parser/src/impl/bison/BisonParserGenerated.cpp"

  /// Build a parser object.
  parser::parser ()
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr)
#else

#endif
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_NUM: // "number"
      case symbol_kind::S_exp: // exp
        value.YY_MOVE_OR_COPY< NumType<double> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ID: // "identifier"
        value.YY_MOVE_OR_COPY< std::string_view > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s)
  {
    switch (that.kind ())
    {
      case symbol_kind::S_NUM: // "number"
      case symbol_kind::S_exp: // exp
        value.move< NumType<double> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ID: // "identifier"
        value.move< std::string_view > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_NUM: // "number"
      case symbol_kind::S_exp: // exp
        value.copy< NumType<double> > (that.value);
        break;

      case symbol_kind::S_ID: // "identifier"
        value.copy< std::string_view > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_NUM: // "number"
      case symbol_kind::S_exp: // exp
        value.move< NumType<double> > (that.value);
        break;

      case symbol_kind::S_ID: // "identifier"
        value.move< std::string_view > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_NUM: // "number"
      case symbol_kind::S_exp: // exp
        yylhs.value.emplace< NumType<double> > ();
        break;

      case symbol_kind::S_ID: // "identifier"
        yylhs.value.emplace< std::string_view > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // input: exp
#line 82 "/home/scientist73/projects/Algebra/calc/pars/Parser/src/impl/bison/Bison_Parser.y"
           { setParseResult(yystack_[0].value.as < NumType<double> > ()); }
#line 544 "/home/scientist73/projects/Algebra/calc/pars/Parser/src/impl/bison/BisonParserGenerated.cpp"
    break;

  case 3: // exp: "number"
#line 85 "/home/scientist73/projects/Algebra/calc/pars/Parser/src/impl/bison/Bison_Parser.y"
     { yylhs.value.as < NumType<double> > () = yystack_[0].value.as < NumType<double> > (); }
#line 550 "/home/scientist73/projects/Algebra/calc/pars/Parser/src/impl/bison/BisonParserGenerated.cpp"
    break;

  case 4: // exp: exp "+" exp
#line 86 "/home/scientist73/projects/Algebra/calc/pars/Parser/src/impl/bison/Bison_Parser.y"
                { yylhs.value.as < NumType<double> > () = yystack_[2].value.as < NumType<double> > () + yystack_[0].value.as < NumType<double> > (); }
#line 556 "/home/scientist73/projects/Algebra/calc/pars/Parser/src/impl/bison/BisonParserGenerated.cpp"
    break;

  case 5: // exp: exp "-" exp
#line 87 "/home/scientist73/projects/Algebra/calc/pars/Parser/src/impl/bison/Bison_Parser.y"
                { yylhs.value.as < NumType<double> > () = yystack_[2].value.as < NumType<double> > () - yystack_[0].value.as < NumType<double> > (); }
#line 562 "/home/scientist73/projects/Algebra/calc/pars/Parser/src/impl/bison/BisonParserGenerated.cpp"
    break;

  case 6: // exp: exp "*" exp
#line 88 "/home/scientist73/projects/Algebra/calc/pars/Parser/src/impl/bison/Bison_Parser.y"
                { yylhs.value.as < NumType<double> > () = yystack_[2].value.as < NumType<double> > () * yystack_[0].value.as < NumType<double> > (); }
#line 568 "/home/scientist73/projects/Algebra/calc/pars/Parser/src/impl/bison/BisonParserGenerated.cpp"
    break;

  case 7: // exp: exp "/" exp
#line 89 "/home/scientist73/projects/Algebra/calc/pars/Parser/src/impl/bison/Bison_Parser.y"
                { yylhs.value.as < NumType<double> > () = yystack_[2].value.as < NumType<double> > () / yystack_[0].value.as < NumType<double> > (); }
#line 574 "/home/scientist73/projects/Algebra/calc/pars/Parser/src/impl/bison/BisonParserGenerated.cpp"
    break;

  case 8: // exp: "(" exp ")"
#line 90 "/home/scientist73/projects/Algebra/calc/pars/Parser/src/impl/bison/Bison_Parser.y"
                { yylhs.value.as < NumType<double> > () = yystack_[1].value.as < NumType<double> > (); }
#line 580 "/home/scientist73/projects/Algebra/calc/pars/Parser/src/impl/bison/BisonParserGenerated.cpp"
    break;


#line 584 "/home/scientist73/projects/Algebra/calc/pars/Parser/src/impl/bison/BisonParserGenerated.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        std::string msg = YY_("syntax error");
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

#if YYDEBUG || 0
  const char *
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0









  const signed char parser::yypact_ninf_ = -4;

  const signed char parser::yytable_ninf_ = -1;

  const signed char
  parser::yypact_[] =
  {
       8,     8,    -4,     5,    -3,     6,    -4,     8,     8,     8,
       8,    -4,    11,    11,    -4,    -4
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     3,     0,     2,     0,     1,     0,     0,     0,
       0,     8,     5,     4,     6,     7
  };

  const signed char
  parser::yypgoto_[] =
  {
      -4,    -4,    -1
  };

  const signed char
  parser::yydefgoto_[] =
  {
       0,     3,     4
  };

  const signed char
  parser::yytable_[] =
  {
       5,     7,     8,     9,    10,     6,    12,    13,    14,    15,
       7,     8,     9,    10,     0,    11,     1,     9,    10,     2
  };

  const signed char
  parser::yycheck_[] =
  {
       1,     4,     5,     6,     7,     0,     7,     8,     9,    10,
       4,     5,     6,     7,    -1,     9,     8,     6,     7,    11
  };

  const signed char
  parser::yystos_[] =
  {
       0,     8,    11,    13,    14,    14,     0,     4,     5,     6,
       7,     9,    14,    14,    14,    14
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    12,    13,    14,    14,    14,    14,    14,    14
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     1,     3,     3,     3,     3,     3
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "END_OF_INPUT", "error", "\"invalid token\"", "\"\\n\"", "\"-\"",
  "\"+\"", "\"*\"", "\"/\"", "\"(\"", "\")\"", "\"identifier\"",
  "\"number\"", "$accept", "input", "exp", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const signed char
  parser::yyrline_[] =
  {
       0,    82,    82,    85,    86,    87,    88,    89,    90
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 30 "/home/scientist73/projects/Algebra/calc/pars/Parser/src/impl/bison/Bison_Parser.y"
} } } } } // alg::calc::pars::impl::bison
#line 887 "/home/scientist73/projects/Algebra/calc/pars/Parser/src/impl/bison/BisonParserGenerated.cpp"

#line 92 "/home/scientist73/projects/Algebra/calc/pars/Parser/src/impl/bison/Bison_Parser.y"


using alg::calc::pars::impl::bison::parser;

NumType<double> parse_result;
std::queue<parser::symbol_type> parser_tokens;


void alg::calc::pars::impl::bison::setParseResult(const NumType<double>& parse_result)
{
    ::parse_result = parse_result;
}
parser::symbol_type alg::calc::pars::impl::bison::yylex ()
{
    auto token = parser_tokens.front();
    parser_tokens.pop();
    return token;
}
void alg::calc::pars::impl::bison::pushToken(TokenType token)
{
    switch (token.getTokenType())
    {
    case TOKEN::TERMINATION:
    {
        auto term_token = get_token<TerminationTokenType>(token);
        switch (term_token.getTerminationTokenType())
        {
        case TerminationTokenType::TERMINATION::END_OF_INPUT:
            parser_tokens.push(parser::make_END_OF_INPUT());
            break;
        case TerminationTokenType::TERMINATION::END_OF_LINE:
            parser_tokens.push(parser::make_END_OF_LINE());
            break;
        }
        break;
    }
    case TOKEN::IDENTIFIER:
    {
        auto id_token = get_token<IdentifierTokenType>(token);
        parser_tokens.push(parser::make_ID(id_token.getIdentifier()));
        break;
    }
    case TOKEN::NUM:
    {
        auto num_token = get_token<NumTokenType>(token);
        // modify code here
        switch (num_token.getNumTokenType())
        {
        case NumTokenType::NUM::REAL:
            parser_tokens.push(parser::make_NUM(NumType<double>(Real<double>(std::stod(std::string(num_token.getScalar()))))));
            break;
        case NumTokenType::NUM::IMAG:
            parser_tokens.push(parser::make_NUM(NumType<double>(Complex<double>(0, std::stod(std::string(num_token.getScalar()))))));
            break;
        }
        break;
    }
    case TOKEN::OPERATOR:
    {
        auto op_token = get_token<OperatorTokenType>(token);
        switch (op_token.getOperatorTokenType())
        {
        case OperatorTokenType::OPERATOR::PLUS:
            parser_tokens.push(parser::make_PLUS());
            break;
        case OperatorTokenType::OPERATOR::MINUS:
            parser_tokens.push(parser::make_MINUS());
            break;
        case OperatorTokenType::OPERATOR::MULT:
            parser_tokens.push(parser::make_MULT());
            break;
        case OperatorTokenType::OPERATOR::DIV:
            parser_tokens.push(parser::make_DIV());
            break;
        }
        break;
    }
    case TOKEN::PAREN:
    {
        auto paren_token = get_token<ParenTokenType>(token);
        switch (paren_token.getParenTokenType())
        {
        case ParenTokenType::PAREN::ROUND_CLOSE:
            parser_tokens.push(parser::make_PAREN_ROUND_CLOSE());
            break;
        case ParenTokenType::PAREN::ROUND_OPEN:
            parser_tokens.push(parser::make_PAREN_ROUND_OPEN());
            break;
        }
        break;
    }
    case TOKEN::EMPTY:
        throw std::runtime_error("parser received empty token");
    }
}
NumType<double> alg::calc::pars::impl::bison::getParseResult()
{
    return parse_result;
}


void parser::error(const std::string& err_mes) 
{
    throw std::runtime_error(err_mes);
}
