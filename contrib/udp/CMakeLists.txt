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
    LIBNAME udp
    SOURCE_FILES model/udp-dispatcher.cc
                model/udp-eventprocessor.cc
                model/udp-mt.cc
    HEADER_FILES model/udp-context.h
                model/udp-dispatcher.h
                model/udp-event.h
                model/udp-eventprocessor.h
                model/udp-header.h
                model/udp-mt.h
                model/udp-rxapp.h
                model/udp-rxnet.h
                model/udp-txapp.h
                model/udp-txnet.h
                
    LIBRARIES_TO_LINK ${libinternet}
    TEST_SOURCES test/modular-transport-test-suite.cc
                 ${examples_as_tests_sources}
)

