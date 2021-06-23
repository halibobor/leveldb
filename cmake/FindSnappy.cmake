# - Find Snappy
# Find the snappy compression library and includes
#
#  SNAPPY_INCLUDE_DIRS - where to find snappy.h, etc.
#  SNAPPY_LIBRARIES   - List of libraries when using snappy.
#  SNAPPY_FOUND       - True if snappy found.

FIND_PATH(SNAPPY_INCLUDE_DIRS snappy.h PATHS
  /usr/include
  /opt/local/include
  /usr/local/include
  /tmp/usr/local/include
)

FIND_LIBRARY(SNAPPY_LIBRARIES NAMES snappy PATHS
  /usr/local/lib
  /opt/local/lib
  /usr/lib
  /tmp/usr/local/lib
)

# handle the QUIETLY and REQUIRED arguments and set SNAPPY_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Snappy
                                  REQUIRED_VARS SNAPPY_LIBRARIES SNAPPY_INCLUDE_DIRS
                                  VERSION_VAR SNAPPY_VERSION_STRING)
MARK_AS_ADVANCED(SNAPPY_INCLUDE_DIRS)