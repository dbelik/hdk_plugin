#pragma once

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

namespace HDK_Sample
{
    template <VEX_Precision PREC>
    static void compute_Evaluate(int argc, void *argv[], void *data)
    {
        VEXfloat<PREC> *result = (VEXfloat<PREC> *)argv[0];
        *result = .5L;
    }
}