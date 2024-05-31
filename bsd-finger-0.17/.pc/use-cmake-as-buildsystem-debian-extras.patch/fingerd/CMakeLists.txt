
add_executable(
    in.fingerd
    fingerd.c
)
install(
    TARGETS in.fingerd
    DESTINATION ${SBIN_DIR}
)

install(
    FILES fingerd.8
    DESTINATION ${MAN_DIR}/man8/
    RENAME in.fingerd.8
)
