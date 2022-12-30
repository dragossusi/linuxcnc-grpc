load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

cc_binary(
    name = "server",
    srcs = ["linuxcnc_server.cc"],
    defines = ["BAZEL_BUILD"],
    deps = [
        "//proto:linuxcnc_cc_grpc",
        "@com_github_grpc_grpc//:grpc++",
    ],
)
