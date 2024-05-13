#include "RendererASCII.cpp";
//#include "Component.hpp"
#include "ComponentBuilder.hpp"

template <typename Rend>
class AbcComp;

template <>
class AbcComp<RendererASCII> : public Component<RendererASCII> {
 public:
  void render(void* callee, RendererASCII& rend) override {
    rend.SetComponent("smth");
    rend << "    123   ";
  }
};

int main() {
  Window<RendererASCII> window(30, 20);

  // Using ComponentBuilder to create and configure a component
  auto abcComponent = ComponentBuilder<AbcComp<RendererASCII>>().SetPosition(10, 0).Build();
  std::cout << abcComponent;
  window.AddComponent("smth", abcComponent);

  window.Render("smth", nullptr);

  return 0;
}
