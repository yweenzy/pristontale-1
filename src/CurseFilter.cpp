#include <windows.h>
#include <string.h>
#include <stdio.h>

#include "CurseFilter.h"

#define MAX_CURSE_STRING	32768
#define HUGE_NUMBER		MAX_CURSE_STRING

static char curse_string[MAX_CURSE_STRING];
static bool bInit = false;
static char curse_stringID[MAX_CURSE_STRING];
static bool bInitID = false;

static int chksum;
static int chksumID;

//static inline void filterChar(const char *src, char *dst, const char *chars)
static void filterChar(const char *src, char *dst, const char *chars)
{
    char *srcp = (char *) src;
    char *dstp = dst;

    while (*srcp) {
	if (strchr(chars, *srcp) == NULL) {
	    *dstp = *srcp;   dstp += 1;
	} else {
	    int msb, lsb;
	    msb = *(unsigned char *)(srcp-1);
	    lsb = *(unsigned char *)srcp;
	    if (srcp > src && (
		(msb == 0x82 && lsb > 0x9e && lsb < 0xf2)	// hirakana
		|| (msb == 0x83 && lsb > 0x3f && lsb < 0x97)	// katakana
	       	|| (msb >= 0x88 && msb <= 0x9f && msb != 0x7f	// kanji 1 group
		    && lsb > 0x3f && lsb < 0xfd)
		|| (msb >= 0xe0 && msb <= 0xfc && msb != 0x7f	// kanji 2 group
		    && lsb > 0x3f && lsb < 0xfd))) {
		*dstp = *srcp;   dstp += 1;
	    }
	}
	srcp += 1;
    }
    *dstp = 0;
}

//static inline char *getField(const char *buf, int delim, char *field)
static char *getField(const char *buf, int delim, char *field)
{
    unsigned char *src = (unsigned char *)buf;
    while ((int)*src == delim && *src != 0) src++;
    while ((int)*src != delim && *src != 0) *field ++ = *src ++;

    *field = '\0';
    return (char *)src;
}

int LoadCurses(const char *filename)
{
	//filterChar(str, string, "\t _-.^");
    static char comment_chars[] = { "\n" };
    char buf[128];
    char *ptr = curse_string;
    FILE *file;

	char passcode[128];

    if (bInit) return FALSE;


    if (file = fopen(filename, "r"), !file) {
	fprintf(stderr, "! can't open [%s]\n", filename);
	return FALSE;
    }

    while (fgets(buf, sizeof(buf), file)) {
	if (strchr(comment_chars, buf[0])) continue;
	
		ZeroMemory(passcode,128);
		PassCode(buf, passcode, strlen(buf));
    	ptr += sprintf(ptr, passcode);
	
		//ptr += sprintf(ptr, buf);

    	if (ptr - curse_string >= MAX_CURSE_STRING) {
    	    fprintf(stderr, "! %s is too long, pass.\n", filename);
    	    curse_string[MAX_CURSE_STRING - 1] = 0;
    	    break;
    	}
    }
    fclose(file);

    fprintf(stderr, "* parsing [%s]. %d bytes read\n", filename, ptr - curse_string);
    return chksum;
}

int LoadCursesID(const char *filename)
{
	//filterChar(str, string, "\t _-.^");
    static char comment_chars[] = { "\n" };
    char buf[128];
    char *ptr = curse_stringID;
    FILE *file;

	char passcode[128];

    if (bInitID) return FALSE;


    if (file = fopen(filename, "r"), !file) {
	fprintf(stderr, "! can't open [%s]\n", filename);
	return FALSE;
    }

    while (fgets(buf, sizeof(buf), file)) {
	if (strchr(comment_chars, buf[0])) continue;
	
		ZeroMemory(passcode,128);
		PassCodeID(buf, passcode, strlen(buf));
    	ptr += sprintf(ptr, passcode);
	
		//ptr += sprintf(ptr, buf);

    	if (ptr - curse_stringID >= MAX_CURSE_STRING) {
    	    fprintf(stderr, "! %s is too long, pass.\n", filename);
    	    curse_stringID[MAX_CURSE_STRING - 1] = 0;
    	    break;
    	}
    }
    fclose(file);

    fprintf(stderr, "* parsing [%s]. %d bytes read\n", filename, ptr - curse_stringID);
    return chksumID;
}


