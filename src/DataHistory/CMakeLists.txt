add_library(DataHistory SHARED DataHistory.cpp DataTrace.cpp DataUtils.cpp)

target_include_directories(DataHistory PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

install(TARGETS DataHistory EXPORT ${CMAKE_PROJECT_NAME}Targets DESTINATION lib)
# install(FILES ${CMAKE_SOURCE_DIR}/include/DataHistory/DataHistory.h
#     ${CMAKE_SOURCE_DIR}/include/DataHistory/DataTrace.h
#     ${CMAKE_SOURCE_DIR}/include/DataHistory/DataUtils.h
#     DESTINATION include/DataHistory)
