@echo off
rem START or STOP Services
rem ----------------------------------
rem Check if argument is STOP or START

if not ""%1"" == ""START"" goto stop


"D:\xampp\mysql\bin\mysqld" --defaults-file="D:\xampp\mysql\bin\my.ini" --standalone --console
if errorlevel 1 goto error
goto finish

:stop
"D:\xampp\apache\bin\pv" -f -k mysqld.exe -q

if not exist "D:\xampp\mysql\data\%computername%.pid" goto finish
echo Delete %computername%.pid ...
del "D:\xampp\mysql\data\%computername%.pid"
goto finish


:error
echo MySQL could not be started

:finish
exit
