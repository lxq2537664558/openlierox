/////////////////////////////////////////
//
//   OpenLieroX
//
//   Auxiliary Software class library
//
//   based on the work of JasonB
//   enhanced by Dark Charlie and Albert Zeyer
//
//   code under LGPL
//
/////////////////////////////////////////


// Cache system
// Created 7/11/01
// By Jason Boettcher


#include "LieroX.h"
#include "Sounds.h"
#include "Cache.h"
#include "GfxPrimitives.h"
#include "FindFile.h"

std::vector<CCache> Cache;



//////////////////////////////////////
//	      The cache item class
//////////////////////////////////////



///////////////////
// Loads an image, and converts it to the same colour depth as the screen (speed)
SDL_Surface *CCache::LoadImgBPP(const std::string& _file, bool withalpha) {
	Type = CCH_IMAGE;
	Filename = _file;

	// Load the image
	std::string fullfname = GetFullFileName(_file);
	if(fullfname.size() == 0)
		return NULL;
	SDL_Surface* img = IMG_Load(fullfname.c_str());

	if(!img) {
//		printf("CCache::LoadImgBPP: Error loading file: %s\n", Filename.c_str());
		return NULL;
	}

	// Convert the image to the screen's colour depth
	SDL_PixelFormat fmt = *(SDL_GetVideoSurface()->format);
	if (withalpha)  {
		fmt.BitsPerPixel = 32;
		fmt.BytesPerPixel = 4;
		fmt.Rmask = ALPHASURFACE_RMASK;
		fmt.Gmask = ALPHASURFACE_GMASK;
		fmt.Bmask = ALPHASURFACE_BMASK;
		fmt.Amask = ALPHASURFACE_AMASK;
		Image = SDL_ConvertSurface(img, &fmt, iSurfaceFormat | SDL_SRCALPHA);
	} else {
		Image = SDL_ConvertSurface(img, &fmt, iSurfaceFormat);
		ResetAlpha(Image);
	}

	SDL_FreeSurface(img);

	if(!Image) {
		printf("ERROR: LoadImgBPP: cannot create new surface\n");
		return NULL;
	}
	
	return Image;
}



///////////////////
// Load a sample
SoundSample* CCache::LoadSample(const std::string& _file, int maxplaying)
{
	Type = CCH_SOUND;
	Filename = _file;
	
	std::string fullfname = GetFullFileName(Filename);
	if(fullfname.size() == 0)
	{
//		SetError("Error loading sample %s: file not found", _file.c_str());
		return NULL;
	}
	
	// Load the sample
	Sample = LoadSoundSample(fullfname, maxplaying);
	
//	if(Sample)
//		Used = true;
//	else
//		SetError("Error loading sample: %s",_file.c_str());

	return Sample;
}


///////////////////
// Shutdown the cache item
void CCache::Shutdown(void)
{
	//if(!Used)
	//	return;

	switch(Type) {

		// Image
		case CCH_IMAGE:
			if(Image)
				SDL_FreeSurface(Image);
			Image = NULL;
			break;

		// Sample
		case CCH_SOUND:
			if(Sample)
				FreeSoundSample(Sample);
			Sample = NULL;
			break;
	}
}




//////////////////////////////////////
//	      The cache system
//////////////////////////////////////



///////////////////
// Initialize the cache
int InitializeCache(void)
{
	// Allocate the cache
	Cache.clear();

	return true;
}


///////////////////
// Shutdown the cache
void ShutdownCache(void)
{
	if(Cache.empty())
		return;


	for (std::vector<CCache>::iterator it=Cache.begin(); it != Cache.end(); it++)  {
		it->Shutdown();
	}
}


