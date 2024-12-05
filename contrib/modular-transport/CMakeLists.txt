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
                helper/mt-list.cc
                helper/mt-queue.cc
                model/mt-context.cc
                model/mt-dispatcher.cc
                model/mt-txnet.cc
                model/mt-txapp.cc
    HEADER_FILES model/modular-transport.h
                helper/mtp-types.h
                helper/mt-flow-id.h
                helper/mt-header.h
                helper/mt-flow-map.h
                helper/mt-addr.h
                helper/mt-app.h
                helper/mt-list.h
                helper/mt-queue.h
                model/mt-event.h
                model/mt-scheduler.h
                model/mt-dispatcher.h
                model/mt-eventprocessor.h
                model/mt-context.h
                model/mt-rxapp.h
                model/mt-txapp.h
                model/mt-txnet.h
                model/mt-rxnet.h
                
    LIBRARIES_TO_LINK ${libinternet}
    TEST_SOURCES test/modular-transport-test-suite.cc
                 ${examples_as_tests_sources}
)

