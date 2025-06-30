cmake_minimum_required(VERSION 3.16)

project(weatherapp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Network Charts LinguistTools Test)

set(TS_FILES weatherapp_ru_RU.ts)

set(PROJECT_SOURCES
  main.cpp
  ${TS_FILES}
)

# Главный исполняемый файл приложения (без тестов)
qt_add_executable(weatherapp
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

target_link_libraries(weatherapp PRIVATE
  Qt6::Widgets
  Qt6::Network
  Qt6::Charts
)

set_target_properties(weatherapp PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# ----------------------
# ОТДЕЛЬНО: тестовый исполняемый файл!
# ----------------------
add_executable(weatherapp_tests
    test_weather.cpp
    main.cpp
    main.h
)

target_link_libraries(weatherapp_tests PRIVATE
  Qt6::Widgets
  Qt6::Network
  Qt6::Charts
  Qt6::Test   # обязательно!
)

target_compile_definitions(weatherapp_tests PRIVATE BUILDING_TESTS)

# ----------------------
# install only main app, тесты не устанавливаем!
# ----------------------
include(GNUInstallDirs)
install(TARGETS weatherapp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_finalize_executable(weatherapp)
qt_finalize_executable(weatherapp_tests)

enable_testing()
add_test(NAME WeatherAppTests COMMAND weatherapp_tests)
