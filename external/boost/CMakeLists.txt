if(NOT EXISTS "$ENV{BOOST_ROOT}")
  message(FATAL_ERROR "Could not find BOOST_ROOT environment variable")
endif()

set(
  BOOST_ROOT
  $ENV{BOOST_ROOT}
)

set(
  BOOST_VERSION
  1.72.0
)

set(
  BOOST_LIBRARYDIR
  "${BOOST_ROOT}/stage/lib"
)

set(
  Boost_NO_SYSTEM_PATHS
  ON
)

find_package(
  Boost
  ${BOOST_VERSION}
  REQUIRED
  COMPONENTS
    program_options
    unit_test_framework
)

if(Boost_FOUND)
  set_target_properties(
    Boost::boost
    Boost::unit_test_framework
    Boost::program_options
    PROPERTIES
    IMPORTED_GLOBAL
    true
  )
endif()
