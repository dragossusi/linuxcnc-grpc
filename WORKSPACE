workspace(name = "linuxcnc-grpc")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# maven
MAVEN_REPOSITORY_RULES_VERSION = "1.2.0"

MAVEN_REPOSITORY_RULES_SHA = "9e23155895d2bfc60b35d2dfd88c91701892a7efba5afacdf00cebc0982229fe"

http_archive(
    name = "maven_repository_rules",
    sha256 = MAVEN_REPOSITORY_RULES_SHA,
    strip_prefix = "bazel_maven_repository-%s" % MAVEN_REPOSITORY_RULES_VERSION,
    type = "zip",
    urls = ["https://github.com/square/bazel_maven_repository/archive/%s.zip" % MAVEN_REPOSITORY_RULES_VERSION],
)

load("@maven_repository_rules//maven:maven.bzl", "maven_repository_specification")

maven_repository_specification(
    name = "maven",
    artifacts = {
        "com.google.guava:guava:25.0-jre": {"sha256": "3fd4341776428c7e0e5c18a7c10de129475b69ab9d30aeafbb5c277bb6074fa9"},
    },
)

# Repositories
load(
    "//:repositories.bzl",
    "com_github_grpc_grpc",
    "linuxcnc_local",
    "linuxcnc_proto",
)

com_github_grpc_grpc()

linuxcnc_local()

linuxcnc_proto()

# gRPC
load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")

grpc_deps()

load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")

grpc_extra_deps()

# Protocol Buffers
load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")

protobuf_deps()

# CC
load("@rules_cc//cc:repositories.bzl", "rules_cc_dependencies")

rules_cc_dependencies()
