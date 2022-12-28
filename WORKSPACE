workspace(name = "linuxcnc-grpc")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")

### linuxcnc git repo
new_git_repository(
    name = "linuxcnc",
    build_file = "linuxcnc/linuxcnc.BUILD",
    commit = "213e0ae91c9b26d9c86065ec438450cac4d1cc80",
    remote = "https://github.com/LinuxCNC/linuxcnc.git",
)

# JVM external
http_archive(
    name = "rules_jvm_external",
    sha256 = "cd1a77b7b02e8e008439ca76fd34f5b07aecb8c752961f9640dea15e9e5ba1ca",
    strip_prefix = "rules_jvm_external-4.2",
    url = "https://github.com/bazelbuild/rules_jvm_external/archive/4.2.zip",
)

load("@rules_jvm_external//:defs.bzl", "maven_install")

# Repositories
load(
    "//:repositories.bzl",
    "IO_GRPC_GRPC_KOTLIN_ARTIFACTS",
    "IO_GRPC_GRPC_KOTLIN_OVERRIDE_TARGETS",
    "com_github_grpc_grpc",
    "grpc_kt_repositories",
    "io_grpc_grpc_java",
)

io_grpc_grpc_java()

com_github_grpc_grpc()

load(
    "@io_grpc_grpc_java//:repositories.bzl",
    "IO_GRPC_GRPC_JAVA_ARTIFACTS",
    "IO_GRPC_GRPC_JAVA_OVERRIDE_TARGETS",
    "grpc_java_repositories",
)

# Maven
maven_install(
    artifacts = [
        "com.google.jimfs:jimfs:1.1",
        "com.google.truth.extensions:truth-proto-extension:1.0.1",
        "com.google.protobuf:protobuf-kotlin:3.18.0",
    ] + IO_GRPC_GRPC_KOTLIN_ARTIFACTS + IO_GRPC_GRPC_JAVA_ARTIFACTS,
    generate_compat_repositories = True,
    override_targets = dict(
        IO_GRPC_GRPC_KOTLIN_OVERRIDE_TARGETS.items() +
        IO_GRPC_GRPC_JAVA_OVERRIDE_TARGETS.items(),
    ),
    repositories = [
        "https://repo.maven.apache.org/maven2/",
    ],
)

load("@maven//:compat.bzl", "compat_repositories")

compat_repositories()

# gRPC
#load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")
#load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")

#grpc_deps()

#grpc_extra_deps()

grpc_kt_repositories()

grpc_java_repositories()

# Protocol Buffers
load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")

protobuf_deps()

# Kotlin
load("@io_bazel_rules_kotlin//kotlin:repositories.bzl", "kotlin_repositories")

kotlin_repositories()

load("@io_bazel_rules_kotlin//kotlin:core.bzl", "kt_register_toolchains")

kt_register_toolchains()

### rules_cc defines rules for generating C++ code from Protocol Buffers.
http_archive(
    name = "rules_cc",
    sha256 = "35f2fb4ea0b3e61ad64a369de284e4fbbdcdba71836a5555abb5e194cf119509",
    strip_prefix = "rules_cc-624b5d59dfb45672d4239422fa1e3de1822ee110",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/rules_cc/archive/624b5d59dfb45672d4239422fa1e3de1822ee110.tar.gz",
        "https://github.com/bazelbuild/rules_cc/archive/624b5d59dfb45672d4239422fa1e3de1822ee110.tar.gz",
    ],
)

load("@rules_cc//cc:repositories.bzl", "rules_cc_dependencies")

rules_cc_dependencies()
