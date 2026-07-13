file(GLOB_RECURSE UTILITIES_SOURCES CONFIGURE_DEPENDS *.cpp)

target_sources(Engine PRIVATE
        ${UTILITIES_SOURCES}
)

target_sources(UnitTests PRIVATE
        ${UTILITIES_SOURCES}
)