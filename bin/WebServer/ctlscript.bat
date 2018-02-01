@echo off
rem START or STOP Services
rem ----------------------------------
rem Check if argument is STOP or START

if not ""%1"" == ""START"" goto stop

if exist D:\xampp\hypersonic\scripts\ctl.bat (start /MIN /B D:\xampp\server\hsql-sample-database\scripts\ctl.bat START)
if exist D:\xampp\ingres\scripts\ctl.bat (start /MIN /B D:\xampp\ingres\scripts\ctl.bat START)
if exist D:\xampp\mysql\scripts\ctl.bat (start /MIN /B D:\xampp\mysql\scripts\ctl.bat START)
if exist D:\xampp\postgresql\scripts\ctl.bat (start /MIN /B D:\xampp\postgresql\scripts\ctl.bat START)
if exist D:\xampp\apache\scripts\ctl.bat (start /MIN /B D:\xampp\apache\scripts\ctl.bat START)
if exist D:\xampp\openoffice\scripts\ctl.bat (start /MIN /B D:\xampp\openoffice\scripts\ctl.bat START)
if exist D:\xampp\apache-tomcat\scripts\ctl.bat (start /MIN /B D:\xampp\apache-tomcat\scripts\ctl.bat START)
if exist D:\xampp\resin\scripts\ctl.bat (start /MIN /B D:\xampp\resin\scripts\ctl.bat START)
if exist D:\xampp\jboss\scripts\ctl.bat (start /MIN /B D:\xampp\jboss\scripts\ctl.bat START)
if exist D:\xampp\jetty\scripts\ctl.bat (start /MIN /B D:\xampp\jetty\scripts\ctl.bat START)
if exist D:\xampp\subversion\scripts\ctl.bat (start /MIN /B D:\xampp\subversion\scripts\ctl.bat START)
rem RUBY_APPLICATION_START
if exist D:\xampp\lucene\scripts\ctl.bat (start /MIN /B D:\xampp\lucene\scripts\ctl.bat START)
if exist D:\xampp\third_application\scripts\ctl.bat (start /MIN /B D:\xampp\third_application\scripts\ctl.bat START)
goto end

:stop
echo "Stopping services ..."
if exist D:\xampp\third_application\scripts\ctl.bat (start /MIN /B D:\xampp\third_application\scripts\ctl.bat STOP)
if exist D:\xampp\lucene\scripts\ctl.bat (start /MIN /B D:\xampp\lucene\scripts\ctl.bat STOP)
rem RUBY_APPLICATION_STOP
if exist D:\xampp\subversion\scripts\ctl.bat (start /MIN /B D:\xampp\subversion\scripts\ctl.bat STOP)
if exist D:\xampp\jetty\scripts\ctl.bat (start /MIN /B D:\xampp\jetty\scripts\ctl.bat STOP)
if exist D:\xampp\hypersonic\scripts\ctl.bat (start /MIN /B D:\xampp\server\hsql-sample-database\scripts\ctl.bat STOP)
if exist D:\xampp\jboss\scripts\ctl.bat (start /MIN /B D:\xampp\jboss\scripts\ctl.bat STOP)
if exist D:\xampp\resin\scripts\ctl.bat (start /MIN /B D:\xampp\resin\scripts\ctl.bat STOP)
if exist D:\xampp\apache-tomcat\scripts\ctl.bat (start /MIN /B /WAIT D:\xampp\apache-tomcat\scripts\ctl.bat STOP)
if exist D:\xampp\openoffice\scripts\ctl.bat (start /MIN /B D:\xampp\openoffice\scripts\ctl.bat STOP)
if exist D:\xampp\apache\scripts\ctl.bat (start /MIN /B D:\xampp\apache\scripts\ctl.bat STOP)
if exist D:\xampp\ingres\scripts\ctl.bat (start /MIN /B D:\xampp\ingres\scripts\ctl.bat STOP)
if exist D:\xampp\mysql\scripts\ctl.bat (start /MIN /B D:\xampp\mysql\scripts\ctl.bat STOP)
if exist D:\xampp\postgresql\scripts\ctl.bat (start /MIN /B D:\xampp\postgresql\scripts\ctl.bat STOP)

:end

