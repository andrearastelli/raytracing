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
    texture.h
    stb_image.h
    #stb_image_write.h
    aabb.h
    bvhnode.h
    perlin.h
    rect.h
    constantmedium.h
)

add_executable(
        ${TARGET_NAME}
        main.cpp
        ${SRC}
)


target_link_libraries(${TARGET_NAME} ${LIBRARIES})