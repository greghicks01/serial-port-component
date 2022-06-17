//---------------------------------------------------------------------------
/*
 *                          Department of Defence
 *                                  © 2006
 *                            Software Engineer
 *                             Gregory Hicks
 *
 *    Component base for file reading/writing.
 *    Automatically opens valid files,
 *    Close previous file if open or if blank filename sent
 *    Events Open,Close,BOF,EOF and Fail
 *
 *    $Log: FileBase.cpp $
 *    Revision 1.1  2006/09/21 02:49:55  Administrator
 *    Initial revision
 *
 *
*/
#include <vcl.h>
#pragma hdrstop

#include "FileBase.h"
#pragma package(smart_init)
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
/*

static void ValidCtrCheck ( TFileBase * )
{
        new TFileBase(NULL);
}
//---------------------------------------------------------------------------
namespace Filebase
{
        void __fastcall PACKAGE Register ( )
        {
                 TComponentClass classes[1] = {__classid(TFileBase)};
                 RegisterComponents("Test", classes, 0);
        }
}//*/
//---------------------------------------------------------------------------

const AnsiString TFileBase::pathDelim = "\\"         ;

/*
  Purpose: Opens valid filename or creates new file to write to
  Accepts: NIL
  Returns: NIL
*/
__fastcall TFileBase::TFileBase ( TComponent * Owner ) :
        Inherited ( Owner ) , FFileHandle ( -1 ) , FFileName ( "" ) ,
        FFmConst  ( -1 )    , FAutoCreate ( true ) , FPath ( "" )
{
}
//---------------------------------------------------------------------------

/*
  Purpose: Opens valid filename or creates new file to write to
  Accepts: NIL
  Returns: NIL
*/

void __fastcall TFileBase::Open ( )
{
    // Close previous file if open
    if ( FFileHandle != -1 )
        Close ( ) ;

    AnsiString t = FPath + FFileName ;

    // If file not present, create
    if ( ! FileExists ( t ) && FAutoCreate )
        FFileHandle = FileCreate ( t ) ;
    else
        FFileHandle = FileOpen ( t , FFmConst ) ;

    TestOpen ( ) ;

}
//---------------------------------------------------------------------------

/*
  Purpose: Test if open worked as expected and record file length
           Trigger Open or Fail events as needed
  Accepts: NIL
  Returns: NIL
*/

void __fastcall TFileBase::TestOpen ( )
{
    // Make sure file handle is valid
    if ( FFileHandle > 0 )
    {
        FSuccess = true ;
        FFileLength = FileSeek ( FFileHandle , 0 , 2 ) ;
        Reset ( ) ;

        if ( FOnOpen )
                FOnOpen ( this ) ;
    }
    // invalid handle detected
    else
    {
        FSuccess = false ;

        if ( FOnFail )
                FOnFail ( this ) ;
    }
}

//---------------------------------------------------------------------------

/*
  Purpose: Moves filepointer to start of file
  Accepts: NIL
  Returns: NIL
*/

void __fastcall TFileBase::Reset ( )
{
        //Only do when valid file is set
        if ( FSuccess )
                FileSeek ( FFileHandle , 0 , 0 ) ;
}

//---------------------------------------------------------------------------

/*
  Purpose:  Closes previously open file and resets Success and FileHandle
  Accepts:  NIL
  Returns:  NIL
*/
void __fastcall TFileBase::Close ( )
{
        //DONE: Add your source code here
        if ( FSuccess )
        {
                FileClose ( FFileHandle ) ;
                FSuccess = false ;
                FFileHandle = -1 ;

                if ( FOnClose )
                        FOnClose ( this ) ;
        }
}
//---------------------------------------------------------------------------

/*
  Purpose: Detects EOF condition, triggers EOF event
  Accepts: NIL
  Returns: true if EOF
*/

bool __fastcall TFileBase::GetEOF ( )
{
        //DONE: Add your source code here
        if ( FSuccess )
        {
                if ( FileSeek (FFileHandle , 0 , 1 ) == FFileLength )
                {
                        if ( FOnEOF )
                                FOnEOF ( this ) ;

                        return true ;
                }
                else
                        return false ;
        }

        return true ;
}

//---------------------------------------------------------------------------

/*
  Purpose: Detects BOF condition, triggers BOF event
  Accepts: NIL
  Returns: true if BOF
*/

bool __fastcall TFileBase::GetBOF()
{
        //DONE: Add your source code here
        if ( FSuccess )
        {
                if ( FileSeek ( FFileHandle , 0, 1 ) == 0 )
                {
                        if ( FOnBOF )
                                FOnBOF ( this ) ;

                        return true ;
                }
                else
                        return false ;
        }

        return true ;
}
//---------------------------------------------------------------------------

/*
  Purpose: Detects name change and attempts to open file,
           Blank name forces close
           Resend previous value force pointer reset
  Accepts: value - path and filename to open
  Returns:
*/

void __fastcall TFileBase::SetFileName ( AnsiString value )
{
        //TODO: Add your source code here
        if ( ! FPath.IsEmpty ( ) )
        {
                if ( FFileName != value )
                {
                        FFileName = value ;

                        if ( FFileName.IsEmpty ( ) )
                        {
                                Close ( ) ;
                        }
                        else
                        {
                                if ( FFmConst != -1 )
                                        Open ( ) ;
                        }
                }
                else
                {
                        Reset ( ) ;
                }
        }
        else
        {
                //TODO: create a path not set event 
        }
}
//---------------------------------------------------------------------------

/*
  Purpose: Sets File Mode Constants, may try opening the file
  Accepts: value = File Mode Constants
  Returns: NIL
*/

void __fastcall TFileBase::SetFMConst ( int value )
{
        //TODO: Add your source code here
        if ( FFmConst != value )
        {
                FFmConst = value ;

                if ( ! FFileName.IsEmpty() && FFmConst != -1 )
                        Open ( ) ;
        }
}
//---------------------------------------------------------------------------

/*
  Purpose: To prepare path with trailing \
  Accepts: value = Path information
  Returns: NIL
*/

void __fastcall TFileBase::SetFPath ( AnsiString v )
{
        //TODO: Add your source code here
        FPath = ( v [ v.Length ( ) ] == pathDelim ) ? v : v + pathDelim  ;
}
