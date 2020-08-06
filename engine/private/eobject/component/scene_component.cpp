#include <eobject/component/scene_component.hpp>

namespace ENGH::EObject::Comps {

void SceneComponent::Traverse(const std::function<bool(Component *)> &target, bool receiveSelf) {
  if (receiveSelf) {
    if (!target(this)) {
      return;
    }
  }
  auto iter = [target](const auto& list, const auto& iter) -> bool {
    for (const auto &e : list) {
      if (!target(e)) {
        return false;
      }
      SceneComponent *sc = dynamic_cast<SceneComponent *>(e);
      if (sc) {
        if(!iter(sc->children, iter)) {
          return false;
        }
      }
    }
    return true;
  };
  iter(children, iter);
}

}
