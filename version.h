#define MAJOR_VERSION_STR "17"
#define MAJOR_VERSION_INT 17

#define SUB_VERSION_STR "2"
#define SUB_VERSION_INT 2

#define RELEASE_NUMBER_STR "0"
#define RELEASE_NUMBER_INT 0

#define BUILD_NUMBER_STR "0" // Build number to be sure that each result could identified.
#define BUILD_NUMBER_INT 0

// Version with build number (example "1.0.3.342")
#define FULL_VERSION_STR MAJOR_VERSION_STR "." SUB_VERSION_STR "." RELEASE_NUMBER_STR "." BUILD_NUMBER_STR

// Version without build number (example "1.0.3")
#define VERSION_STR MAJOR_VERSION_STR "." SUB_VERSION_STR "." RELEASE_NUMBER_STR

#define stringOriginalFilename	"StudioLinkOnAir.dll"
#if PLATFORM_64
#define stringFileDescription	"StudioLink OnAir Plugin (64Bit)"
#else
#define stringFileDescription	"StudioLink OnAir Plugin"
#endif
#define stringCompanyName		"IT-Service Sebastian Reimers\0"
#define stringLegalCopyright	"2017 IT-Service Sebastian Reimers"
#define stringLegalTrademarks	"VST is a trademark of Steinberg Media Technologies GmbH"
