cmake_minimum_required(VERSION 3.29)
project(CrowExampleProject)

set(CMAKE_TOOLCHAIN_FILE "/home/manufacture/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/application/contact
        ${CMAKE_CURRENT_SOURCE_DIR}/application/product
        ${CMAKE_CURRENT_SOURCE_DIR}/domain/contact
        ${CMAKE_CURRENT_SOURCE_DIR}/domain/contact_group
        ${CMAKE_CURRENT_SOURCE_DIR}/domain/product
        ${CMAKE_SOURCE_DIR}/domain
        ${CMAKE_SOURCE_DIR}/application

)

add_executable(crow_example
        main.cpp
        application/contact/contact-service.hpp
        application/product/product-service.hpp

        domain/contact/contact.hpp
        domain/contact/contact-service.hpp
        domain/contact/contact-factory.hpp
        domain/contact/contact-repository.hpp

        domain/contact_group/contactgroup-service.hpp
        domain/contact_group/contactgroup-repository.hpp
        domain/contact_group/contactgroup-factory.hpp
        domain/contact_group/contact-group.hpp

        domain/product/product.hpp
        domain/product/product-factory.hpp
        domain/product/product-repository.hpp
        domain/product/product-service.hpp
)

find_package(Crow CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(libpqxx CONFIG REQUIRED)

target_link_libraries(crow_example PRIVATE
        Crow::Crow
        libpqxx::pqxx
        nlohmann_json::nlohmann_json
)
