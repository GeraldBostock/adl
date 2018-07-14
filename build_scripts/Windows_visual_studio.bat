@echo off

cd ..

mkdir build
cd build

cmake ../

mkdir Debug
mkdir Release
copy ..\dependencies\bin\ Debug
copy ..\dependencies\bin\ Release
cd ..

set /p DUMMY=Hit ENTER to continue...