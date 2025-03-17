// for potential windows support

#if defined(_WIN32)
// Home path definer <windows>
#define HOME_PATH "C:/"
#define DATA_DIRECTORY "GAMEPI/"
#else
/// Home path definer <linux>
#define HOME_PATH std::string(std::getenv("HOME"))
#define DATA_DIRECTORY ".GAMEPI/"
#endif

#define DEFAULT_RESOLUTION {800, 600}
#define FRAMES_LIMIT 30

#define LOGO_ASSET_NAME "GamePI_Icon"
