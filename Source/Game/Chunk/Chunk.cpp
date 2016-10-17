#include "Chunk.h"

#include <iostream>

#include "Blocks.h"

#include "Loader.h"
#include "Height_Generator.h"

#include "Random.h"

#include "World.h"


namespace
{
    Block_t         air;
    Block::Grass    grass;
    Block::Dirt     dirt;
    Block::Stone    stone;
    Block::Water    water;
    Block::Sand     sand;
    Block::Oak_Wood oakWood;
    Block::Oak_Leaf oakLeaf;
}



Chunk :: Chunk ( std::unordered_map<Vector2i, Chunk_Ptr>& chunkMap,
                 const Vector2i& location,
                 const Texture_Atlas& atlas,
                 World& world       )
:   m_p_chunkMap    ( &chunkMap     )
,   m_blocks        ( WIDTH * WIDTH * HEIGHT )
,   m_location      ( location      )
,   m_p_atlas       ( &atlas        )
,   m_p_world       ( &world        )
{
    m_position = { location.x * WIDTH, location.z * WIDTH };
    generateBlockData       ();
    //generateStructureData   ();
}



void Chunk :: setBlock (   GLuint x, GLuint y, GLuint z, Block::ID id, bool overrideBlocks )
{
    switch ( id )
    {
        case Block::ID::Air:
            return;
        case Block::ID::Dirt:
            setBlock( x, y, z, dirt, overrideBlocks );
            break;

        case Block::ID::Grass:
            setBlock( x, y, z, grass, overrideBlocks );
            break;

        case Block::ID::Stone:
            setBlock( x, y, z, stone, overrideBlocks );
            break;

        case Block::ID::Oak_Leaf:
            setBlock( x, y, z, oakLeaf, overrideBlocks );
            break;

        case Block::ID::Oak_Wood:
            setBlock( x, y, z, oakWood, overrideBlocks );
            break;

        case Block::ID::Sand:
            setBlock( x, y, z, sand, overrideBlocks );
            break;

        case Block::ID::Water:
            setBlock( x, y, z, water, overrideBlocks );
            break;
        case Block::ID::NUM_BLOCK_TYPES:
            return;
    }
}



void Chunk :: setBlock (   GLuint x, GLuint y, GLuint z, Block_t& block, bool overrideBlocks )
{
    if ( y > HEIGHT - 1 || y < 0 ) return;

    if ( x < 0 )
    {
        std::cout << "\n" << x << std::endl;
        std::cout << "LESS THAN X" << std::endl;
    }
    else if ( z < 0 )
    {
        std::cout << "LESS THAN Z" << std::endl;
    }
    else if ( x >= WIDTH )
    {
        std::cout << "\n" << x << std::endl;
        std::cout << "GREATER THAN X" << std::endl;
    }
    else if ( z >= WIDTH )
    {
        std::cout << "GREATER THAN Z" << std::endl;
    }
    else
    {
        if ( !m_blocks.at( WIDTH * WIDTH * y + WIDTH * x + z ) )
        {
            m_blocks.at( WIDTH * WIDTH * y + WIDTH * x + z ) = &block;
        }
        else if ( getBlock( x, y, z).getID() == Block::ID::Air )
        {
            m_blocks.at( WIDTH * WIDTH * y + WIDTH * x + z ) = &block;
        }
        else if ( overrideBlocks )
        {
            m_blocks.at( WIDTH * WIDTH * y + WIDTH * x + z ) = &block;
        }
    }
}



const Block_t& Chunk :: getBlock ( int x, int y, int z ) const
{
    if ( x == -1 )
    {
        return getAdjChunkBlock( -1, 0, WIDTH - 1, y, z );
    }
    else if ( z == -1 )
    {
        return getAdjChunkBlock( 0, -1, x, y, WIDTH - 1 );
    }
    else if ( x == WIDTH )
    {
        return getAdjChunkBlock( 1, 0, 0, y, z );
    }
    else if ( z == WIDTH )
    {
        return getAdjChunkBlock( 0, 1, z, y, 0 );
    }
    else if ( y == -1 || y > HEIGHT - 1 )
    {
        return dirt;
    }
    else
    {
        return *m_blocks.at( WIDTH * WIDTH * y + WIDTH * x + z );
    }
    return dirt;    //This is for world edges.
}



const Block_t& Chunk :: getAdjChunkBlock ( int xChange, int zChange, int blockX, int blockY, int blockZ ) const
{
    Vector2i location ( m_location.x + xChange, m_location.z + zChange);

    if ( m_p_chunkMap->find( location ) != m_p_chunkMap->end() )
    {
        return m_p_chunkMap->at( location )->getBlock ( blockX, blockY, blockZ );
    }
    else return dirt;
}



const Block_t& Chunk :: getBlock ( const Vector3& location ) const
{
    return getBlock( location.x, location.y, location.z );
}



const AABB Chunk :: getBlockAABBTop ( const Vector3& location ) const
{
    int x = location.x;
    int y = location.y;
    int z = location.z; //Cast to int

    if ( getBlock( x, y, z ).getID() == Block::ID::Air ) return Vector3{ 0, 0, 0 };

    AABB block ( { 1, 1, 1 } );
    block.setPosition( { x, y + 1, z } );
    return block;
}



bool Chunk :: hasVertexData () const
{
    return m_hasVertexData;
}


bool Chunk :: hasBlockData   () const
{
    return m_hasBlockData;
}


bool Chunk :: hasBuffered () const
{
    return m_hasBufferedData;
}


const Vector2i& Chunk :: getLocation () const
{
    return m_location;
}


const Vector2& Chunk :: getPosition () const
{
    return m_position;
}

const Model& Chunk :: getChunkModel  () const
{
    return m_solidPart.model;
}


const Model& Chunk :: getWaterModel  () const
{
    return m_waterPart.model;
}


const Model& Chunk :: getFloraModel  () const
{
    return m_solidPart.model;
}


void Chunk :: setToDelete ()
{
    m_shouldBeDeleted = true;
}


bool Chunk :: shouldBeDeleted ()
{
    return m_shouldBeDeleted;
}


