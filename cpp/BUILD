package(default_visibility = ["//visibility:public"])

cc_library(
    name = "server_lib",
    srcs = glob(["*.cc"]),
    hdrs = glob(["*.h"]),
    deps = [
        "//proto:linuxcnc_cc_grpc",
        "//proto:linuxcnc_cc_proto",
    ],
)

cc_binary(
    name = "server",
    deps = [":server_lib"],
)
