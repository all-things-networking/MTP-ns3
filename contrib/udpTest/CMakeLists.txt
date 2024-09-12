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
    LIBNAME udpTest
    SOURCE_FILES MTUDP.cc
                 UDPRXApp.cc
                 UDPDispatcher.cc
    HEADER_FILES MTUDP.h
                 UDPRXApp.h
                 UDPEvents.h
                 UDPEventProcs.h
                 UDPDispatcher.h
                 UDPContext.h
                 UDPStructs.h

                
    LIBRARIES_TO_LINK ${libinternet}
    TEST_SOURCES test/modular-transport-test-suite.cc
                 ${examples_as_tests_sources}
)

