@ECHO OFF
CLS
ECHO This file batches the insertion of:
ECHO     1)      *.h
ECHO     2)      *.cpp
ECHO     3)      *.dfm
ECHO     4)      *.bpr
ECHO     files to protect from loss should the system fall over
ECHO     and provide the ability to work bacwards if a build fails.
PAUSE
CLS
echo.
echo Entering files into RCS tree
echo.
ci -l *.h
ci -l *.cpp
ci -l *.dfm
ci -l *.bpr
echo.
ECHO Completed RCS Tree insertion.
ECHO Removing Builder Temporary Files
del *.~*
echo Job Done
:END
