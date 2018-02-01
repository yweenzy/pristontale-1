#define SQLSOR_CPP

#include <windows.h>
#include <windowsx.h>
#include <winbase.h>
#include <stdio.h>
#include <tchar.h>

#include "common.h"
#include "GameSql.h"

#ifdef _W_SERVER

//±âÅ¸ ÀÓ½Ã ±â·Ï ÆÄÀÏ·Î ³²±è
int Record_TempLogFile(char *szMessage);

#ifdef _USE_NEW_MSSQL_CLASS

SQLDATA::SQLDATA()
{
}

SQLDATA::~SQLDATA()
{
}

void SQLDATA::ShowErrorInfo(SQLRETURN rc, SQLSMALLINT hType, SQLHANDLE h)
{
	SQLRETURN retcode;
	SQLSMALLINT iRecord = 1;
	SQLCHAR szSqlState[REM_LEN];
	SQLINTEGER pfNativeError;
	SQLCHAR szErrorMsg[REM_LEN];
	SQLSMALLINT cbErrorMsgMax = REM_LEN - 1;
	SQLSMALLINT pcbErrorMsg;


	Utils_Log(LOG_ERROR, "Handle type: %s\n", (hType == SQL_HANDLE_STMT) ? "Statement" :
		(hType == SQL_HANDLE_ENV) ? "Environment" :
		(hType == SQL_HANDLE_DBC) ? "DBC" : "???");


	retcode = SQLGetDiagRec(hType, h, // SQL_HANDLE_STMT, m_hstmt,
		iRecord, szSqlState, &pfNativeError,
		szErrorMsg, cbErrorMsgMax, &pcbErrorMsg);


	Utils_Log(LOG_ERROR, " *** %s *** sqlstate '%s'       errormsg '%s'\n",
		(rc == SQL_ERROR) ? "SQL_ERROR" :
		(rc == SQL_SUCCESS_WITH_INFO) ? "SQL_SUCCESS_WITH_INFO" : "",
		szSqlState, szErrorMsg);

	/*
	if (m_nLastError == 0)
	{
	m_nLastError = rc;
	m_strLastErrorSqlState = (char*)szSqlState;
	m_strLastErrorMessage = (char*)szErrorMsg;
	}
	*/
}

int SQLDATA::Start_ODBC()
{
	char *svr_name;
	char *user_name;
	char *user_pswd;

	if (Odbc_Config.Dsn[0])
	{
		svr_name = Odbc_Config.Dsn;
		user_name = Odbc_Config.Name;
		user_pswd = Odbc_Config.Password;
	}
	else
	{
		svr_name = "localhost\\SQLEXPRESS";
		user_name = "c8master";
		user_pswd = "c8master";
	}

	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env_hdl))
	{
		Utils_Log(LOG_ERROR, "SQLDATA: Unable to allocate handle for environment.");
		return 0;
	}

	if (SQL_SUCCESS != SQLSetEnvAttr(env_hdl, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
	{
		Utils_Log(LOG_ERROR, "SQLDATA: Unable to set ODBC version.");
		return 0;
	}

	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, env_hdl, &conn_hdl))
	{
		Utils_Log(LOG_ERROR, "SQLDATA: Unable to allocate handle for connection.");
		return 0;
	}

	wsprintf(connectString, "DRIVER={SQL Server};SERVER=%s;DATABASE=accountdb;UID=%s;PWD=%s;", svr_name, user_name, user_pswd);
	//Utils_Log(LOG_DEBUG, "User Sql Config Server: %s  User: %s Pass: %s", svr_name, user_name, user_pswd);

	SQLRETURN retcode = SQLDriverConnect(conn_hdl, NULL, (SQLCHAR*)TEXT(connectString), SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);
	if (SQL_SUCCESS != retcode && SQL_SUCCESS_WITH_INFO != retcode)
	{
		ShowErrorInfo(retcode, SQL_HANDLE_DBC, conn_hdl);
		return 0;
	}

	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, conn_hdl, &stmt_hdl))
	{
		Utils_Log(LOG_ERROR, "SQLAllocHandle failed. Error 4");
		return 0;
	}

	return 1;
}

int SQLDATA::End_ODBC()
{
	int r;

	if (stmt_hdl != NULL)
	{
		r = SQLFreeHandle(SQL_HANDLE_STMT, stmt_hdl);
		if (r == SQL_ERROR)
			return 0;
	}

	if (conn_hdl != NULL)
	{
		r = SQLDisconnect(conn_hdl);
		if (r == SQL_ERROR)
			return 0;
		r = SQLFreeHandle(SQL_HANDLE_DBC, conn_hdl);
		if (r == SQL_ERROR)
			return 0;
	}

	if (env_hdl != NULL)
	{
		r = SQLFreeHandle(SQL_HANDLE_ENV, env_hdl);
		if (r == SQL_ERROR)
			return 0;
	}
	return 1;
}

