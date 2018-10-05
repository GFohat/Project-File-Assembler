//"ImportADO.h"

//#include "ImportADO.h"
#pragma once

//warning C4146: unary minus operator applied to unsigned type, result still unsigned
//    adCreateStructDoc = -2147483648,
#pragma warning( disable : 4146)

#import "C:\\Program Files\\Common Files\\System\\ado\\msado15.dll" named_guids rename("EOF", "EndOfFile")

#pragma warning( default : 4146)

/*
msado15.dll"
        rename("EOF", "EndOfFile")
*/