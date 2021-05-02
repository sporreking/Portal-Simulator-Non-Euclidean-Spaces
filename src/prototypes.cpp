#include "prototypes.h"

#include "components/playercontroller.h"

namespace PROT {
Entity* newPlayer(double const& speed, bool noclip) {
    return (new Entity)->addComponent(new COMP::PlayerController(speed, noclip));
}
}  // namespace PROT