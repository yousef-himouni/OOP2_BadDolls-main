#include "Resources.h"
namespace
{
    AnimationData FirstPlayerData()
    {
        const auto size = sf::Vector2i(32, 32);
        const auto initSpace = sf::Vector2i(96, 128);
        auto firstPlayer = AnimationData{};
        auto currentStart = initSpace;

        auto nextStart = [&]()
        {
            currentStart.x += size.x;
            return currentStart;
        };

        firstPlayer.m_data[Direction::Down].emplace_back(currentStart, size);
        for (int i = 0; i < 2; ++i) {
            firstPlayer.m_data[Direction::Down].emplace_back(nextStart(), size);
        }
        currentStart.x = 96;
        currentStart.y += size.y;
        firstPlayer.m_data[Direction::Left].emplace_back(currentStart, size);
        for (int i = 0; i < 2; ++i) {
            firstPlayer.m_data[Direction::Left].emplace_back(nextStart(), size);
        }
        currentStart.x = 96;
        currentStart.y += size.y;
        firstPlayer.m_data[Direction::Right].emplace_back(currentStart, size);
        for (int i = 0; i < 2; ++i) {
            firstPlayer.m_data[Direction::Right].emplace_back(nextStart(), size);
        }
        currentStart.x = 96;
        currentStart.y += size.y;
        firstPlayer.m_data[Direction::Up].emplace_back(currentStart, size);
        for (int i = 0; i < 2; ++i) {
            firstPlayer.m_data[Direction::Up].emplace_back(nextStart(), size);
        }


        return firstPlayer;
    }
    AnimationData SecondPlayerData()
    {
        const auto size = sf::Vector2i(32, 32);
        const auto initSpace = sf::Vector2i(0, 0);
        auto secondPlayer = AnimationData{};
        auto currentStart = initSpace;

        auto nextStart = [&]()
        {
            currentStart.x += size.x;
            return currentStart;
        };
        secondPlayer.m_data[Direction::Down].emplace_back(currentStart, size);
        for (int i = 0; i < 2; ++i) {
            secondPlayer.m_data[Direction::Down].emplace_back(nextStart(), size);
        }
        currentStart.x = 0;
        currentStart.y += size.y;
        secondPlayer.m_data[Direction::Left].emplace_back(currentStart, size);
        for (int i = 0; i < 2; ++i) {
            secondPlayer.m_data[Direction::Left].emplace_back(nextStart(), size);
        }
        currentStart.x = 0;
        currentStart.y += size.y;
        secondPlayer.m_data[Direction::Right].emplace_back(currentStart, size);
        for (int i = 0; i < 2; ++i) {
            secondPlayer.m_data[Direction::Right].emplace_back(nextStart(), size);
        }
        currentStart.x = 96;
        currentStart.y += size.y;
        secondPlayer.m_data[Direction::Up].emplace_back(currentStart, size);
        for (int i = 0; i < 2; ++i) {
            secondPlayer.m_data[Direction::Up].emplace_back(nextStart(), size);
        }


        return secondPlayer;
    }
    AnimationData EnemySpiderData()
    {
        const auto size = sf::Vector2i(40, 40);
        const auto initSpace = sf::Vector2i(0, 40);
        auto enemySpider = AnimationData{};
        auto currentStart = initSpace;

        auto nextStart = [&]()
        {
            currentStart.x += size.x;
            return currentStart;
        };

        enemySpider.m_data[Direction::Left].emplace_back(currentStart, size);
        for (int i = 0; i < 2; ++i) {
            enemySpider.m_data[Direction::Left].emplace_back(nextStart(), size);
        }

        currentStart = sf::Vector2i(0, 80);

        // Create left-direction frames as a reflection of the right-direction frames
        enemySpider.m_data[Direction::Right].emplace_back(currentStart, size);
        for (int i = 0; i < 2; ++i) {
            enemySpider.m_data[Direction::Right].emplace_back(nextStart(), size);
        }
        return enemySpider;
    }

