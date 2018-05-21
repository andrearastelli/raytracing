set(TARGET_NAME raytracing)

set(SRC
        vec3.h
        image.h
        color.h
        ray.h
        hitable.h
        sphere.h
        hitablelist.h
        camera.h
        material.h
        parser.h
        movingsphere.h
        aabb.h
        bvhnode.h
        perlin.h
        texture.h
        )

add_executable(
        ${TARGET_NAME}
        main.cpp
        ${SRC}
)


target_link_libraries(${TARGET_NAME} ${LIBRARIES})