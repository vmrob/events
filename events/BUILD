cc_library(
    name = "main",
    srcs = ["src/Publisher.cpp"],
    strip_include_prefix = "include",
    hdrs = glob(["include/events/*.h"]),
    deps = ["@constexpr//:main"],
    visibility = ["//visibility:public"]
)
