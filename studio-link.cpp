#include "studio-link.h"
#include <pthread.h>
#include "re/re.h"
#include "baresip.h"

#define DEFAULT_PROG "Default"
#define UNIQUE_ID 'studiolinkonair'

#define EFFECT_NAME "StudioLinkOnAir"
#define PRODUCT_STRING "StudioLinkOnAir"
#define VENDOR_STRING "IT-Service Sebastian Reimers"
#define VENDOR_VERSION 1

#define MAX_GAIN 1

pthread_t tid;
bool running = false;


static void ua_exit_handler(void *arg)
{
	(void)arg;
	debug("ua exited -- stopping main runloop\n");

	/* The main run-loop can be stopped now */
	re_cancel();
}

AudioEffect* createEffectInstance(audioMasterCallback audioMaster)
{
	return new vstplugin (audioMaster);
}

// Constructor
vstplugin::vstplugin(audioMasterCallback audiomaster)
: AudioEffectX(audioMaster, 1,3)
{
	setNumInputs(2);
	setNumOutputs(2);
	setUniqueID(UNIQUE_ID);
	canProcessReplacing();

	resume();

	vst_strncpy(programName,DEFAULT_PROG,kVstMaxProgNameLen);

	if (!running) {
		(void)sys_coredump_set(true);
		libre_init();
		conf_configure();
		baresip_init(conf_config(), false);
		ua_init("baresip v" BARESIP_VERSION " (" ARCH "/" OS ")",
				true, true, true, false);
		conf_modules();
		uag_set_exit_handler(ua_exit_handler, NULL);
		pthread_create(&tid, NULL, (void*(*)(void*))&re_main, NULL);
		running = true;
	}
	gain = 1;

}
// Destructor
vstplugin::~vstplugin()
{
	if (running) {
		ua_stop_all(false);
		sys_msleep(1200);
		ua_close();
		conf_close();
		baresip_close();
		mod_close();
		libre_close();
		tmr_debug();
		mem_debug();
		running = false;
	}
}

// Processing
void vstplugin::processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames)
{
	float *input0 = inputs[0];
	float *output0 = outputs[0];
	float *input1 = inputs[1];
	float *output1 = outputs[1];

	effectlive_src(input0, input1, sampleFrames);
}

//Parameters
void vstplugin::setParameter(VstInt32 index, float value)
{
        gain = value*MAX_GAIN;
}

float vstplugin::getParameter(VstInt32 index)
{
        float param = 0.0;
        param = gain/MAX_GAIN;
        return param;
}

void vstplugin::getParameterName(VstInt32 index, char* label)
{
        vst_strncpy(label,"Gain",kVstMaxParamStrLen);
}

void vstplugin::getParameterDisplay(VstInt32 index, char* text)
{
        dB2string(gain, text, kVstMaxParamStrLen);
}

void vstplugin::getParameterLabel(VstInt32 index, char* label)
{
        vst_strncpy(label, "dB", kVstMaxParamStrLen);
}



// Plugin name set/get
void vstplugin::setProgramName(char* name)
{
	vst_strncpy(programName, name, kVstMaxProgNameLen);
}
void vstplugin::getProgramName(char* name)
{
	vst_strncpy(name, programName, kVstMaxProgNameLen);
}

//VST host functions
bool vstplugin::getEffectName(char* name) {
    vst_strncpy (name, EFFECT_NAME, kVstMaxEffectNameLen);
    return true;
}
bool vstplugin::getProductString(char* text) {
    vst_strncpy (text, PRODUCT_STRING, kVstMaxProductStrLen);
    return true;
}
bool vstplugin::getVendorString(char* text) {
    vst_strncpy (text, VENDOR_STRING, kVstMaxVendorStrLen);
    return true;
}
VstInt32 vstplugin::getVendorVersion() {
    return VENDOR_VERSION;
}
