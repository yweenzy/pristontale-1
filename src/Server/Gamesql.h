#include "..\\nettype.h"

#ifdef _W_SERVER

#include <windows.h>
#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>
#include <odbcss.h>

#define REM_LEN 1024

class SQLDATA
{
public:
	SQLHENV env_hdl;
	SQLHDBC conn_hdl;
	SQLHSTMT stmt_hdl;

	char stmt_buf[512];
	char errmsg[512];

	SQLDATA();
	~SQLDATA();

	int Start_ODBC();
	int End_ODBC();

	int	LogOn(char *szID, char *szPassword);
	void ShowErrorInfo(SQLRETURN rc, SQLSMALLINT hType, SQLHANDLE h);

private:
	char connectString[256];
};


#endif

////////////////////////////////////////////////////////////////////////
struct	ODBC_CONFIG {
	char	Dsn[32];			//Á¢¼Ó ¼­ºñ½º¸í
	char	Name[32];			//Á¢¼ÓÀÚ ID
	char	Password[32];		//Á¢¼ÓÀÚ ¾ÏÈ£

	char	Table[32];			//Å×ÀÌºí ÀÌ¸§
	char	Table_Id[32];		//Å×ÀÌºí °èÁ¤
	int		Table_Password;		//Å×ÀÌºí ¾ÏÈ£ ¿­
	int		Table_Play;			//Å×ÀÌºí Çã°¡ ¿­

	int		CloseAccount;		//Å×½ºÆ® À¯Àú¸¸ Çã¿ë

};

extern	ODBC_CONFIG	Odbc_Config;

int	InitODBC();
int	CloseODBC();
int SqlLogOn(char *szID, char *szPass);