int LoadCursesDebug(const char *filename)
{
	//filterChar(str, string, "\t _-.^");
    static char comment_chars[] = { "\n" };
    char buf[128];
    char *ptr = curse_string;
    FILE *file;

    if (bInit) return FALSE;


    if (file = fopen(filename, "r"), !file) {
	fprintf(stderr, "! can't open [%s]\n", filename);
	return FALSE;
    }

    while (fgets(buf, sizeof(buf), file)) {
	if (strchr(comment_chars, buf[0])) continue;
	
		ptr += sprintf(ptr, buf);

    	if (ptr - curse_string >= MAX_CURSE_STRING) {
    	    fprintf(stderr, "! %s is too long, pass.\n", filename);
    	    curse_string[MAX_CURSE_STRING - 1] = 0;
    	    break;
    	}
    }
    fclose(file);

    fprintf(stderr, "* parsing [%s]. %d bytes read\n", filename, ptr - curse_string);
    return chksum;
}

int LoadCursesDebugID(const char *filename)
{
	//filterChar(str, string, "\t _-.^");
    static char comment_chars[] = { "\n" };
    char buf[128];
    char *ptr = curse_stringID;
    FILE *file;

    if (bInitID) return FALSE;


    if (file = fopen(filename, "r"), !file) {
	fprintf(stderr, "! can't open [%s]\n", filename);
	return FALSE;
    }

    while (fgets(buf, sizeof(buf), file)) {
	if (strchr(comment_chars, buf[0])) continue;
	
		ptr += sprintf(ptr, buf);

    	if (ptr - curse_stringID >= MAX_CURSE_STRING) {
    	    fprintf(stderr, "! %s is too long, pass.\n", filename);
    	    curse_stringID[MAX_CURSE_STRING - 1] = 0;
    	    break;
    	}
    }
    fclose(file);

    fprintf(stderr, "* parsing [%s]. %d bytes read\n", filename, ptr - curse_stringID);
    return chksumID;
}

bool IsCurse(const char * str)
{
    char string[HUGE_NUMBER], line[HUGE_NUMBER], word[HUGE_NUMBER];
    char *ptr = curse_string;
    const char *sub, *subs, *subw;

    if (!str) return false;

    // filter characters to keep users from
    // speaking curses mixed with white spaces 
    // or punctuaion mark

	filterChar(str, string, " ");


    // optimized for multibyte code set.

    while (ptr = getField(ptr, '\n', line), line[0]) {
	getField(line, '\t', word);	
	sub = str;
	//sub = string;
	while (*sub && *(sub + 1)) {
	    subs = sub;	// current comparison pointer in string
	    subw = word;	// current comparison pointer in word
	    while (*subs && (*subs == *subw)) {
		subs++; subw++;
		if (*subw == 0) {
		    return true;		// reach to null, curse
		}
	    }
	    sub += *sub < 0 ? 2 : 1;
	}
    }

    return false;
}

bool IsCurseID(const char * str)
{
    char string[HUGE_NUMBER], line[HUGE_NUMBER], word[HUGE_NUMBER];
    char *ptr = curse_stringID;
    const char *sub, *subs, *subw;

    if (!str) return false;

    // filter characters to keep users from
    // speaking curses mixed with white spaces 
    // or punctuaion mark

	filterChar(str, string, " ");


    // optimized for multibyte code set.

    while (ptr = getField(ptr, '\n', line), line[0]) {
	getField(line, '\t', word);	
	sub = str;
	//sub = string;
	while (*sub && *(sub + 1)) {
	    subs = sub;	// current comparison pointer in string
	    subw = word;	// current comparison pointer in word
	    while (*subs && (*subs == *subw)) {
		subs++; subw++;
		if (*subw == 0) {
		    return true;		// reach to null, curse
		}
	    }
	    sub += *sub < 0 ? 2 : 1;
	}
    }
    return false;
}

