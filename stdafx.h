// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <Windows.h>
#include <WtsApi32.h>
#include <Sddl.h>
#include <tchar.h>
#include <locale.h>
#include <conio.h>

#include <cstdio>
#include <cassert>

#include <iostream>
#include <sstream>
#include <iterator>
#include <exception>


#pragma comment(lib, "WtsApi32")

using _tstring = std::basic_string<_TCHAR>;
using _tstringstream = std::basic_stringstream<_TCHAR>;



