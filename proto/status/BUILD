load("@rules_cc//cc:defs.bzl", "cc_proto_library")
load("@rules_proto//proto:defs.bzl", "proto_library")

package(default_visibility = ["//visibility:public"])

proto_library(
    name = "length_unit_proto",
    srcs = ["length_unit.proto"],
)

proto_library(
    name = "position_proto",
    srcs = ["position.proto"],
)

cc_proto_library(
    name = "length_unit_cc_proto",
    deps = [":length_unit_proto"],
)

cc_proto_library(
    name = "position_cc_proto",
    deps = [":position_proto"],
)
