@echo off

echo type args ...
echo models: name path
echo shaders: name vertex_shader_path fragment_shader_path
echo fonts: name path

SET /P argType=Type:
SET /P argName=Name:
SET /P argPath1=Path1:
SET /P argPath2=Path2(Optional):

echo %argType% %argName% %argPath1% %argPath2%

..\ThirdParty\Nodejs\Windows\node.exe Importer.js %argType% %argName% %argPath1% %argPath2

timeout /t 10
