#include "TestReporterStdout.h"
#include <cstdio>

#include "TestDetails.h"

// cstdio doesn't pull in namespace std on VC6, so we do it here.
#if defined(UNITTEST_WIN32) && (_MSC_VER == 1200)
	namespace std {}
#endif

#include <set>
#include <string>
std::set<std::string> failed_tests;

namespace UnitTest {

void TestReporterStdout::ReportFailure(TestDetails const& details, char const* failure)
{
    using namespace std;
#if defined(__APPLE__) || defined(__GNUG__)
    char const* const errorFormat = "%s:%d:%d: error: Failure in %s: %s\n";
    fprintf(stderr, errorFormat, details.filename, details.lineNumber, 1, details.testName, failure);
#else
    char const* const errorFormat = "%s(%d): error: Failure in %s: %s\n";
    fprintf(stderr, errorFormat, details.filename, details.lineNumber, details.testName, failure);
#endif
    failed_tests.insert( details.testName );
}

void TestReporterStdout::ReportTestStart(TestDetails const& test)
{
    printf("* Start  %s:%s.\n", test.suiteName, test.testName);
}

void TestReporterStdout::ReportTestFinish(TestDetails const& test, float secondsElapsed)
{
    printf("  Finish %s:%s in %.2f seconds.\n", test.suiteName, test.testName, secondsElapsed);
}

void TestReporterStdout::ReportSummary(int const totalTestCount, int const failedTestCount,
                                       int const failureCount, float const secondsElapsed)
{
	using namespace std;
    printf("Total test time: %.2f seconds.\n", secondsElapsed);

    if (failureCount > 0)
    {
        printf("FAILURE: %d out of %d tests failed (%d failures):\n", failedTestCount, totalTestCount, failureCount);
        for (auto & tname : failed_tests)
            printf("- %s\n", tname.c_str());
    }
    else
        printf("Success: %d tests passed.\n", totalTestCount);
}

}
