#ifndef AutocompleteTests_Included
#define AutocompleteTests_Included

#include "TestDriver.h"

/* List of all the tests to run. */
extern TestGroup gAutocompleteTests;

/* This logic is necessary to get the testing harness to properly pick up all the tests
 * from your file.
 */
#ifdef GROUP
#undef GROUP
#endif

#define GROUP gAutocompleteTests

#endif
