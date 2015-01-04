#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

// Entry point for tests which initialises and calls catch
int main(int argc, char** argv)
{
    int result;

    // Pause if this is a windows build and COMENT_TESTS_PAUSE_AT_EXIT is defined
    // TODO: provide an implementation for non-windows platforms?
#if defined(_MSC_VER) && defined(COMENT_TESTS_PAUSE_AT_EXIT)
    atexit([]() { system("pause"); });
#endif

    // Initialise catch session
    Catch::Session session;

    // Set any catch configuration
    Catch::ConfigData& configData = session.configData();

    // Pass command line arguments
    result = session.applyCommandLine(argc, argv);
    if (result != 0)
        return result;

    // Run catch
    result = session.run();

    // Return result
    return result;
}