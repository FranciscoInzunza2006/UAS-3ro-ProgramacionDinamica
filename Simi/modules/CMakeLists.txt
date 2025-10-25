
add_library(print+ print+.cpp)
add_library(input_handler input_handler.cpp)

add_library(menu menu.cpp)
target_link_libraries(menu
        print+
        input_handler
)

add_library(patient patient.cpp)
target_link_libraries(patient input_handler)

add_library(clinic clinic.cpp)
target_link_libraries(clinic
        patient
        menu
)


