# FACTORY
cc_library(
  name = "factory_abstract_lib",
  hdrs = ["factory/factory_abstract/car_factory.hh",
          "factory/factory_abstract/car.hh"],
)

cc_binary(
  name = "factory_abstract",
  srcs = ["factory/factory_abstract/main.cc"],
  deps = [
    ":factory_abstract_lib",
  ],
)

cc_binary(
  name = "factory_method",
  srcs = ["factory/factory_method.cc"],
)

cc_binary(
  name = "factory_inner",
  srcs = ["factory/factory_inner.cc"],
)

cc_binary(
  name = "factory_functional",
  srcs = ["factory/factory_functional.cc"],
)

# BUILDER
cc_library(
  name = "builder_lib",
  srcs = glob(["builder/*.cc"]),
  hdrs = glob(["builder/*.hh"]),
)

cc_binary(
  name = "builder",
  srcs = ["builder/main.cpp"],
  deps = [
    ":builder_lib",
  ],
)
