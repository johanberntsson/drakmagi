@echo off
rem informbp
rem if errorlevel 2 goto pathok
rem echo Setting path
set PATH=..\bin;%PATH%
:pathok
front game game.inf game.ulx > err.txt
if errorlevel 1 goto uncool
wglulxe game.blb
goto slut:
:uncool
type err.txt | more
:slut
