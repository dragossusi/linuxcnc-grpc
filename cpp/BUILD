cc_library(
    name = "emc_decode",
    srcs = [
        "emcDecode.cc",
    ],
    copts = [
        "-Iexternal/linuxcnc/include",
    ],
    deps = ["@linuxcnc"],
)

cc_library(
    name = "status_reader",
    srcs = ["status_reader.cc"],
    hdrs = ["status_reader.hh"],
    copts = [
        "-Iexternal/linuxcnc/include",
        "-Iexternal/linuxcnc/src",
    ],
    deps = ["@linuxcnc"],
)

cc_binary(
    name = "server",
    srcs = [
        "linuxcnc_server.cc",
    ],
    copts = [
        "-Iexternal/linuxcnc/include",
        "-Iexternal/linuxcnc/src",
    ],
    defines = ["BAZEL_BUILD"],
    deps = [
        ":status_reader",
        "//proto:linuxcnc_grpc",
        "@com_github_grpc_grpc//:grpc++",
    ],
)

cc_binary(
    name = "test_nml",
    srcs = ["TestNML.cc"],
    copts = [
        "-Iexternal/linuxcnc/include",
        "-Iexternal/linuxcnc/src",
    ],
    deps = ["@linuxcnc"],
)