char *ConvertString(char * str, int max_len)
{
    char result[MAX_CURSE_STRING], string[MAX_CURSE_STRING];
    char line[128], curse[128], replace[128];
    char *ptr = curse_string, *lptr, *cptr;

    if (!str) return NULL;

    if (!max_len || max_len >= sizeof(result)) return str;

    // skip converting, if no curse is found.
    // in fact, 'isCurse' and 'convert' are redundant.
    // but it can be ignored and more efficient 
    // because users speak a normal sentence 
    // much more than a curse

    if (!IsCurse(str)) return str;


    // filter characters to keep users from
    // speaking curses mixed with white spaces 
    // or punctuaion mark
	filterChar(str, string, " ");//"\t _-.^");

	while (ptr = getField(ptr, '\n', line), line[0]) {

		lptr = line;
		lptr = getField(lptr, '\t', curse);		// get the first field	
		lptr = getField(lptr, '\t', replace);	// get the second field
		cptr = string;
		strcpy(result, string);

		while (cptr = strstr(string, curse), cptr) {
			// if there is no matching replacement of curse word
			if (!replace[0]) {
				str = 0;
			return str;
			}

			if ((int)(max_len) < 
				(int)((cptr - string) + strlen(replace) + strlen(cptr + strlen(curse)))) {
					// string too long, remove the curses that linger around
					strncpy(result, string, cptr - string);
					strcpy(result + (cptr - string), cptr + strlen(curse));
				} else {               	    
				strncpy(result, string, cptr - string);
				strcpy(result + (cptr - string), replace);
				strcpy(result + (cptr - string + strlen(replace)), cptr + strlen(curse));
				}

			// refresh intermediate result
			strcpy(string, result);
		}
	}

    result[max_len] = 0;		// prevent overflow
    strcpy(str, result);

    return str;
}

char *ConvertStringTHAI(char * str, int max_len)
{
    char result[MAX_CURSE_STRING], string[MAX_CURSE_STRING];
    char line[128], curse[128], replace[128];
    char *ptr = curse_string, *lptr, *cptr;
	//char *replace="*****";

    if (!str) return NULL;

    if (!max_len || max_len >= sizeof(result)) return str;

    // skip converting, if no curse is found.
    // in fact, 'isCurse' and 'convert' are redundant.
    // but it can be ignored and more efficient 
    // because users speak a normal sentence 
    // much more than a curse

   // if (!IsCurse(str)) return str;
	IsCurse(str);


    // filter characters to keep users from
    // speaking curses mixed with white spaces 
    // or punctuaion mark
	filterChar(str, string, "");//"\t _-.^");

	while (ptr = getField(ptr, '\n', line), line[0]) {

		lptr = line;
		lptr = getField(lptr, '\t', curse);		// get the first field	
		cptr = string;
		strcpy(result, string);

		while (cptr = strstr(string, curse), cptr) {
			// if there is no matching replacement of curse word
			ZeroMemory(replace, 128);
			for(int i=0; i<(int)strlen(string); i++)
			{
				strcat(replace,"*");
			}
			//wsprintf(replace,"***");
			if (!replace[0]) {
				str = 0;
			return str;
			}


			if ((int)(max_len) < 
				(int)((cptr - string) + strlen(replace) + strlen(cptr + strlen(curse)))) {
					// string too long, remove the curses that linger around
					strncpy(result, string, cptr - string);
					strcpy(result + (cptr - string), cptr + strlen(curse));
				} else {               	    
				strncpy(result, string, cptr - string);
				strcpy(result + (cptr - string), replace);
				strcpy(result + (cptr - string + strlen(replace)), cptr + strlen(curse));
				}

			// refresh intermediate result
			strcpy(string, result);
		}
	}

    result[max_len] = 0;		// prevent overflow
    strcpy(str, result);

    return str;
}

char *ConvertStringTaiwanChat(char * str, int max_len)
{
    return ConvertStringTHAI(str, max_len);
}

bool BadTaiwanID(const char * str)
{
	return IsCurseID(str);		
}


void PassCode(char PassBefore[], char PassAfter[], int number)
//void PassCode(char *PassBefore, char *PassAfter, int number)
{
	int j;

	for ( j=0 ; j < number ; j++ )
	{
		chksum += PassBefore[j];
		PassAfter[j] = PassBefore[j]^0x1;
	}
}

void PassCodeID(char PassBefore[], char PassAfter[], int number)
//void PassCode(char *PassBefore, char *PassAfter, int number)
{
	int j;

	for ( j=0 ; j < number ; j++ )
	{
		chksumID += PassBefore[j];
		PassAfter[j] = PassBefore[j]^0x1;
	}
}

int ChatChkSum()
{
	return chksum;
}

int ChatChkSumID()
{
	return chksumID;
}
