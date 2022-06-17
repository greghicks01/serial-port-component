//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FileRead.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
///*

static void ValidCtrCheck(TFileRead *)
{
        new TFileRead(NULL);
}
//---------------------------------------------------------------------------
namespace Fileread
{
        void __fastcall PACKAGE Register()
        {
                 TComponentClass classes[1] = {__classid(TFileRead)};
                 RegisterComponents("Test", classes, 0);
        }
}//*/
//---------------------------------------------------------------------------

/*
  Purpose: Opens valid filename or creates new file to write to
  Accepts: NIL
  Returns: NIL
*/
__fastcall TFileRead::TFileRead ( TComponent * Owner ):
        Inherited ( Owner ), FBuffSz ( 20 ) , FDelim ( "\r\n" )
{
}

//---------------------------------------------------------------------------

/*
  Purpose: Opens valid filename or creates new file to write to
  Accepts: NIL
  Returns: NIL
*/

bool __fastcall TFileRead::Next()
{
    if ( EOF ) return false ;

    AnsiString tmp = "" ;

    int bytesRead;

    // buffer for FileRead
    char * buffer = new char [ FBuffSz + 1 ] ;

    // read until delimiter found or bytesRead < buffer size
    do
    {
        bytesRead = FileRead ( FileHandle , buffer , FBuffSz ) ;
        buffer [ bytesRead ] = 0 ;
        tmp += buffer ;
    } while ( tmp . Pos ( FDelim ) == 0 && bytesRead == FBuffSz ) ;

    delete[] buffer ;

    // Truncate the line to one char before the
    // delimiter and seek to new position
    if ( tmp . Pos ( FDelim ) != 0 )
    {
        int tL = tmp . Length ( ) ;
        tmp = tmp.SubString ( 1 , tmp.Pos ( FDelim ) -1 ) ;

        // seeks to the end of the delimiter
        FileSeek ( FileHandle , tmp . Length ( ) -  tL + FDelim . Length ( ) , 1 ) ;
    }

    FCurrentLine = tmp ;

    return true ;
}
//---------------------------------------------------------------------------

/*
  Purpose: Opens valid filename or creates new file to write to
  Accepts: NIL
  Returns: NIL
*/
bool __fastcall TFileRead::Next(AnsiString aThis , int here )
{
        //TODO: Add your source code here
        bool found = false;

        while ( ! EOF )
        {
                Next ( ) ;
                if ( CurrentLine . Pos ( aThis ) == here )
                {
                        found = true ;
                        break ;
                }
        }

        return found ;
}
//---------------------------------------------------------------------------

/*
  Purpose: Opens valid filename or creates new file to write to
  Accepts: NIL
  Returns: NIL
*/
bool __fastcall TFileRead::Next( AnsiString aThis , int here , TStringList * t )
{
        //TODO: Add your source code here
        bool found = false;

        while ( ! EOF )
        {
                if ( Next ( aThis , here ) )
                {
                        found = true ;
                        if ( t )
                                t->Add( CurrentLine ) ;
                }
        }

        return found ;
}
//---------------------------------------------------------------------------

/*
  Purpose: Opens valid filename or creates new file to write to
  Accepts: NIL
  Returns: NIL
*/
bool __fastcall TFileRead::Next(TStringList * t )
{
        //TODO: Add your source code here
        bool tmp = false ;

        while ( ! EOF )
        {
                if ( CurrentLine.IsEmpty ( ) )
                        continue ;

                if ( t )
                {
                        t->Add ( CurrentLine ) ;
                        tmp = true ;
                }
        }
        return tmp ;
} 

//---------------------------------------------------------------------------
