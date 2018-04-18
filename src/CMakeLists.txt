set(TARGET_NAME raytracing)

set(SRC
        vec3.h
        image.h
        color.h
)

add_executable(
        ${TARGET_NAME}
        main.cpp
        ${SRC}
)


target_link_libraries(${TARGET_NAME} ${LIBRARIES})