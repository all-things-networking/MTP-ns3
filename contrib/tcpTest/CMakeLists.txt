check_include_file_cxx(stdint.h HAVE_STDINT_H)
if(HAVE_STDINT_H)
    add_definitions(-DHAVE_STDINT_H)
endif()

set(examples_as_tests_sources)
if(${ENABLE_EXAMPLES})
    set(examples_as_tests_sources
        #test/modular-transport-examples-test-suite.cc
        )
endif()

build_lib(
    LIBNAME tcpTest
    SOURCE_FILES MTTCP.cc
                 TCPRXApp.cc
                 TCPTXNet.cc
                 TCPRXNet.cc
                 TCPDispatcher.cc
                 TCPEventProcs.cc
    HEADER_FILES MTTCP.h
                 TCPRXApp.h
                 TCPTXNet.h
                 TCPRXNet.h
                 TCPEvents.h
                 TCPEventProcs.h
                 TCPDispatcher.h
                 TCPContext.h
                 TCPStructs.h
                 TCPContext.h

                
    LIBRARIES_TO_LINK ${libinternet}
    TEST_SOURCES test/modular-transport-test-suite.cc
                 ${examples_as_tests_sources}
)

