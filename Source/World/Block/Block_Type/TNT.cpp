#include "TNT.h"

#include "../../World.h"

namespace Block
{
    TNT::TNT()
    :   Block_Type("TNT")
    { }

    Interaction_Type TNT::interact(World& world, Chunk& chunk, const Vector3& location, Temp_Item_ID id) const
    {
        explode(world, location);
        return Interaction_Type::Chunk_Block_Change;
    }

    void TNT::breakBlock(World& world, Chunk& chunk, const Vector3& location, Break_Type breakType) const
    {
        if(breakType == Break_Type::Explosion)
            explode(world, location);
    }

    void TNT::explode(World& world, const Vector3& location) const
    {
        world.makeExplosion(location, 10);
    }
}
