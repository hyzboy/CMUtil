#pragma once

enum class TokenType
{
    Unrecognized=0,

    End,

    WhiteSpace,         // ' ','\t','\r','\n'
    OnelineComment,     // //
    MultilineComment,   // /* */

    // Atoms
    Identifier,         // abc123
    Integer,            // 1234
    Float,              // 12.34
    String,             // "123"
    RawString,          // """text"""

    // Math operators
    Plus,               // +
    Minus,              // -
    Star,               // *
    Slash,              // /
    Percent,            // %

    Handle,             // #
    At,                 // @

    AddAssign,          // +=
    SubAssign,          // -=
    MulAssign,          // *=
    DivAssign,          // /=
    ModAssign,          // %=

    OrAssign,           // |=
    AndAssign,          // &=
    XorAssign,          // ^=
    ShiftLeftAssign,    // <<=
    ShiftRightAssign,   // >>=

    Inc,                // ++
    Dec,                // --

    Dot,                // .

    // Statement tokens
    Assignment,         // =
    EndStatement,       // ;
    ListSeparator,      // ,
    StartStatementBlock,// {
    EndStatementBlock,  // }
    OpenParenthesis,    // (
    CloseParenthesis,   // )
    OpenBracket,        // [
    CloseBracket,       // ]
    Amp,                // &

    Not,                // !
    Or,                 // ||
    And,                // &&
    Xor,                // ^^

    // Bitwise operators
    BitOr,              // |
    BitNot,             // ~
    BitXor,             // ^
    BitShiftLeft,       // <<
    BitShiftRight,      // >>

    // Compare operators
    Equal,              // ==
    NotEqual,           // !=
    LessThan,           // <
    GreaterThan,        // >
    LessThanOrEqual,    // <=
    GreaterThanOrEqual, // >=

    Question,           // ?
    Colon,              // :
};//

struct TokenWord
{
    const char *word;
    uint        work_size;
    uint        token_type;
};

constexpr TokenWord token_words[]=
{
#define DEFINE_TOKEN(str,type)  {str,sizeof(str)-1,uint(TokenType::type)}

    DEFINE_TOKEN("+",   Plus),
    DEFINE_TOKEN("-",   Minus),
    DEFINE_TOKEN("*",   Star),
    DEFINE_TOKEN("/",   Slash),
    DEFINE_TOKEN("%",   Percent),
    DEFINE_TOKEN("=",   Assignment),
    DEFINE_TOKEN(".",   Dot),
    DEFINE_TOKEN("+=",  AddAssign),
    DEFINE_TOKEN("-=",  SubAssign),
    DEFINE_TOKEN("*=",  MulAssign),
    DEFINE_TOKEN("/=",  DivAssign),
    DEFINE_TOKEN("%=",  ModAssign),
    DEFINE_TOKEN("|=",  OrAssign),
    DEFINE_TOKEN("&=",  AndAssign),
    DEFINE_TOKEN("^=",  XorAssign),
    DEFINE_TOKEN("<<=", ShiftLeftAssign),
    DEFINE_TOKEN(">>=", ShiftRightAssign),
    DEFINE_TOKEN("|",   BitOr),
    DEFINE_TOKEN("~",   BitNot),
    DEFINE_TOKEN("^",   BitXor),
    DEFINE_TOKEN("<<",  BitShiftLeft),
    DEFINE_TOKEN(">>",  BitShiftRight),
    DEFINE_TOKEN(";",   EndStatement),
    DEFINE_TOKEN(",",   ListSeparator),
    DEFINE_TOKEN("{",   StartStatementBlock),
    DEFINE_TOKEN("}",   EndStatementBlock),
    DEFINE_TOKEN("(",   OpenParenthesis),
    DEFINE_TOKEN(")",   CloseParenthesis),
    DEFINE_TOKEN("[",   OpenBracket),
    DEFINE_TOKEN("]",   CloseBracket),
    DEFINE_TOKEN("?",   Question),
    DEFINE_TOKEN(":",   Colon),
    DEFINE_TOKEN("==",  Equal),
    DEFINE_TOKEN("!=",  NotEqual),
    DEFINE_TOKEN("<",   LessThan),
    DEFINE_TOKEN(">",   GreaterThan),
    DEFINE_TOKEN("<=",  LessThanOrEqual),
    DEFINE_TOKEN(">=",  GreaterThanOrEqual),
    DEFINE_TOKEN("++",  Inc),
    DEFINE_TOKEN("--",  Dec),
    DEFINE_TOKEN("&",   Amp),
    DEFINE_TOKEN("!",   Not),
    DEFINE_TOKEN("||",  Or),
    DEFINE_TOKEN("&&",  And),
    DEFINE_TOKEN("^^",  Xor),
    DEFINE_TOKEN("#",   Handle),
    DEFINE_TOKEN("@",   At)

#undef DEFINE_TOKEN
};

constexpr uint TokenWordsNumber    =sizeof(token_words)/sizeof(TokenWord);
constexpr char WhiteSpaces[]       =" \t\r\n";
constexpr uint WhiteSpacesNumber   =sizeof(WhiteSpaces)-1;

/**
 * 通用词法解析器
 */
class Tokenizer
{

public:


};//class Tokenizer