int	SQLDATA::LogOn(char *szID, char *szPassword)
{
	char id[128] = { 0, };
	char pass[128] = { 0, };
	char sell, block;
	//char	Temp[256];

	int r;

	///////////////// ID Find a table according to the first letter ////////////////////// 

	BYTE	ch;
	char TableName[32];

	ch = (BYTE)szID[0];
	TableName[0] = 0;

	if (ch >= 'a' && ch <= 'z')
	{
		// TableName[0] = ch;
		// TableName[1] = 0;
		// Changed parts
		TableName[0] = ch - 32;
		TableName[1] = 0;
	}
	else
	{
		if (ch >= 'A' && ch <= 'Z')
		{
			// TableName[0] = ch+0x20;
			// TableName[1] = 0;
			// Changed parts
			TableName[0] = ch;
			TableName[1] = 0;
		}
		else
		{
			if (ch >= '0' && ch <= '9')
			{
				// lstrcpy( TableName , "number" );
				// Changed parts
				lstrcpy(TableName, "[0GameUser]");
			}
			else
			{
				// lstrcpy( TableName , "etc" );
				// Changed parts
				lstrcpy(TableName, "[9GameUser]");
			}
		}
	}

	if (!TableName[0])
		return -1;

	/////////////////////////////////////////////////////////////////////////
	// wsprintf( stmt_buf , "SELECT * FROM %s_member WHERE u_id='%s'" , TableName , szID );
	// º¯°æµÈ ºÎºÐ
	wsprintf(stmt_buf, "SELECT * FROM %sGameUser WHERE userid='%s'", TableName, szID);


	//wsprintf( stmt_buf , "SELECT * FROM AllGameUser WHERE userid='%s'" , szID );

	//Other leaving a temporary log file
	//wsprintf( Temp , "%s\r\n" , stmt_buf );
	//Record_TempLogFile( Temp );
	r = SQLExecDirect(stmt_hdl, (unsigned char*)stmt_buf, SQL_NTS);
	if (r == SQL_ERROR)
		return 0;											//No connection

	// Changed parts
	r = SQLBindCol(stmt_hdl, 2, SQL_C_CHAR, &pass, 9, NULL);
	r = SQLBindCol(stmt_hdl, 11, SQL_C_UTINYINT, &sell, 1, NULL);
	r = SQLBindCol(stmt_hdl, 12, SQL_C_UTINYINT, &block, 1, NULL);


	if (SQLFetch(stmt_hdl) == SQL_NO_DATA_FOUND)			//No account
		return -1;

	SQLFreeStmt(stmt_hdl, SQL_CLOSE);

	if (lstrcmpi(szPassword, pass) != 0)
		return -2;											//Password check
	if (Odbc_Config.CloseAccount && sell != 1)
		return -3;											//No permission (not a beta tester)
	if (block)
		return -3;											//Account block

	return TRUE;		//Certification Success
}

SQLDATA		SqlData;

int SqlLogOn(char *szID, char *szPass)
{
	int val;
	SqlData.Start_ODBC();
	val = SqlData.LogOn(szID, szPass);
	SqlData.End_ODBC();

	return val;
}

#else

SQLDATA::SQLDATA()
{
}
SQLDATA::~SQLDATA()
{
}

int SQLDATA::Start_ODBC()
{
	char *svr_name;
	char *user_name;
	char *user_pswd;

	int r;

	if (Odbc_Config.Dsn[0]) {
		svr_name = Odbc_Config.Dsn;
		user_name = Odbc_Config.Name;
		user_pswd = Odbc_Config.Password;
	}
	else {
		svr_name = "c8master";
		user_name = "c8master";
		user_pswd = "joddo";
	}


	r = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env_hdl);
	//fd("start 00 rrrrrrrr %d ", r);
	if (r == SQL_ERROR) return 0;
	SQLSetEnvAttr(env_hdl, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, SQL_IS_INTEGER);

	r = SQLAllocHandle(SQL_HANDLE_DBC, env_hdl, &conn_hdl);
	//fd("start 11 rrrrrrrr %d ", r);
	if (r == SQL_ERROR) return 0;

	//r = SQLConnect(conn_hdl,(SQLTCHAR*)svr_name, SQL_NTS,
	//                        (SQLTCHAR*)user_name, SQL_NTS,
	//                        (SQLTCHAR*)user_pswd, SQL_NTS);
	r = SQLConnect(conn_hdl, (unsigned char*)svr_name, SQL_NTS,
		(unsigned char*)user_name, SQL_NTS,
		(unsigned char*)user_pswd, SQL_NTS);

	//fd("start 22 rrrrrrrr %d ", r);
	if (r == SQL_ERROR) return 0;

	r = SQLAllocHandle(SQL_HANDLE_STMT, conn_hdl, &stmt_hdl);
	//fd("start 33 rrrrrrrr %d ", r);
	return 1;
}

