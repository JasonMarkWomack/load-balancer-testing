#include "envoy/upstream/load_balancer.h"
#include "envoy/upstream/load_balancer_factory.h"

namespace Envoy {
namespace Upstream {

// Custom load balancer that implements round-robin host selection
class RoundRobinLoadBalancer : public LoadBalancer {
public:
  RoundRobinLoadBalancer(const PrioritySet& priority_set, const PrioritySet* local_priority_set,
                         ClusterStats& stats, Runtime::Loader& runtime,
                         Random::RandomGenerator& random)
      : LoadBalancer(priority_set, local_priority_set, stats, runtime, random) {}

  // Selects the next host based on round-robin strategy
  HostConstSharedPtr chooseHost(LoadBalancerContext* context) override {
    const auto& hosts = prioritySet().hostsWithoutHealthCheck();
    if (hosts.empty()) {
      return nullptr;
    }
    // Use round-robin index to select the next host
    const uint32_t index = roundRobinIndex_++ % hosts.size();
    return hosts[index];
  }

private:
  uint32_t roundRobinIndex_ = 0; // Round-robin index for host selection
};

// Factory for creating instances of RoundRobinLoadBalancer
class RoundRobinLoadBalancerFactory : public LoadBalancerFactory {
public:
  // Returns the name of the load balancer
  std::string name() const override { return "custom_round_robin"; }

  // Creates a new instance of RoundRobinLoadBalancer
  LoadBalancerPtr create() const override {
    return std::make_unique<RoundRobinLoadBalancer>(prioritySet(), localPrioritySet(), stats(), runtime(), random());
  }
};

// Register the custom load balancer factory
static Registry::RegisterFactory<RoundRobinLoadBalancerFactory, LoadBalancerFactory>
    registered_;

} // namespace Upstream
} // namespace Envoy
