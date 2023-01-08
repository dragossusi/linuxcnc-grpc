filegroup(
    name = "simple_srcs",
    srcs = glob(["**"]),
    visibility = ["//visibility:public"],
)

cc_library(
    name = "headers",
    hdrs = glob([
        "include/*.h",
        "include/*.hh",
    ]),
    copts = [
        "-I/home/dragos/Apps/linuxcnc/include)",
        "-I/home/dragos/Apps/linuxcnc/src)",
    ],
    visibility = ["//visibility:public"],
)

cc_import(
    name = "nml",
    hdrs = glob([
        "include/*.h",
        "include/*.hh",
        "src/*.h",
        "src/*.hh",
    ]),
    shared_library = "lib/libnml.so",
    visibility = ["//visibility:public"],
)
