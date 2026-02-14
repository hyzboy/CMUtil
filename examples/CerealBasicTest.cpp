#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/array.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>

#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#define CHECK(cond, msg) do { if(!(cond)) { \
    std::ostringstream oss; \
    oss << msg << " (at line " << __LINE__ << ")"; \
    throw std::runtime_error(oss.str()); \
} } while(0)

namespace
{
    struct Vec3
    {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        template <class Archive>
        void serialize(Archive &ar)
        {
            ar(CEREAL_NVP(x), CEREAL_NVP(y), CEREAL_NVP(z));
        }

        bool operator==(const Vec3 &other) const
        {
            return x == other.x && y == other.y && z == other.z;
        }
    };

    struct Item
    {
        int id = 0;
        std::string name;
        std::array<int, 3> stats{};

        template <class Archive>
        void serialize(Archive &ar)
        {
            ar(CEREAL_NVP(id), CEREAL_NVP(name), CEREAL_NVP(stats));
        }

        bool operator==(const Item &other) const
        {
            return id == other.id && name == other.name && stats == other.stats;
        }
    };

    struct Player
    {
        std::string name;
        int level = 0;
        Vec3 position;
        std::vector<Item> inventory;
        std::map<std::string, int> skills;

        template <class Archive>
        void serialize(Archive &ar)
        {
            ar(CEREAL_NVP(name), CEREAL_NVP(level), CEREAL_NVP(position),
               CEREAL_NVP(inventory), CEREAL_NVP(skills));
        }

        bool operator==(const Player &other) const
        {
            return name == other.name && level == other.level && position == other.position &&
                   inventory == other.inventory && skills == other.skills;
        }
    };

    struct Scene
    {
        std::string id;
        std::vector<Player> players;

        template <class Archive>
        void serialize(Archive &ar)
        {
            ar(CEREAL_NVP(id), CEREAL_NVP(players));
        }

        bool operator==(const Scene &other) const
        {
            return id == other.id && players == other.players;
        }
    };

    Scene BuildScene()
    {
        Scene scene;
        scene.id = "scene-001";

        Player alice;
        alice.name = "Alice";
        alice.level = 12;
        alice.position = {1.0f, 2.5f, -3.0f};
        alice.inventory = {
            {101, "Potion", {10, 0, 0}},
            {202, "Sword", {3, 7, 1}}
        };
        alice.skills = { {"heal", 2}, {"slash", 5} };

        Player bob;
        bob.name = "Bob";
        bob.level = 8;
        bob.position = {-4.0f, 0.0f, 6.0f};
        bob.inventory = {
            {303, "Shield", {1, 8, 4}}
        };
        bob.skills = { {"block", 3} };

        scene.players = { alice, bob };
        return scene;
    }

    void RoundTripScene(const Scene &scene)
    {
        const std::string jsonPath = "CerealBasicTest.json";
        const std::string binPath = "CerealBasicTest.bin";

        {
            std::ofstream jsonOut(jsonPath, std::ios::out | std::ios::trunc);
            CHECK(jsonOut.is_open(), "Failed to open JSON output file");
            cereal::JSONOutputArchive oar(jsonOut);
            oar(cereal::make_nvp("scene", scene));
        }

        {
            std::ofstream binOut(binPath, std::ios::binary | std::ios::trunc);
            CHECK(binOut.is_open(), "Failed to open binary output file");
            cereal::BinaryOutputArchive oar(binOut);
            oar(scene);
        }

        std::cout << "[JSON Output] file=" << jsonPath << "\n";
        std::cout << "[Binary Output] file=" << binPath << "\n";

        Scene fromJson;
        Scene fromBinary;

        {
            std::ifstream jsonIn(jsonPath);
            CHECK(jsonIn.is_open(), "Failed to open JSON input file");
            cereal::JSONInputArchive iar(jsonIn);
            iar(cereal::make_nvp("scene", fromJson));
        }
        {
            std::ifstream binIn(binPath, std::ios::binary);
            CHECK(binIn.is_open(), "Failed to open binary input file");
            cereal::BinaryInputArchive iar(binIn);
            iar(fromBinary);
        }

        CHECK(scene == fromJson, "JSON round-trip mismatch");
        CHECK(scene == fromBinary, "Binary round-trip mismatch");
    }
}

int main(int, char **)
{
    std::cout << "[CerealBasicTest] Start" << std::endl;

    Scene scene = BuildScene();
    RoundTripScene(scene);

    std::cout << "[CerealBasicTest] All tests passed" << std::endl;
    return 0;
}