    AnimationData EnemyGhostData()
    {
        const auto size = sf::Vector2i(40, 40);
        const auto initSpace = sf::Vector2i(0, 0);
        auto enemyGhost = AnimationData{};
        auto currentStart = initSpace;

        auto nextStart = [&]()
        {
            currentStart.x += size.x;
            return currentStart;
        };

        enemyGhost.m_data[Direction::Down].emplace_back(currentStart, size);
        for (int i = 0; i < 2; ++i) {
            enemyGhost.m_data[Direction::Down].emplace_back(nextStart(), size);
        }

        currentStart = sf::Vector2i(0, 40);

        enemyGhost.m_data[Direction::Left].emplace_back(currentStart, size);
        for (int i = 0; i < 2; ++i) {
            enemyGhost.m_data[Direction::Left].emplace_back(nextStart(), size);
        }

        currentStart = sf::Vector2i(0, 80);

        // Create left-direction frames as a reflection of the right-direction frames
        enemyGhost.m_data[Direction::Right].emplace_back(currentStart, size);
        for (int i = 0; i < 2; ++i) {
            enemyGhost.m_data[Direction::Right].emplace_back(nextStart(), size);
        }

        currentStart = sf::Vector2i(0, 120);

        // Create left-direction frames as a reflection of the right-direction frames
        enemyGhost.m_data[Direction::Up].emplace_back(currentStart, size);
        for (int i = 0; i < 2; ++i) {
            enemyGhost.m_data[Direction::Up].emplace_back(nextStart(), size);
        }
        return enemyGhost;
    }



    AnimationData HeartData()
    {
        const auto size = sf::Vector2i(32, 32);
        const auto initSpace = sf::Vector2i(0, 0);
        auto heart = AnimationData{};
        auto currentStart = initSpace;

        auto nextStart = [&]()
        {
            currentStart.x += size.x;
            return currentStart;
        };
        heart.m_data[Direction::Stay].emplace_back(currentStart, size);
        for (int i = 0; i < 7; ++i) {
            heart.m_data[Direction::Stay].emplace_back(nextStart(), size);
        }
        currentStart = sf::Vector2i(0, 32);
        heart.m_data[Direction::Stay].emplace_back(currentStart, size);
        for (int i = 0; i < 7; ++i) {
            heart.m_data[Direction::Stay].emplace_back(nextStart(), size);
        }
        return heart;
    }
    AnimationData HealingBallData()
    {
        const auto size = sf::Vector2i(40, 35);
        const auto initSpace = sf::Vector2i(0, 0);
        auto healingBall = AnimationData{};
        auto currentStart = initSpace;

        auto nextStart = [&]()
        {
            currentStart.x += size.x;
            return currentStart;
        };
        healingBall.m_data[Direction::Stay].emplace_back(currentStart, size);
        for (int i = 0; i < 4; ++i) {
            healingBall.m_data[Direction::Stay].emplace_back(nextStart(), size);
        }
        currentStart = sf::Vector2i(0, 40);
        healingBall.m_data[Direction::Stay].emplace_back(currentStart, size);
        for (int i = 0; i < 4; ++i) {
            healingBall.m_data[Direction::Stay].emplace_back(nextStart(), size);
        }
        currentStart = sf::Vector2i(0, 80);
        healingBall.m_data[Direction::Stay].emplace_back(currentStart, size);
        for (int i = 0; i < 4; ++i) {
            healingBall.m_data[Direction::Stay].emplace_back(nextStart(), size);
        }
        currentStart = sf::Vector2i(0, 120);
        healingBall.m_data[Direction::Stay].emplace_back(currentStart, size);
        for (int i = 0; i < 4; ++i) {
            healingBall.m_data[Direction::Stay].emplace_back(nextStart(), size);
        }
        currentStart = sf::Vector2i(0, 160);
        healingBall.m_data[Direction::Stay].emplace_back(currentStart, size);
        for (int i = 0; i < 4; ++i) {
            healingBall.m_data[Direction::Stay].emplace_back(nextStart(), size);
        }
        return healingBall;
    }

    AnimationData CoinData()
    {
        const auto size = sf::Vector2i(32, 32);
        const auto initSpace = sf::Vector2i(0, 0);
        auto coin = AnimationData{};
        auto currentStart = initSpace;

        auto nextStart = [&]()
        {
            currentStart.x += size.x;
            return currentStart;
        };
        coin.m_data[Direction::Stay].emplace_back(currentStart, size);
        for (int i = 0; i < 4; ++i) {
            coin.m_data[Direction::Stay].emplace_back(nextStart(), size);
        }
        currentStart = sf::Vector2i(0, 32);
        coin.m_data[Direction::Stay].emplace_back(currentStart, size);
        for (int i = 0; i < 4; ++i) {
            coin.m_data[Direction::Stay].emplace_back(nextStart(), size);
        }
        return coin;
    }
    AnimationData FireData()
    {
        const auto size = sf::Vector2i(40, 25);
        const auto initSpace = sf::Vector2i(0, 0);
        auto fire = AnimationData{};
        auto currentStart = initSpace;

        auto nextStart = [&]()
        {
            currentStart.x += size.x;
            return currentStart;
        };
        fire.m_data[Direction::Stay].emplace_back(currentStart, size);
        for (int i = 0; i < 3; ++i) {
            fire.m_data[Direction::Stay].emplace_back(nextStart(), size);
        }
        currentStart = sf::Vector2i(0, 30);
        fire.m_data[Direction::Stay].emplace_back(currentStart, size);
        for (int i = 0; i < 3; ++i) {
            fire.m_data[Direction::Stay].emplace_back(nextStart(), size);
        }
        currentStart = sf::Vector2i(0, 60);
        fire.m_data[Direction::Stay].emplace_back(currentStart, size);
        for (int i = 0; i < 3; ++i) {
            fire.m_data[Direction::Stay].emplace_back(nextStart(), size);
        }
        currentStart = sf::Vector2i(0, 90);
        fire.m_data[Direction::Stay].emplace_back(currentStart, size);
        for (int i = 0; i < 3; ++i) {
            fire.m_data[Direction::Stay].emplace_back(nextStart(), size);
        }
        return fire;
    }

