// header file that we are implementing here.
#include "AiksaurusGTK_utils.h"

// cstring needed for strlen.
#include <cstring>

// new needed for nothrow.
#include <new>


bool AiksaurusGTK_strEquals(const char* lhs, const char* rhs)
{
	if ((!lhs) || (!rhs))
		return (lhs == rhs);
	
	register int i = 0;
	while(lhs[i] != '\0')
	{
		if (rhs[i] != lhs[i])
			return false;
		
		++i;
	}

	return (rhs[i] == '\0');
}


char* AiksaurusGTK_strCopy(const char* str)
{	
	char* ret;
	
	if (!str)
	{
		ret = new(nothrow) char[1];
		
		if (!ret)
			return ret;
		
		ret[0] = '\0';
		
	}

	else
	{
		const int len = strlen(str);

		ret = new(nothrow) char[len+1];
	
		if (!ret)
			return ret;
		
		for(register int i = 0;i < len;++i)
		{
			ret[i] = str[i];
		}

		ret[len] = '\0';
	}

	return ret;
}

