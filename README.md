# Envoy Proxy Deployment on Kubernetes  with a custom load balacing filter

This repository contains configurations, directions, and instructions for deploying Envoy Load balancing Proxy on Kubernetes with a filter


## Sugestions / Directions

To integrate your custom load balancing logic into the Envoy source code and compile it with your code, you'll need to  these  steps:

1 ) Use the new C++ file I made (e.g custom_load_balancer.cc) in the right directory within the Envoy source tree ( source/extensions/load_balancers).Will need to tweak it to your specfic needs.

2 ) Register Your Custom Load Balancer:
Within your custom load balancer file, register your load balancer factory using REGISTER_FACTORY.

3 ) Update the BUILD files to include your custom load balancer file in the compilation process.
You may need to modify other configuration files (e.g., WORKSPACE, BUILD.bazel, or BUILD) as per your build system (Bazel or CMake).

4 ) After building Envoy, you can test your custom load balancer by running the compiled Envoy binary with your configuration that references the custom load balancing policy.# load-balancing-testing
