//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "filecopy.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
///*

static void ValidCtrCheck(TFileCopy *)
{
        new TFileCopy(NULL);
}
//---------------------------------------------------------------------------

namespace Filecopy
{
        void __fastcall PACKAGE Register()
        {
                 TComponentClass classes[1] = {__classid(TFileCopy)};
                 RegisterComponents("Test", classes, 0);
        }
}//*/
//---------------------------------------------------------------------------

__fastcall TFileCopy::TFileCopy(TComponent * Owner): Inherited ( Owner ) , FFileList ( NULL )
{
        //TODO: Add your source code here
} 
//---------------------------------------------------------------------------

__fastcall TFileCopy::~TFileCopy()
{
        //TODO: Add your source code here
}
//---------------------------------------------------------------------------

void TFileCopy::FileLineCopy()
{
        //TODO: Add your source code here
        AnsiString name = FileRename ( ) ;

        int NewFileHandle = FileCreate ( name ) ;

        while ( Next() )
        {
                AnsiString tmp = CurrentLine ;

                if ( FLineAlter )
                        tmp = FLineAlter ( NewFileHandle ) ;
                        
                FileWrite ( NewFileHandle , tmp.c_str ( )    , tmp.Length    ( ) ) ;
                FileWrite ( NewFileHandle , LineDelimiter.c_str ( ) , LineDelimiter.Length ( ) ) ;
        }

        FileClose ( NewFileHandle ) ;
        AnsiString oldFile = FileName ;
        FileName = name ;
        DeleteFile ( oldFile ) ;
}
//---------------------------------------------------------------------------

AnsiString TFileCopy::FileRename ( )
{
        //TODO: Add your source code here
        AnsiString newName = FileName ,
                   oldName = ExtractFilePath ( FileName ) + "_"
                             + ExtractFileName ( FileName ) ;

        if ( ! FileExists ( oldName ) )
        {
                Close ( ) ;

                RenameFile ( newName , oldName ) ;

                FileName = oldName ;
        }
        
        return newName ;
}
//---------------------------------------------------------------------------

void __fastcall TFileCopy::SetCopy( void )
{
        FileLineCopy ( ) ;
}
//---------------------------------------------------------------------------

void TFileCopy::FileRename( AnsiString fname )
{
        //TODO: Add your source code here
        AnsiString oldName = FileName ;

        FileName = "" ;

        RenameFile ( oldName , fname ) ;

        FileName = fname ;
}
//--------------------------------------------------------------------------

void __fastcall TFileCopy::FileScan ( )
{
        //TODO: Add your source code here
        if ( FFileList )
        {
                for ( int i = 0 ; i < FFileList->Count ; i++ )
                {
                        FileName = FFileList->Strings[i] ;
                        ScanFileAll ( ) ;
                }
        }
        else
        {
                Reset ( ) ;
                ScanFileAll ( ) ;
        }
}
//--------------------------------------------------------------------------

void __fastcall TFileCopy::ListFile ( )
{
        //TODO -oGreg: Add your source code here

        TSearchRec sr ;

        int iAttributes = faAnyFile ;

        if ( FindFirst ( Path + Pattern , iAttributes , sr ) == 0 )
        {
                do
                {
                        //TODO -oGreg: Add a call back function to increase code re-use
                        if ( FListFile )
                                FListFile ( sr ) ;

                } while ( FindNext ( sr ) == 0 ) ;
                FindClose ( sr ) ;
        } // if

}
//--------------------------------------------------------------------------

void TFileCopy::ScanFileAll ( ) 
{
        //TODO: Add your source code here
        
        while ( Next ( ) )
        {
                if ( FScanFile )
                        FScanFile ( FileHandle ) ;
        }
}
//--------------------------------------------------------------------------

void TFileCopy::WriteLine( )
{
        //TODO: Add your source code here
        if ( FWriteFile )
                FWriteFile ( FileHandle ) ;
}
//--------------------------------------------------------------------------

void __fastcall TFileCopy::DelFile  ( )
{
        // temp holder, release file
        AnsiString temp = FileName ;
        FileName = "" ;

        // delete the file
        if ( DeleteFile ( Path + temp ) )
                FileName = temp ;
        // else error occured
}