    AnimationData BatData()
    {
        const auto size = sf::Vector2i(32, 32);
        const auto initSpace = sf::Vector2i(0, 32);
        auto bat = AnimationData{};
        auto currentStart = initSpace;

        auto nextStart = [&]()
        {
            currentStart.x += size.x;
            return currentStart;
        };
        bat.m_data[Direction::Right].emplace_back(currentStart, size);
        for (int i = 0; i < 3; ++i) {
            bat.m_data[Direction::Right].emplace_back(nextStart(), size);
        }
        currentStart = sf::Vector2i(0, 96);
        bat.m_data[Direction::Left].emplace_back(currentStart, size);
        for (int i = 0; i < 3; ++i) {
            bat.m_data[Direction::Left].emplace_back(nextStart(), size);
        }
        return bat;


    }

    AnimationData fullHeartData()
    {
        const auto size = sf::Vector2i(32, 32);
        const auto initSpace = sf::Vector2i(0, 0);
        auto fullHeart = AnimationData{};
        auto currentStart = initSpace;

        auto nextStart = [&]()
        {
            currentStart.x += size.x;
            return currentStart;
        };
        fullHeart.m_data[Direction::Stay].emplace_back(currentStart, size);
        for (int i = 0; i < 7; ++i) {
            fullHeart.m_data[Direction::Stay].emplace_back(nextStart(), size);
        }
        currentStart = sf::Vector2i(0, 32);
        fullHeart.m_data[Direction::Stay].emplace_back(currentStart, size);
        for (int i = 0; i < 7; ++i) {
            fullHeart.m_data[Direction::Stay].emplace_back(nextStart(), size);
        }
        return fullHeart;
    }
}
Resources::Resources():m_animationData(Max), m_levelCoins(0), m_takenCoins(0), m_singlePlayerMode(false)
{
    m_singlePlayerLevels = readNamesVector("singleLevels.txt"); //read the levels names from the single player levels file
    m_multiPlayerLevels = readNamesVector("multiLevels.txt"); //read the levels names from the multiplayer levels file
    std::vector<std::string> texturesNames = readNamesVector("allTextures.txt"); //read the textures names from allTextures file
    std::vector<std::string> soundsNames = readNamesVector("allSounds.txt"); //read the sounds names from sounds file
    m_textures = getTexturesVector(texturesNames); //get the images textures from the images file
   m_buffers = fillBufferVector(soundsNames);
    m_sounds = fillSoundsVector(m_buffers);
    m_friendlyFire = false;

    try 
    {
        m_font.loadFromFile("arial.ttf");
    }
    catch (const std::exception& e)
    {
        // Handle the specific exception here
        std::cerr << "Failed to load font: " << e.what() << std::endl;
    }

    m_animationData[FirstPlayer] = FirstPlayerData();
    m_animationData[SecondPlayer] = SecondPlayerData();
    m_animationData[EnemySpider] = EnemySpiderData();
    m_animationData[EnemyGhost] = EnemyGhostData();
    m_animationData[Heart] = HeartData();
    m_animationData[Coin] = CoinData();
    m_animationData[EnemyBat] = BatData();
    m_animationData[FullHeart] = fullHeartData();
    m_animationData[Fire] = FireData();
    m_animationData[HealingBall] =HealingBallData();
}
void Resources::playMusic()
{
    m_sounds[background].setLoop(true);// play all the time
    m_sounds[background].setVolume(8);
    m_sounds[background].play();
}
void Resources::playSound(const int index)
{

    m_sounds[index].setVolume(15);
    m_sounds[index].play();
}
Resources& Resources::instance()
{
    static Resources instance;
    return instance;
}

