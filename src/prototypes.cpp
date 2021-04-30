#include "prototypes.h"

#include "components/playercontroller.h"

namespace PROT {
Entity* newPlayer(double const& speed = 1.0, bool noclip = false) {
    return (new Entity)->addComponent(new COMP::PlayerController(speed, noclip));
}
}  // namespace PROT