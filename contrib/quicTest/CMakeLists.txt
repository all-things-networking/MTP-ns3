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
    LIBNAME quicTest
    SOURCE_FILES MTQUIC.cc
                 QUICRXApp.cc
                 QUICTXNet.cc
                 QUICRXNet.cc
                 QUICDispatcher.cc
                 QUICEventProcs.cc
                 QUICHeaders.cc
    HEADER_FILES MTQUIC.h
                 QUICRXApp.h
                 QUICTXNet.h
                 QUICRXNet.h
                 QUICEvents.h
                 QUICEventProcs.h
                 QUICDispatcher.h
                 QUICContext.h
                 QUICStructs.h
                 QUICContext.h

                
    LIBRARIES_TO_LINK ${libinternet}
    TEST_SOURCES test/modular-transport-test-suite.cc
                 ${examples_as_tests_sources}
)

