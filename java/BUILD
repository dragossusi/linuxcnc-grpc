load("@io_bazel_rules_kotlin//kotlin:jvm.bzl", "kt_jvm_binary")

package_group(
    name = "visibility",
    packages = ["//java/..."],
)

kt_jvm_binary(
    name = "client",
    main_class = "ro.dragossusi.grpc.linuxcnc.main.MainKt",
    runtime_deps = [
        "//java/ro/dragossusi/grpc/linuxcnc/main",
    ],
)
