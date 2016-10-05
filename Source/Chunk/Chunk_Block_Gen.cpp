#include "Chunk.h"

#include "Blocks/Blocks.h"

#include <iostream>

void Chunk :: makeBlock ( GLfloat x, GLfloat y, GLfloat z, const Block& block )
{


    if ( getBlock( x, y + 1, z).type == Block_Type::Air ) {
        makeTop( x, y, z, block );

    }
    if ( getBlock( x, y - 1, z).type == Block_Type::Air ) {
        makeBottom( x, y, z, block );
    }


    if ( getBlock( x, y, z + 1).type == Block_Type::Air ) {
        makeFront( x, y, z, block );
    }
    if ( getBlock( x, y, z - 1).type == Block_Type::Air ) {
        makeBack( x, y, z, block );
    }


    if ( getBlock( x - 1, y, z).type == Block_Type::Air ) {
        makeLeft( x, y, z, block );
    }
    if ( getBlock( x + 1, y, z).type == Block_Type::Air )  {
        makeRight( x, y, z, block );
    }
}

/*
 *  This marks the start of creating blocks
 */

void Chunk :: makeFront ( GLfloat x, GLfloat y, GLfloat z, const Block& block )
{
    std::vector<GLfloat> vertices =
    {
        x,      y,      z + 1,
        x + 1,  y,      z + 1,
        x + 1,  y + 1,  z + 1,
        x + 1,  y + 1,  z + 1,
        x,      y + 1,  z + 1,
        x,      y,      z + 1,
    };
    std::vector<GLfloat> textureCoords = block.getSideTxrCoords();

    m_vertexList.insert     ( m_vertexList.end(),   vertices.begin(),       vertices.end()      );
    m_textureList.insert    ( m_textureList.end(),  textureCoords.begin(),  textureCoords.end() );
}


void Chunk :: makeTop ( GLfloat x, GLfloat y, GLfloat z, const Block& block )
{
    std::vector<GLfloat> vertices =
    {
        x,      y + 1, z + 1,
        x + 1,  y + 1, z + 1,
        x + 1,  y + 1, z,
        x + 1,  y + 1, z,
        x,      y + 1, z,
        x,      y + 1, z + 1,
    };

    std::vector<GLfloat> textureCoords = block.getTopTxrCoords();

    m_vertexList.insert     ( m_vertexList.end(),   vertices.begin(),       vertices.end()      );
    m_textureList.insert    ( m_textureList.end(),  textureCoords.begin(),  textureCoords.end() );
}

void Chunk::makeLeft(GLfloat x, GLfloat y, GLfloat z, const Block& block)
{
    std::vector<GLfloat> vertices =
    {
        x, y,       z,
        x, y,       z + 1,
        x, y + 1,   z + 1,
        x, y + 1,   z + 1,
        x, y + 1,   z,
        x, y,       z,
    };

    std::vector<GLfloat> textureCoords = block.getSideTxrCoords();

    m_vertexList.insert     ( m_vertexList.end(),   vertices.begin(),       vertices.end()      );
    m_textureList.insert    ( m_textureList.end(),  textureCoords.begin(),  textureCoords.end() );
}

void Chunk::makeRight(GLfloat x, GLfloat y, GLfloat z, const Block& block)
{
    std::vector<GLfloat> vertices =
    {
        x + 1, y,       z + 1,
        x + 1, y,       z,
        x + 1, y + 1,   z,
        x + 1, y + 1,   z,
        x + 1, y + 1,   z + 1,
        x + 1, y,       z + 1,
    };

    std::vector<GLfloat> textureCoords = block.getSideTxrCoords();

    m_vertexList.insert     ( m_vertexList.end(),   vertices.begin(),       vertices.end()      );
    m_textureList.insert    ( m_textureList.end(),  textureCoords.begin(),  textureCoords.end() );
}

void Chunk::makeBack(GLfloat x, GLfloat y, GLfloat z, const Block& block)
{
    std::vector<GLfloat> vertices =
    {
        x + 1,  y,      z,
        x,      y,      z,
        x,      y + 1,  z,
        x,      y + 1,  z,
        x + 1,  y + 1,  z,
        x + 1,  y,      z,
    };

    std::vector<GLfloat> textureCoords = block.getSideTxrCoords();

    m_vertexList.insert     ( m_vertexList.end(),   vertices.begin(),       vertices.end()      );
    m_textureList.insert    ( m_textureList.end(),  textureCoords.begin(),  textureCoords.end() );
}

void Chunk::makeBottom(GLfloat x, GLfloat y, GLfloat z, const Block& block)
{
    std::vector<GLfloat> vertices =
    {
        x,      y, z,
        x + 1,  y, z,
        x + 1,  y, z + 1,
        x + 1,  y, z + 1,
        x,      y, z + 1,
        x,      y, z
    };

    std::vector<GLfloat> textureCoords = block.getBottomTxrCoords();

    m_vertexList.insert     ( m_vertexList.end(),   vertices.begin(),       vertices.end()      );
    m_textureList.insert    ( m_textureList.end(),  textureCoords.begin(),  textureCoords.end() );
}
