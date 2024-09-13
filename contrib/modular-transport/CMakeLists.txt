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
    LIBNAME modular-transport
    SOURCE_FILES model/modular-transport.cc
                model/mt-event.cc
                model/mt-scheduler.cc
                helper/mt-header.cc
    HEADER_FILES model/modular-transport.h
                helper/mtp-types.h
                model/mt-rxapp.h
                model/mt-event.h
                model/mt-scheduler.h
                model/mt-dispatcher.h
                model/mt-eventprocessor.h
                model/mt-context.h
                helper/mt-header.h
    LIBRARIES_TO_LINK ${libinternet}
    TEST_SOURCES test/modular-transport-test-suite.cc
                 ${examples_as_tests_sources}
)

