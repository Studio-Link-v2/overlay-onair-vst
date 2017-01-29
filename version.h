#define MAJOR_VERSION_STR "16"
#define MAJOR_VERSION_INT 16

#define SUB_VERSION_STR "12"
#define SUB_VERSION_INT 12

#define RELEASE_NUMBER_STR "1"
#define RELEASE_NUMBER_INT 1

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
