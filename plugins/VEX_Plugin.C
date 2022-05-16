#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <UT/UT_DSOVersion.h>
#include <UT/UT_Thread.h>
#include <UT/UT_DoubleLock.h>
#include <VEX/VEX_VexOp.h>
#include <UT/UT_HDKVersion.h>

#include "utilities/utilities.h"

using namespace UT::Literal;
using namespace HDK_Sample;

void newVEXOp(void *)
{
	new VEX_VexOp(
		"compute_plugin@&F"_sh,
		compute_Evaluate<VEX_32>,
		compute_Evaluate<VEX_64>,
		VEX_ALL_CONTEXT,
		nullptr, nullptr,
		nullptr, nullptr);
}
