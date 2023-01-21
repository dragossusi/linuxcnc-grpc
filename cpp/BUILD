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
        "//proto:linuxcnc_cc_proto",
        "//proto/status:length_unit_cc_proto",
        "//proto/status:position_cc_proto",
        "//proto/status/task:task_cc_proto",
        "@linuxcnc",
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
        "//proto:linuxcnc_cc_proto",
        "//proto/status/message:message_cc_proto",
        "@linuxcnc",
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
        "//proto:linuxcnc_cc_proto",
        "//proto/status:length_unit_cc_proto",
        "//proto/status:position_cc_proto",
        "//proto/status/task:task_cc_proto",
        "@linuxcnc",
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
        ":status_reader",
        "//proto:linuxcnc_grpc",
        "@com_github_grpc_grpc//:grpc++",
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
