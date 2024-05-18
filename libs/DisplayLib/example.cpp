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
    rend << "----------";
    rend << "|  hello  |";
    rend << "----------";
    rend.Draw();
  }
};

int main() {
  Window<RendererASCII> window(30, 20);

  // Using ComponentBuilder to create and configure a component
  auto abcComponent = ComponentBuilder<AbcComp<RendererASCII>>()
                          .SetPosition(10, 10)
                          .SetSize(10, 10)
                          .Build();
  window.AddComponent("smth", abcComponent);

  window.Render("smth", nullptr);

  return 0;
}
