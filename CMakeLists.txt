cmake_minimum_required(VERSION 3.29)
project(CrowExampleProject)

# Vcpkg toolchain dosyasını ayarlayın
set(CMAKE_TOOLCHAIN_FILE "/home/fatmanur/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Yürütülebilir dosya hedefi oluşturun
add_executable(crow_example
        main.cpp
        application/contact-service.hpp
        ############## CONTACT-GROUP İÇİN #############
        domain/contact_group/contactgroup-service.hpp
        domain/contact_group/contact-group.hpp
        domain/contact_group/contactgroup-factory.hpp
        domain/contact_group/contactgroup-repository.hpp


        domain/contact/contact-service.hpp
        domain/contact/contact.hpp
        domain/contact/contact-factory.hpp
        domain/contact/contact-repository.hpp
)

# Crow ve diğer kütüphaneleri bulun
find_package(Crow CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(libpqxx CONFIG REQUIRED)

# Hedefe kütüphaneleri bağlayın
target_link_libraries(crow_example PRIVATE
        Crow::Crow
        libpqxx::pqxx
        nlohmann_json::nlohmann_json
)
