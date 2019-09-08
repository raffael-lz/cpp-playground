cc_library(
  name = "observer_classic_lib",
  srcs = glob(["observer_classic/*.cc"]),
  hdrs = glob(["observer_classic/*.h"]),
)

cc_binary(
  name = "observer_classic",
  srcs = ["observer_classic/main.cpp"],
  deps = [
    ":observer_classic_lib",
  ],
)

cc_library(
  name = "observer_modern_lib",
  srcs = glob(["observer_modern/*.cc"]),
  hdrs = glob(["observer_modern/*.h"]),
)

cc_binary(
  name = "observer_modern",
  srcs = ["observer_modern/main.cpp"],
  deps = [
    ":observer_modern_lib",
  ],
)
