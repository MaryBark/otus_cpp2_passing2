# версия Cmake, чтобы потом понять, почему не собирается
cmake_minimum_required(VERSION 3.10)

# подготовка версии сборки DEB-пакета
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

# версия проекта
project(otusCPP2_passing2 VERSION ${PROJECT_VESRION})

# Подключаем библиотеки и пишем какие копмоненты нужны
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
find_package(GTest COMPONENTS unit_test_framework REQUIRED)

# создание конфигурационного файла
configure_file(version.h.in version.h)

# Добавляем обычные исполняемые файлы, библиотеку и опять фалы
add_executable(IP_filtr_client main.cpp)
add_library(otusCPP2_passing2 ip_filtr.h ip_filtr.cpp tuplesIP.h tuplesIP.cpp)
add_executable(test_version test_version.cpp  #[[Gtest_version.cpp]])
add_executable(test_versionGtest Gtest_version.cpp)

# устанавливаем свойства для этих объектов, чтобы все фалы были только в 17-м стандарте
set_target_properties(IP_filtr_client otusCPP2_passing2 test_version PROPERTIES
 CXX_STANDARD 17
 CXX_STANDARD_REQUIRED ON
)

# подключаем директорию
target_include_directories(otusCPP2_passing2
    PRIVATE "${CMAKE_BINARY_DIR}"
)

# Устанавливаем свойства для тестов с помощью Boost
set_target_properties(test_version PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

# Линкуем объект в папке
target_link_libraries(IP_filtr_client PRIVATE
 otusCPP2_passing2
)

# линкуем тест в бустом
target_link_libraries(test_version
    ${Boost_LIBRARIES}
    otusCPP2_passing2
)

########################
#target_include_directories(
#test_version PRIVATE
#    ${GTEST_INCLUDE_DIRS}
#    ${CMAKE_THREAD_LIBS_INIT}
#)

#target_link_libraries(
# test_version PRIVATE
#    ${GTEST_BOTH_LIBRARIES}
#    otusCPP2_passing2
#)

#######################



# Выбираем компиляции таргетов в зависимости от компиллятора?????
if (MSVC)
    target_compile_options(IP_filtr_client PRIVATE
 /W4
    )
    target_compile_options(otusCPP2_passing2 PRIVATE
 /W4
    )
    target_compile_options(test_version PRIVATE
 /W4
    )
else ()
    target_compile_options(IP_filtr_client PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(otusCPP2_passing2 PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_version PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

# сборка DEB-пакета
install(TARGETS IP_filtr_client RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT Alttaira@yandex.ru)

include(CPack)

enable_testing()

add_test(test_version test_version)
