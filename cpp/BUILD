load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

#cc_library(#    name = "server_lib",
#    srcs = glob(["*.cc"]),
#    hdrs = glob(["*.h"]),
#    deps = [
#        "//proto:linuxcnc_cc_grpc",
#        "//proto:linuxcnc_cc_proto",
#    ],
#)

cc_binary(
    name = "server",
    srcs = glob(["*.cc"]),
    #    hdrs = glob(["*.h"]),
    defines = ["BAZEL_BUILD"],
    deps = [
        #        ":server_lib",
        "//proto:linuxcnc_cc_grpc",
        "@com_github_grpc_grpc//:grpc++",
    ],
)
