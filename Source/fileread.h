//---------------------------------------------------------------------------

#ifndef FileReadH
#define FileReadH
//---------------------------------------------------------------------------

# include "filebase.h"

class  PACKAGE TFileRead : public TFileBase
{
        typedef TFileBase Inherited ;
public:
        __fastcall TFileRead ( TComponent *  ) ;

private:
        AnsiString FCurrentLine ; 
        AnsiString FDelim ;
        int FBuffSz ;

protected:
        virtual __fastcall ~TFileRead ( )  { } ;
        bool __fastcall Next ( ) ;
        bool __fastcall Next ( TStringList * ) ;
        bool __fastcall Next ( AnsiString , int ) ;
        bool __fastcall Next ( AnsiString , int , TStringList * ) ;

__published:
        __property AnsiString CurrentLine    = { read = FCurrentLine , write = FCurrentLine } ;
        __property AnsiString LineDelimiter  = { read = FDelim       , write = FDelim       } ;

};
#endif
 