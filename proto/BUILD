package(default_visibility = ["//visibility:public"])

load("@rules_cc//cc:defs.bzl", "cc_proto_library")
load("@rules_proto//proto:defs.bzl", "proto_library")
load("@rules_java//java:defs.bzl", "java_proto_library")

java_proto_library(
    name = "linuxcnc_java_proto",
    deps = [":linuxcnc_proto"],
)

cc_proto_library(
    name = "linuxcnc_cc_proto",
    deps = [":linuxcnc_proto"],
)

proto_library(
    name = "linuxcnc_proto",
    srcs = ["linuxcnc.proto"],
    deps = [],
)
