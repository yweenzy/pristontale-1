#ifndef	_NET_TYPE_HEADER_
#define _NET_TYPE_HEADER_

//New items authentication code applies
#define _NEW_ITEM_FORMCODE_

//The new complex cryptographic authentication code applies to items (Chinese, English application server)
#define _NEW_ITEM_FORMCODE2
//More new hybrid encryption authentication code applies to the item (Thai / Japanese)
#define _NEW_ITEM_FORMCODE3

//#define _SERVER_MODE_OLD

#define _WINMODE_DEBUG

#ifdef _WINMODE_DEBUG
#define _DEBUG_SOCKET
#endif

//DRZ Defines
//#define _USE_DYNAMIC_ENCODE		//set this flag for enable the original dynamic encode methods. (dont work yet)

#define _USE_NEW_MSSQL_CLASS		//set this flag for use the new MSSQL-CLASS

#endif
