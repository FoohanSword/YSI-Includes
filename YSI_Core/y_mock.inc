#if defined _INC_y_mock
	#endinput
#endif
#define _INC_y_mock

#include "y_utils"
#include "y_als"
#include "..\YSI_Coding\y_hooks"

#include "y_mock/impl"

#if defined YSI_TESTS
	#pragma dynamic 20000
	#include "..\YSI_Core\y_testing"
	#include "y_mock/tests"
#endif