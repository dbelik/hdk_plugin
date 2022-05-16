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

using namespace UT::Literal;

namespace HDK_Sample {

#if !defined(WIN32)
template <VEX_Precision PREC>
static void
drand_Evaluate(int, void *argv[], void *)
{
    VEXfloat<PREC>	*result = (VEXfloat<PREC> *)argv[0];
    const VEXint<PREC>	*seed = (const VEXint<PREC> *)argv[1];

    SYSsrand48(*seed);
    *result = SYSdrand48();
}
#endif

template <VEX_Precision PREC>
static void
time_Evaluate(int, void *argv[], void *)
{
    VEXint<PREC>		*result = (VEXint<PREC> *)argv[0];

    *result = time(0);
}

// Simple class to show shared storage.  A single gamma table is shared between
// all instances of the gamma() function.
template <VEX_Precision PREC>
class gamma_Table
{
public:
    gamma_Table()
    {
    }
    ~gamma_Table()
    {
    }

    VEXfloat<PREC>	evaluate(VEXfloat<PREC> v)	{ return 0; }
};

template <VEX_Precision PREC> static void *
gamma_Init()
{
    // Note that multiple threads may call init simultaneously, so this method
    // should be thread-safe.  If there's complicated initialization required,
    // you should likely lock around the initialization.
    // The method below uses C++11 static initialization.
    static gamma_Table<PREC>    theTable;
    return &theTable;
}

template <VEX_Precision PREC> static void
gamma_Cleanup(void *data)
{
    // Nothing required here.
}

template <VEX_Precision PREC>
static void
gamma_Evaluate(int, void *argv[], void *data)
{
    VEXfloat<PREC>		*result = (VEXfloat<PREC> *)argv[0];
    const VEXfloat<PREC>	*value = (const VEXfloat<PREC> *)argv[1];

    gamma_Table<VEX_32>	*table = (gamma_Table<VEX_32> *)data;
    *result = table->evaluate(*value);
}

template <VEX_Precision PREC>
static void
myprint_Evaluate(int argc, VEX_VexOpArg argv[], void *data)
{
    printf("%d args:\n", argc);
    for (int i = 0; i < argc; i++)
    {
	if (argv[i].myArray)
	    continue; // Doesn't support arrays
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

//
// Installation function
//
using namespace HDK_Sample;
void
newVEXOp(void *)
{
#if !defined(WIN32)
    //	Returns a random number based on the seed argument
    new VEX_VexOp("drand@&FI"_sh,	// Signature
		drand_Evaluate<VEX_32>,		// Evaluator 32
		drand_Evaluate<VEX_64>,		// Evaluator 64
		VEX_ALL_CONTEXT,	// Context mask
		nullptr,nullptr,	// init function 32,64
		nullptr,nullptr);		// cleanup function 32,64
#endif

    // Return the time() function.  This is non-deterministic, so the
    // optimization level has to be lowered.
    new VEX_VexOp("time@&I"_sh,		// Signature
		time_Evaluate<VEX_32>,		// Evaluator 32
		time_Evaluate<VEX_64>,		// Evaluator 64
		VEX_ALL_CONTEXT,	// Context mask
		nullptr,nullptr,	// init function 32, 64
		nullptr,nullptr,	// cleanup function 32, 64
		VEX_OPTIMIZE_1);	// Optimization level

    // Use the default optimization (better performance)
    new VEX_VexOp("gamma@&FF"_sh,	// Signature
		gamma_Evaluate<VEX_32>,		// Evaluator 32
		gamma_Evaluate<VEX_64>,		// Evaluator 64
		VEX_ALL_CONTEXT,	// Context mask
		gamma_Init<VEX_32>,	// init function 32
		gamma_Init<VEX_64>,	// init function 64
		gamma_Cleanup<VEX_32>,		// Cleanup function 32
		gamma_Cleanup<VEX_64>);		// Cleanup function 64

    // A variadic function to print integers and floats
    new VEX_VexOp("myprint@+"_sh,	// Signature
		myprint_Evaluate<VEX_32>,	// Evaluator 32
		myprint_Evaluate<VEX_64>,	// Evaluator 64
		VEX_ALL_CONTEXT,	// Context mask
		nullptr,nullptr,	// init function 32,64
		nullptr,nullptr,	// Cleanup function 32,64
		VEX_OPTIMIZE_0);	// Optimization level
}
