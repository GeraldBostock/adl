@echo off

SETLOCAL DISABLEDELAYEDEXPANSION

SET /P className=ClassName:
SET /p classPath=Path: ..\..\source\?

echo ClassName : %className%
echo ClassPath : %classPath%

call :CreateClass Templates\cppTemplate.txt cpp
call :CreateClass Templates\hTemplate.txt h

ENDLOCAL

echo Completed!
timeout /t 5

:CreateClass
echo %~2
FOR /f "tokens=1,* delims=�" %%L IN (%~1) DO (
  SET "line=%%L"
  SETLOCAL ENABLEDELAYEDEXPANSION
  echo !line:${Class}=%className%! >> ..\..\source\%classPath%\%className%.%~2 
  echo. >> ..\..\source\%classPath%\%className%.%~2
  ENDLOCAL
)
exit /b 0
