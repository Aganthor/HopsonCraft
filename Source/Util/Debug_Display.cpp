#include "Debug_Display.h"

#include <memory>
#include <mutex>
#include <SFML/Graphics.hpp>

#include "../World/Chunk/Chunk_Location.h"
#include "../Maths/Position_Converter_Maths.h"

#include "../Renderer/Master_Renderer.h"

namespace Debug_Display
{
    namespace
    {
        sf::Font font;


        //t_ prefix for TEXT
        sf::Text t_fps;

        sf::Text t_highestBlock;

        sf::Text t_chunkPosition;
        sf::Text t_blockPosition;
        sf::Text t_worldPosition;

        sf::Text t_lookVector;

        sf::Text t_chunkUpdates;
        sf::Text t_numChunks;

        sf::Text t_heldBlock;

        sf::Text t_lightText;


        void initText(sf::Text& text)
        {
            text.setFont            (font);
            text.setCharacterSize   (23);
            text.move               (5, 0);
            text.setOutlineColor    (sf::Color::Black);
            text.setOutlineThickness(2);
        }
    }

    void init()
    {
        font.loadFromFile("Data/Font/rs.ttf");

        initText(t_fps);
        initText(t_highestBlock);

        initText(t_chunkPosition);
        initText(t_blockPosition);
        initText(t_worldPosition);

        initText(t_lookVector);

        initText(t_chunkUpdates);
        initText(t_numChunks);

        initText(t_heldBlock);

        initText(t_lightText);

        t_chunkPosition.move(0, 40);
        t_blockPosition.move(0, 80);
        t_worldPosition.move(0, 120);

        t_lookVector.move(0, 160);

        t_chunkUpdates.move(300, 0);
        t_numChunks.move(300, 40);

        t_heldBlock.move(500, 0);

        t_lightText.move(500, 40);
        t_highestBlock.move(500, 110);

    }


    void addHighestBlock(uint32_t y)
    {
        t_highestBlock.setString("Highest Block -> " + std::to_string(y));
    }

    void addFPS(float fps)
    {
        t_fps.setString("FPS: " + std::to_string((int)fps));
    }

    void addPlayerPosition  (const Vector3& location)
    {
        Chunk_Location cl(Maths::worldToChunkPosition(location));
        Block_Location bl(Maths::worldToBlockPosition(location));

        t_chunkPosition.setString("Chunk Location: X: " + std::to_string(cl.x) +
                                                 " Z: " + std::to_string(cl.z));

        t_blockPosition.setString("Block Location: X: " + std::to_string((int)bl.x) +
                                                 " Y: " + std::to_string((int)bl.y) +
                                                 " Z: " + std::to_string((int)bl.z));

        t_worldPosition.setString("World Location: X: " + std::to_string((int)location.x) +
                                                 " Y: " + std::to_string((int)location.y) +
                                                 " Z: " + std::to_string((int)location.z));
    }

    void addPlayerLightLevel(const Vector3& location, const Chunk* chunk)
    {
        if (!chunk)
        {
            t_lightText.setString("Not in Chunk");
        }
        else
        {
            auto pos = Maths::worldToBlockPosition  (location);
            std::string nat (std::to_string(chunk->getNaturalLight  (pos)));
            std::string blo (std::to_string(chunk->getBlockLight    (pos)));
            std::string light("Lights:\n");
            t_lightText.setString(light +
                                  "Natural -> " + nat + "\n" +
                                  "Blocks  -> " + blo);
        }
    }


    void addLookVector(const Vector3& rotation)
    {
        t_lookVector.setString("Look Rotation: X: " + std::to_string((int)rotation.x) +
                                             " Y: " + std::to_string((int)rotation.y) +
                                             " Z: " + std::to_string((int)rotation.z));
    }

    void addChunkUpdates (size_t numChunks)
    {
        t_chunkUpdates.setString("Chunk Updates: " + std::to_string(numChunks));
    }

    void addChunkAmounth (size_t numChunks)
    {
        t_numChunks.setString("Total Chunks: " + std::to_string(numChunks));
    }

    void addheldBlock(const Block::Block_Type& block)
    {
        std::string name = block.getData().getName();
        std::string id   = std::to_string((uint32_t)(block.getData().getID()));

        t_heldBlock.setString("Held block: " + name + "\tBlock ID: " + id);
    }


    void draw(Master_Renderer& renderer)
    {
        renderer.draw(t_fps);

        renderer.draw(t_chunkPosition);
        renderer.draw(t_blockPosition);
        renderer.draw(t_worldPosition);

        renderer.draw(t_lookVector);

        renderer.draw(t_chunkUpdates);
        renderer.draw(t_numChunks);

        renderer.draw(t_heldBlock);

        renderer.draw(t_lightText);

        renderer.draw(t_highestBlock);
    }
}
