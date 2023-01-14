load("@rules_cc//cc:defs.bzl", "cc_proto_library")
load("@rules_proto//proto:defs.bzl", "proto_library")

package(default_visibility = ["//visibility:public"])

proto_library(
    name = "pin_proto",
    srcs = ["pin.proto"],
)

proto_library(
    name = "component_proto",
    srcs = ["component.proto"],
)

cc_proto_library(
    name = "pin_cc_proto",
    deps = [":pin_proto"],
)

cc_proto_library(
    name = "component_cc_proto",
    deps = [":component_proto"],
)
