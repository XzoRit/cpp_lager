set(BOOST_VERSION 1.70.0)

set(BOOST_ROOT $ENV{BOOST_ROOT})
set(BOOST_LIBRARYDIR "${BOOST_ROOT}/stage/lib")
set(Boost_NO_SYSTEM_PATHS ON)

find_package(
  Boost
  ${BOOST_VERSION}
  EXACT
  REQUIRED
  COMPONENTS program_options unit_test_framework
)

if(Boost_FOUND)
  set_target_properties(Boost::boost Boost::unit_test_framework
                        Boost::program_options PROPERTIES IMPORTED_GLOBAL true)
endif()
