load("@rules_cc//cc:defs.bzl", "cc_proto_library")
load("@rules_proto//proto:defs.bzl", "proto_library")
load("@rules_java//java:defs.bzl", "java_proto_library")
load("@io_grpc_grpc_java//:java_grpc_library.bzl", "java_grpc_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")
load("@com_github_grpc_grpc//bazel:grpc_build_system.bzl", "grpc_proto_library")
load("@com_github_grpc_grpc_kotlin//:kt_jvm_grpc.bzl", "kt_jvm_grpc_library", "kt_jvm_proto_library")

package(default_visibility = ["//visibility:public"])

java_proto_library(
    name = "linuxcnc_java_proto",
    deps = [":linuxcnc_proto"],
)

proto_library(
    name = "linuxcnc_proto",
    srcs = ["linuxcnc.proto"],
    deps = [
        "//proto/hal:component_proto",
        "//proto/hal:pin_proto",
        "//proto/status/io:io_proto",
        "//proto/status/motion:motion_proto",
        "//proto/status/task:task_proto",
    ],
)

java_grpc_library(
    name = "linuxcnc_java_grpc",
    srcs = [":linuxcnc_proto"],
    deps = [":linuxcnc_java_proto"],
)

kt_jvm_grpc_library(
    name = "linuxcnc_kt_grpc",
    srcs = [":linuxcnc_proto"],
    deps = [":linuxcnc_java_proto"],
)

cc_proto_library(
    name = "linuxcnc_cc_proto",
    deps = [":linuxcnc_proto"],
)

cc_grpc_library(
    name = "linuxcnc_grpc",
    srcs = [":linuxcnc_proto"],
    grpc_only = True,
    #    has_services = True,
    deps = [
        ":linuxcnc_cc_proto",
        "//proto/hal:component_cc_proto",
        "//proto/hal:pin_cc_proto",
        "//proto/status/io:io_cc_proto",
        "//proto/status/task:task_cc_proto",
    ],
)
