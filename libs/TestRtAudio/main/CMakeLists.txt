set(Main_SRCS
    main.cpp
)

add_executable(main
    ${Main_SRCS}
)


target_link_libraries(main TestRtAudioLib )


install(TARGETS main DESTINATION bin)