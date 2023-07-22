cc_library(
    name = "status_reader",
    srcs = ["status_reader.cc"],
    hdrs = ["status_reader.hh"],
    copts = [
        "-Iexternal/linuxcnc/include",
        "-Iexternal/linuxcnc/src",
    ],
    defines = ["BAZEL_BUILD"],
    deps = [
        "@linuxcnc",
        "@linuxcnc_proto//:linuxcnc_cc_proto",
        "@linuxcnc_proto//status:length_unit_cc_proto",
        "@linuxcnc_proto//status:position_cc_proto",
        "@linuxcnc_proto//status/task:task_cc_proto",
    ],
)

cc_library(
    name = "error_reader",
    srcs = ["error_reader.cc"],
    hdrs = ["error_reader.hh"],
    copts = [
        "-Iexternal/linuxcnc/include",
        "-Iexternal/linuxcnc/src",
    ],
    defines = ["BAZEL_BUILD"],
    deps = [
        "@linuxcnc",
        "@linuxcnc_proto//:linuxcnc_cc_proto",
        "@linuxcnc_proto//status/message:message_cc_proto",
    ],
)

cc_library(
    name = "component",
    srcs = ["component.cc"],
    hdrs = ["component.hh"],
    copts = [
        "-Iexternal/linuxcnc/include",
        "-Iexternal/linuxcnc/src",
    ],
    defines = ["BAZEL_BUILD"],
    deps = [
        "@linuxcnc",
        "@linuxcnc_proto//:linuxcnc_cc_proto",
        "@linuxcnc_proto//status/message:message_cc_proto",
    ],
)

cc_library(
    name = "command_writer",
    srcs = ["command_writer.cc"],
    hdrs = ["command_writer.hh"],
    copts = [
        "-Iexternal/linuxcnc/include",
        "-Iexternal/linuxcnc/src",
    ],
    defines = ["BAZEL_BUILD"],
    deps = [
        "@linuxcnc",
        "@linuxcnc_proto//:linuxcnc_cc_proto",
        "@linuxcnc_proto//status:length_unit_cc_proto",
        "@linuxcnc_proto//status:position_cc_proto",
        "@linuxcnc_proto//status/task:task_cc_proto",
    ],
)

cc_library(
    name = "hal_handler",
    srcs = ["hal_handler.cc"],
    hdrs = ["hal_handler.hh"],
    copts = [
        "-Iexternal/linuxcnc/include",
        "-Iexternal/linuxcnc/src",
        "-DULAPI",
    ],
    defines = ["BAZEL_BUILD"],
    deps = [
        ":component",
        "@linuxcnc",
        "@linuxcnc_proto//:linuxcnc_cc_proto",
    ],
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
        ":command_writer",
        ":error_reader",
        ":hal_handler",
        ":status_reader",
        "@com_github_grpc_grpc//:grpc++",
        "@linuxcnc_proto//:linuxcnc_grpc",
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
