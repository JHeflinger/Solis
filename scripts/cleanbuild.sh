bazel clean --expunge
./scripts/shaders.sh
bazel build Solis
bazel build Flare