//return vector of textures
const std::vector<sf::Texture>& Resources::getTextures() const
{
    return m_textures;
}

const sf::Font& Resources::getFont() const
{
    return m_font;
}

const std::string& Resources::getSingleLevel(const int index) const
{
    return m_singlePlayerLevels[index];
}

const std::string& Resources::getMultiLevel(const int index) const
{
    return m_multiPlayerLevels[index];
}

//return a vector of strings that read from text
std::vector<std::string> Resources::readNamesVector(const char file_name[]) const
{
    std::ifstream file;
    std::vector<std::string> names;

    //opens the file
    file.open(file_name);
    if (!file.is_open()) {
        std::cerr << "input file not found" << std::endl;
        exit(EXIT_FAILURE);
    }

    //reads the image's name
    for (auto line = std::string(); std::getline(file, line);)
    {
        names.push_back(line);
    }

    file.close();

    return names;
}

//return a vector of textures
std::vector<sf::Texture> Resources::getTexturesVector(const std::vector<std::string>& names) const
{
    std::vector<sf::Texture> textures(names.size());

    try
    {
        for (int i = 0; i < names.size(); i++)
        {
            if (!textures[i].loadFromFile(names[i]))
            {
                throw std::runtime_error("Failed to load texture: " + names[i]);
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "input file not found" << std::endl;
        exit(EXIT_FAILURE);
    }

    return textures;
}

//return a vector of sounds
std::vector<sf::Sound> Resources::fillSoundsVector(const std::vector<sf::SoundBuffer>& buffer) const
{
    std::vector<sf::Sound> sounds(buffer.size());

    for (int i = 0; i < buffer.size(); i++)
        sounds[i].setBuffer(buffer[i]);

    return sounds;
}

//return a vector of buffers
std::vector<sf::SoundBuffer> Resources::fillBufferVector(const std::vector<std::string>& names) const
{
    std::vector<sf::SoundBuffer> buffers(names.size());
    sf::SoundBuffer buffer;

    for (int i = 0; i < names.size(); i++)
    {
        buffers[i].loadFromFile(names[i]);
    }

    return buffers;
}


//to build the map from a text file
std::vector<std::string> Resources::buildMap(const int level)
{
    std::ifstream file;
    std::vector<std::string> map;
    auto time = std::string();

    //if single or multi
    if (getSinglePlayerMode())
    {
        file.open(getSingleLevel(level));
    }
    else
    {
        file.open(getMultiLevel(level));
    }
    try 
    {
        if (!file.is_open()) {
            throw std::invalid_argument("Invalid Path\n");
        }
    }
    catch (std::invalid_argument error) {
        std::cerr << error.what();
        exit(EXIT_FAILURE);
    }

    //reads the map
    for (auto line = std::string(); std::getline(file, line);)
    {
        map.push_back(line);
    }

    file.close();

    return map;
}

void Resources::setFriendlyFire(bool f)
{
    m_friendlyFire = f;
}

bool Resources::getFriendlyFire()const
{
    return m_friendlyFire;
}

void Resources::addTakenCoins()
{
    m_takenCoins++;
}

void Resources::addLevelCoins()
{
    m_levelCoins++;
}

void Resources::addCurrentLevel()
{
    m_currentLevel++;
}

int Resources::getCurrentLevel() const
{
    return m_currentLevel;
}

int Resources::getTakenCoins()const
{
    return m_takenCoins;
}

int Resources::getLevelCoins()const
{
    return m_levelCoins;
}

bool Resources::getLevelWon()const
{
    return m_levelCoins == m_takenCoins;
}

bool Resources::getGameFinished()const
{
    if(m_singlePlayerMode)
        return m_currentLevel == m_singlePlayerLevels.size();
    else
        return m_currentLevel == m_multiPlayerLevels.size();
}

void Resources::setSinglePlayerMode(bool b)
{
    m_singlePlayerMode = b;
    if (b)
        m_numOfPlayers = 1;
    else
        m_numOfPlayers = 2;
}

bool Resources::getSinglePlayerMode()const
{
    return m_singlePlayerMode;
}

void Resources::playerKilled()
{
    m_numOfPlayers--;
}

bool Resources::getLevelLost()const
{
    return m_numOfPlayers == 0;
}

void Resources::resetGame()
{
    m_currentLevel = 0;
    m_takenCoins = 0;
    m_levelCoins = 0;
}

void Resources::resetCoins()
{
    m_takenCoins = 0;
    m_levelCoins = 0;
}

int Resources::getSingleLvlCount() const
{
    return m_singlePlayerLevels.size();
}
int Resources::getMultipleLvlCount() const
{
    return m_multiPlayerLevels.size();
}