int SQLDATA::End_ODBC()
{
	int r;

	if (stmt_hdl != NULL) {
		r = SQLFreeHandle(SQL_HANDLE_STMT, stmt_hdl);
		//fd("End 00 rrrrrrrr %d ", r);
		if (r == SQL_ERROR) return 0;
	}

	if (conn_hdl != NULL) {
		r = SQLDisconnect(conn_hdl);
		//fd("End 11 rrrrrrrr %d ", r);
		if (r == SQL_ERROR) return 0;
		r = SQLFreeHandle(SQL_HANDLE_DBC, conn_hdl);
		//fd("End 22 rrrrrrrr %d ", r);
		if (r == SQL_ERROR) return 0;
	}

	if (env_hdl != NULL) {
		r = SQLFreeHandle(SQL_HANDLE_ENV, env_hdl);
		//fd("End 33 rrrrrrrr %d ", r);
		if (r == SQL_ERROR) return 0;
	}
	return 1;
}

int	SQLDATA::LogOn(char *szID, char *szPassword)
{

	char id[128] = { 0, };
	char pass[128] = { 0, };
	char sell, block;
	//char	Temp[256];

	int r;

	//u_hope		->°èÁ¤ºí·° ( 0 - ÀÏ¹Ý  1 - °ÔÀÓ¸øÇÏ°Ô )
	/*
	if ( !Odbc_Config.Dsn[0] ) {
	//±âº» ¼³Á¤

	///////////////// ID Ã¹±ÛÀÚ¿¡ µû¸¥ Å×ÀÌºí Ã£±â //////////////////////
	BYTE	ch;
	char TableName[32];

	ch = (BYTE)szID[0];
	TableName[0]=0;

	if ( ch>='a' && ch<='z' ) {
	TableName[0] = ch;
	TableName[1] = 0;
	}
	else {
	if ( ch>='A' && ch<='Z' ) {
	TableName[0] = ch+0x20;
	TableName[1] = 0;
	}
	else {
	if ( ch>='0' && ch<='9' ) {
	lstrcpy( TableName , "number" );
	}
	else {
	lstrcpy( TableName , "etc" );
	}
	}
	}

	if ( !TableName[0] )
	return -1;
	/////////////////////////////////////////////////////////////////////////

	wsprintf( stmt_buf , "SELECT * FROM %s_member WHERE u_id='%s'" , TableName , szID );
	r = SQLExecDirect(stmt_hdl, (unsigned char*)stmt_buf, SQL_NTS);
	if(r== SQL_ERROR) return 0;											//¿¬°á ºÒ°¡

	r = SQLBindCol(stmt_hdl, 3, SQL_C_CHAR, &pass, 9 , NULL);
	r = SQLBindCol(stmt_hdl, 17, SQL_C_UTINYINT , &sell, 1 , NULL);
	r = SQLBindCol(stmt_hdl, 20, SQL_C_UTINYINT , &block, 1 , NULL);

	if(SQLFetch(stmt_hdl) == SQL_NO_DATA_FOUND )
	return -1;				//°èÁ¤ÀÌ ¾øÀ½

	SQLFreeStmt( stmt_hdl, SQL_CLOSE );

	if ( lstrcmpi( szPassword , pass )!=0 ) return -2;					//ºñ¹ø Æ²¸²
	if ( Odbc_Config.CloseAccount && sell!=1 ) return -3;			//±ÇÇÑ¾øÀ½ ( º£Å¸Å×½ºÅÍ ¾Æ´Ô )
	if ( block ) return -3;											//°èÁ¤ ºí·°
	}
	*/

	if (!Odbc_Config.Dsn[0]) {
		//±âº» ¼³Á¤ 

		///////////////// ID Ã¹±ÛÀÚ¿¡ µû¸¥ Å×ÀÌºí Ã£±â ////////////////////// 
		BYTE	ch;
		char TableName[32];

		ch = (BYTE)szID[0];
		TableName[0] = 0;

		if (ch >= 'a' && ch <= 'z') {
			// TableName[0] = ch;
			// TableName[1] = 0;
			// º¯°æµÈ ºÎºÐ
			TableName[0] = ch - 0x20;
			TableName[1] = 0;
		}
		else {
			if (ch >= 'A' && ch <= 'Z') {
				// TableName[0] = ch+0x20;
				// TableName[1] = 0;
				// º¯°æµÈ ºÎºÐ
				TableName[0] = ch;
				TableName[1] = 0;
			}
			else {
				if (ch >= '0' && ch <= '9') {
					// lstrcpy( TableName , "number" );
					// º¯°æµÈ ºÎºÐ
					lstrcpy(TableName, "[0GameUser]");
				}
				else {
					// lstrcpy( TableName , "etc" );
					// º¯°æµÈ ºÎºÐ
					lstrcpy(TableName, "[9GameUser]");
				}
			}
		}

		if (!TableName[0])
			return -1;
		/////////////////////////////////////////////////////////////////////////

		// wsprintf( stmt_buf , "SELECT * FROM %s_member WHERE u_id='%s'" , TableName , szID );
		// º¯°æµÈ ºÎºÐ
		wsprintf(stmt_buf, "SELECT * FROM %sGameUser WHERE userid='%s'", TableName, szID);

		//±âÅ¸ ÀÓ½Ã ±â·Ï ÆÄÀÏ·Î ³²±è
		//wsprintf( Temp , "%s\r\n" , stmt_buf );
		//Record_TempLogFile( Temp );

		r = SQLExecDirect(stmt_hdl, (unsigned char*)stmt_buf, SQL_NTS);
		if (r == SQL_ERROR) {
			return 0;											//¿¬°á ºÒ°¡
		}

		//r = SQLBindCol(stmt_hdl, 3, SQL_C_CHAR, &pass, 9 , NULL);
		//r = SQLBindCol(stmt_hdl, 17, SQL_C_UTINYINT , &sell, 1 , NULL);
		//r = SQLBindCol(stmt_hdl, 20, SQL_C_UTINYINT , &block, 1 , NULL);
		// º¯°æµÈ ºÎºÐ

		r = SQLBindCol(stmt_hdl, 2, SQL_C_CHAR, &pass, 9, NULL);
		r = SQLBindCol(stmt_hdl, 11, SQL_C_UTINYINT, &sell, 1, NULL);
		r = SQLBindCol(stmt_hdl, 12, SQL_C_UTINYINT, &block, 1, NULL);


		if (SQLFetch(stmt_hdl) == SQL_NO_DATA_FOUND)  {

			return -1;				//°èÁ¤ÀÌ ¾øÀ½
		}

		SQLFreeStmt(stmt_hdl, SQL_CLOSE);

		if (lstrcmpi(szPassword, pass) != 0) return -2;	//ºñ¹ø Æ²¸²
		if (Odbc_Config.CloseAccount && sell != 1) return -3;	//±ÇÇÑ¾øÀ½ ( º£Å¸Å×½ºÅÍ ¾Æ´Ô )
		if (block) return -3;					//°èÁ¤ ºí·°
	}

	else {
		//À¯Àú ¼³Á¤  ( ÇÑ°ÔÀÓ µîµî )
		wsprintf(stmt_buf, "SELECT * FROM %s WHERE %s='%s'", Odbc_Config.Table, Odbc_Config.Table_Id, szID);
		r = SQLExecDirect(stmt_hdl, (unsigned char*)stmt_buf, SQL_NTS);
		if (r == SQL_ERROR) return 0;											//¿¬°á ºÒ°¡

		r = SQLBindCol(stmt_hdl, Odbc_Config.Table_Password, SQL_C_CHAR, &pass, 16, NULL);
		if (Odbc_Config.Table_Play) {
			r = SQLBindCol(stmt_hdl, Odbc_Config.Table_Play, SQL_C_UTINYINT, &sell, 1, NULL);
		}
		else {
			sell = 1;
		}

		if (SQLFetch(stmt_hdl) == SQL_NO_DATA_FOUND) return -1;				//°èÁ¤ÀÌ ¾øÀ½

		SQLFreeStmt(stmt_hdl, SQL_CLOSE);

		if (lstrcmpi(szPassword, pass) != 0) return -2;					//ºñ¹ø Æ²¸²
		if (Odbc_Config.CloseAccount && sell != 1) return -3;											//±ÇÇÑ¾øÀ½ ( º£Å¸Å×½ºÅÍ ¾Æ´Ô )

	}

	return TRUE;		//ÀÎÁõ ¼º°ø
}



SQLDATA		SqlData;


int SqlLogOn(char *szID, char *szPass)
{
	int val;
	SqlData.Start_ODBC();
	val = SqlData.LogOn(szID, szPass);
	SqlData.End_ODBC();

	return val;
}

int LogTest()
{
	int val;

	SqlData.Start_ODBC();

	val = SqlData.LogOn("penguinboy", "pengo1");

	SqlData.End_ODBC();

	return TRUE;
}

#endif

#endif

int	InitODBC()
{
	return TRUE;
}

int	CloseODBC()
{
	return TRUE;
}
