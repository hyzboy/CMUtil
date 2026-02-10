#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/cereal.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>

#include <cstdint>
#include <fstream>
#include <iostream>
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
    struct Config
    {
        int mode = 0;
        std::vector<int> thresholds;
        std::string comment;

        template <class Archive>
        void save(Archive &ar, const std::uint32_t version) const
        {
            ar(CEREAL_NVP(mode), CEREAL_NVP(thresholds));
            if (version >= 2)
                ar(CEREAL_NVP(comment));
        }

        template <class Archive>
        void load(Archive &ar, const std::uint32_t version)
        {
            ar(CEREAL_NVP(mode), CEREAL_NVP(thresholds));
            if (version >= 2)
                ar(CEREAL_NVP(comment));
            else
                comment.clear();
        }

        bool operator==(const Config &other) const
        {
            return mode == other.mode && thresholds == other.thresholds && comment == other.comment;
        }
    };

    struct Profile
    {
        std::string name;
        Config config;
        std::vector<std::string> tags;

        template <class Archive>
        void serialize(Archive &ar)
        {
            ar(CEREAL_NVP(name), CEREAL_NVP(config), CEREAL_NVP(tags));
        }

        bool operator==(const Profile &other) const
        {
            return name == other.name && config == other.config && tags == other.tags;
        }
    };

    Profile BuildProfile()
    {
        Profile profile;
        profile.name = "default";
        profile.config.mode = 3;
        profile.config.thresholds = { 5, 10, 15 };
        profile.config.comment = "versioned settings";
        profile.tags = { "alpha", "beta" };
        return profile;
    }

    void RoundTripProfile(const Profile &profile)
    {
        const std::string jsonPath = "CerealVersionedTest.json";
        const std::string binPath = "CerealVersionedTest.bin";

        {
            std::ofstream jsonOut(jsonPath, std::ios::out | std::ios::trunc);
            CHECK(jsonOut.is_open(), "Failed to open JSON output file");
            cereal::JSONOutputArchive oar(jsonOut);
            oar(cereal::make_nvp("profile", profile));
        }

        {
            std::ofstream binOut(binPath, std::ios::binary | std::ios::trunc);
            CHECK(binOut.is_open(), "Failed to open binary output file");
            cereal::BinaryOutputArchive oar(binOut);
            oar(profile);
        }

        std::cout << "[JSON Output] file=" << jsonPath << "\n";
        std::cout << "[Binary Output] file=" << binPath << "\n";

        Profile fromJson;
        Profile fromBinary;

        {
            std::ifstream jsonIn(jsonPath);
            CHECK(jsonIn.is_open(), "Failed to open JSON input file");
            cereal::JSONInputArchive iar(jsonIn);
            iar(cereal::make_nvp("profile", fromJson));
        }
        {
            std::ifstream binIn(binPath, std::ios::binary);
            CHECK(binIn.is_open(), "Failed to open binary input file");
            cereal::BinaryInputArchive iar(binIn);
            iar(fromBinary);
        }

        CHECK(profile == fromJson, "JSON round-trip mismatch");
        CHECK(profile == fromBinary, "Binary round-trip mismatch");
    }
}

CEREAL_CLASS_VERSION(Config, 2)

int main(int, char **)
{
    std::cout << "[CerealVersionedTest] Start" << std::endl;

    Profile profile = BuildProfile();
    RoundTripProfile(profile);

    std::cout << "[CerealVersionedTest] All tests passed" << std::endl;
    return 0;
}
