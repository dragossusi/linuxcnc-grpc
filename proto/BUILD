load("@rules_cc//cc:defs.bzl", "cc_proto_library")
load("@rules_proto//proto:defs.bzl", "proto_library")
load("@rules_java//java:defs.bzl", "java_proto_library")
load("@io_grpc_grpc_java//:java_grpc_library.bzl", "java_grpc_library")
#load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")
#load("@com_github_grpc_grpc//bazel:grpc_build_system.bzl", "grpc_proto_library")

package(default_visibility = ["//visibility:public"])

proto_library(
    name = "linuxcnc_proto",
    srcs = ["linuxcnc.proto"],
)

#grpc_proto_library(
#    name = "linuxcnc_grpc",
#    srcs = ["linuxcnc.proto"],
#    deps = [],
#)

java_proto_library(
    name = "linuxcnc_java_proto",
    deps = [":linuxcnc_proto"],
)

java_grpc_library(
    name = "linuxcnc_java_grpc",
    srcs = [":linuxcnc_proto"],
    deps = [":linuxcnc_java_proto"],
)

cc_proto_library(
    name = "linuxcnc_cc_proto",
    deps = [":linuxcnc_proto"],
)

# TODO
#cc_grpc_library(
#    name = "linuxcnc_cc_grpc",
#    srcs = [":linuxcnc_proto"],
#    deps = [":linuxcnc_cc_proto"],
#)
