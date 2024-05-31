
add_executable(
    finger
    finger.c
    lprint.c
    net.c
    sprint.c
    util.c
    display.c
)
install(
    TARGETS finger
    DESTINATION ${BIN_DIR}
)

install(
    FILES finger.1
    DESTINATION ${MAN_DIR}/man1/
)
