cc_library(
    name = "emc_decode",
    srcs = [
        "emcDecode.cc",
    ],
    deps = [
        #        "@linuxcnc//:nml",
        "@linuxcnc//:headers",
    ],
)

cc_binary(
    name = "server",
    srcs = [
        "linuxcnc_server.cc",
    ],
    defines = ["BAZEL_BUILD"],
    deps = [
        ":emc_decode",
        "//proto:linuxcnc_cc_grpc",
        "@com_github_grpc_grpc//:grpc++",
    ],
)
