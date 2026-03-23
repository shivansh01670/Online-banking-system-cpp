cmake_minimum_required(VERSION 3.10)

project(OnlineBankingSystem cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add all source files
set(SOURCES
    main.cpp
    User.cpp
    Account.cpp
    Transaction.cpp
    BankService.cpp
)

add_executable(BankApp ${SOURCES})
