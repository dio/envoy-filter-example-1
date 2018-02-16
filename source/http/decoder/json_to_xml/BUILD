package(default_visibility = ["//visibility:public"])

load(
    "@envoy//bazel:envoy_build_system.bzl",
    "envoy_cc_binary",
    "envoy_cc_library",
    "envoy_cc_test",
)
load("@envoy_api//bazel:api_build_system.bzl", "api_proto_library")

envoy_cc_binary(
    name = "envoy",
    repository = "@envoy",
    deps = [
        ":filter_config",
        "@envoy//source/exe:envoy_main_entry_lib",
    ],
)

api_proto_library(
    name = "filter_proto",
    srcs = ["filter.proto"],
)

envoy_cc_library(
    name = "filter_lib",
    srcs = ["filter.cc"],
    hdrs = ["filter.h"],
    external_deps = [
        "rapidjson",
        "rapidxml",
    ],
    repository = "@envoy",
    deps = [
        ":filter_proto_cc",
        "@envoy//source/exe:envoy_common_lib",
    ],
)

envoy_cc_library(
    name = "filter_config",
    srcs = ["filter_config.cc"],
    repository = "@envoy",
    deps = [
        ":filter_lib",
        "@envoy//source/exe:envoy_common_lib",
    ],
)

envoy_cc_test(
    name = "filter_integration_test",
    srcs = ["filter_integration_test.cc"],
    repository = "@envoy",
    deps = [
        ":filter_config",
        "@envoy//test/integration:http_integration_lib",
        "@envoy_api//envoy/config/filter/network/http_connection_manager/v2:http_connection_manager_cc",
    ],
)