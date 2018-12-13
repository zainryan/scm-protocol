add_library(cmd_splitter "")

target_sources(cmd_splitter
    PRIVATE
        cmd_splitter.cpp
    )

target_include_directories(cmd_splitter
    PUBLIC
	../../../inc
	../../../third_party/hls/inc
        ../../../third_party/staccel/inc
    )
