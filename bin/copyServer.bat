@echo off
cd /d %~dp0

IF EXIST Client\char (
	echo Copying server files...
    IF NOT EXIST Server\char (
		mkdir Server\char 
		xcopy /R /D /I /S /Y /EXCLUDE:serverCopyExclude.txt "Client\char\*" "Server\char\*"
	)
	IF NOT EXIST Server\field (
		mkdir Server\field 
		xcopy /R /D /I /S /Y /EXCLUDE:serverCopyExclude.txt "Client\field\*" "Server\field\*"
	)		
)
echo done
exit 0