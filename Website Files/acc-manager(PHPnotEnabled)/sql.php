<?php define("XPT",1);

/*----------------------------------------------------------------------
(c)2007 THAIKHOA - XTREMEVNPT TEAM (JUST BE SOLO ^_^)
 USED FOR NON-COMMERCIAL AND FAN OF PRISTONTALE SERVER
 CONTACT ME IF YOU HAVE SOME PROBLEMS
 EMAIL: thaikhoa@gmail.com
 XTREMEVN PT
 GAME IP: 210.245.33.245
 WEB: http://210.245.33.245:8080
 THANK YOU FOR USING MY XPT SCRIPTS!
 THANK L3zToXz FOR GOOD IDEAS AND THE XP FILE!

DOWNLOAD AND INSTALL PHP BINARY FROM http://www.php.net/downloads.php
CLICK NEXT, NEXT, NEXT, SELECT ISS CGI AND NEXT THEN CLICK INSTALL
USE ODBC
----------------------------------------------------------------------*/

// version;
$version = "ReloadedPT: Account manager :: version 0.01";

include_once("class.func.php");
$func = new func;

// PRISTON TALE SERVER ROOT
$rootDir = "C:/Server/";

// PRISTON TALE DATASERVER
// EVERYONE PERMISSION
$dirUserData   = $rootDir."DataServer/userdata/";
$dirUserInfo   = $rootDir."DataServer/userinfo/";
$dirUserDelete = $rootDir."DataServer/deleted/";

// NORMAL USER
// CREATE / RECOVER / DELTETE / EDIT SKILL,STATE POINTS / CREATE, CHANGE PW ACCOUNT / RECOVER HAIR


//INFORMAÇÕES DESCRITIVAS
$ServerName  = "Reloaded Priston Tale";
$urlmanager  = "http://management.reloadedpt.net/manager/cadastro.php";
$urllogin    = "http://management.reloadedpt.net/manager/login.php";
$urlrecConta = "http://management.reloadedpt.net/manager/enviaSenha.php";
$urlserver   = "http://management.reloadedpt.net";
$urltagsClan = "http://management.reloadedpt.net/ClanContent/";
$dirCContent = "C:/inetpub/wwwroot/ClanContent/";
$paramento   = "?ws";
$levelstart  = 1;

// CHANGE SQLEXPRESS USER AND PASSWORD
$host = "RELOAD";
$user = 'sa';
$pass = '1k2R31GhJ2';

// CHANGE XXX TO YOUR COMPUTER NAME
$connection_string = 'DRIVER={SQL Server};SERVER='.$host.'\SQLEXPRESS;DATABASE=accountdb';
$conexao = odbc_connect($connection_string, $user, $pass);

?>
