#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <VEX/VEX_VexOp.h>

namespace HDK_Sample
{
    template <VEX_Precision PREC>
    static void myprint_Evaluate(int argc, VEX_VexOpArg argv[], void *data)
    {
        printf("%d args:\n", argc);
        for (int i = 0; i < argc; i++)
        {
            if (argv[i].myArray)
                continue;
            switch (argv[i].myType)
            {
            case VEX_TYPE_INTEGER:
                std::cout << "  int " << *(const VEXint<PREC> *)argv[i].myArg << '\n';
                break;
            case VEX_TYPE_FLOAT:
                std::cout << "  float " << *(const VEXfloat<PREC> *)argv[i].myArg << '\n';
                break;
            case VEX_TYPE_STRING:
                std::cout << "  string " << *(const char *)argv[i].myArg << '\n';
                break;
            default:
                break;
            }
        }
    }
}