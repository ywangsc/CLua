#include <LodePNG/lodepng.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
#include <Lightning/Core/Exceptions.h>
#include <Lightning/Core/Json.h>
#include <Lightning/Core/SharedConstants.h>
#include <Lightning/ImageGeneration/SvgToImageControlFlow.h>
#include <Lightning/Interface/LightningInterface.h>
#include <Lightning/Parsers/CharacterDataParser.h>
#include <Lightning/Parsers/GenerateSingleSvg.h>
#include <Lightning/Utilities/FileUtilities.h>
#include <Lightning/Utilities/XmlUtilities.h>

#include "../lightningTestApp/HTTPDownloader.hpp"

struct DataBuffer {
  unsigned char* buffer = nullptr;
  ~DataBuffer() { free(buffer); };
};

#include "wangyi.h"
#include "wangyiMoho.h"

int main(int argc, char* argv[]) {
  wangyiGenAnimation(
      "/Users/Yiyang.Wang/documents/moho/exported/myGenericBoneExport.txt",  //"/Users/Yiyang.Wang/documents/moho/exported/BitMoho-scene test.moho.txt",
      "/exported/svgs/");
  return 0;

  if (argc < 3) {
    std::cerr << "Please pass the comic and character IDs as arguments!"
              << std::endl;

    exit(1);
  }

  ////// CONFIG: //////
  bool friendmoji = argc == 4;
  constexpr bool enableBackground = false;
  constexpr bool enablePng = false;
  constexpr bool enableWebp = false;
  constexpr bool singleSvg = false;
  constexpr bool generateSvg = true;
  constexpr char svgFileInPath[] = "";
  constexpr int numRuns = 1;
  constexpr int requestScale = 1;

  static_assert(generateSvg || sizeof(svgFileInPath) > 1,
                "Either generate the SVG or provide the file path to one.");

  static_assert(!(singleSvg && (enablePng || enableWebp)),
                "Enabling Png or Webp uses rendering and compositing, which "
                "singleSvg does not support!");
  ////////////////////

  HTTPDownloader downloader;

  std::unique_ptr<std::vector<unsigned char>> pngImageData;
  std::unique_ptr<std::vector<unsigned char>> webpImageData;
  Lightning::GeneratedSVGs generatedSVGs;
  Lightning::Metrics perfMetrics;
  Lightning::RequestData requestData;
  // requestData.

  std::string comicID = std::string(argv[1]);
  std::string characterID = std::string(argv[2]);
  std::string character2ID = friendmoji ? std::string(argv[3]) : "";

  try {
    Lightning::initialize();
  } catch (std::exception& e) {
    exit(1);
  }

  if (generateSvg) {
    // Fetch character data
    requestData.characterData["1"] =
        downloader.downloadJSON(CHARACTER_SERVICE_URL_PREFIX + characterID +
                                CHARACTER_SERVICE_URL_BITMOJI_POSTFIX);
    if (friendmoji) {
      requestData.characterData["2"] =
          downloader.downloadJSON(CHARACTER_SERVICE_URL_PREFIX + character2ID +
                                  CHARACTER_SERVICE_URL_BITMOJI_POSTFIX);
    }

    // Fetch panel data
    const std::string jsonComicData = downloader.downloadJSON(
        COMIC_DATA_URL_PREFIX + comicID + COMIC_DATA_URL_POSTFIX);

    std::cout << "comic data url: "
              << COMIC_DATA_URL_PREFIX + comicID + COMIC_DATA_URL_POSTFIX
              << std::endl;

    rapidjson::Document comicData =
        Lightning::loadJSONFromString(jsonComicData);
    rapidjson::StringBuffer panelData;
    rapidjson::Writer<rapidjson::StringBuffer> panelWriter(panelData);
    comicData["strips"][0]["panels"][0].Accept(panelWriter);
    requestData.isExperimental = true;
    requestData.comicId = comicID;
    requestData.comicFrameData.push_back({
        {Lightning::AssetLayerState::ACTIVE, Lightning::AssetLayerState::ACTIVE,
         Lightning::AssetLayerState::ACTIVE} /* assetLayerStates */,
        "" /* comicImagePath */,
        panelData.GetString(),
        0 /* finishTimeMs */,
        true /* isCharacterKeyframe */
    });
  }
  requestData.scale = requestScale;

  if (enableBackground) {
    std::string scalePostfix = "";
    if (requestScale != 1) {
      scalePostfix = "_" + std::to_string(requestScale);
    }

    std::string fgBgImageUrl = Lightning::FG_BG_IMAGE_URL_PREFIX + comicID +
                               scalePostfix +
                               Lightning::FG_BG_IMAGE_URL_POSTFIX;
    unsigned int w, h;
    DataBuffer dataBuffer;
    const char* backgroundPNGPath = "/tmp/background.png";
    downloader.downloadFile(fgBgImageUrl, backgroundPNGPath);
    unsigned int error =
        lodepng_decode32_file(&dataBuffer.buffer, &w, &h, backgroundPNGPath);
    assert(error == 0);
    std::string backgroundRgbaPath = "/tmp/background_rgba";
    std::ofstream file(backgroundRgbaPath, std::ios::binary);
    file.write((const char*)dataBuffer.buffer, w * h * 4);
    requestData.comicFrameData.front().comicImagePath = backgroundRgbaPath;
  }

  for (int i = 0; i < numRuns; ++i) {
    if (generateSvg) {
      if (singleSvg) {
        generatedSVGs.svgs.push_back(Lightning::generateSingleSVG(requestData));
      } else {
        generatedSVGs = Lightning::generateSVGs(requestData, &perfMetrics);
      }
    } else {
      generatedSVGs.svgs.push_back(Lightning::openFileAsString(svgFileInPath));

      Lightning::SvgParser svgParser;
      using xml_node = rapidxml::xml_node<>;
      xml_node* svgRoot = svgParser.getSvgRootFromString(generatedSVGs.svgs[0]);
      generatedSVGs.width =
          std::atoi(svgRoot->first_attribute("width")->value());
      generatedSVGs.height =
          std::atoi(svgRoot->first_attribute("height")->value());
    }

    if (enablePng) {
      requestData.imageFormat = Lightning::ImageFormat::PNG;
      pngImageData = Lightning::svgToCompressedImage(generatedSVGs, requestData,
                                                     &perfMetrics);
    }
    if (enableWebp) {
      requestData.imageFormat = Lightning::ImageFormat::WEBP;
      webpImageData = Lightning::svgToCompressedImage(
          generatedSVGs, requestData, &perfMetrics);
    }
  }

  if (friendmoji) {
    if (singleSvg) {
      Lightning::saveStringAsFile(
          comicID + "." + characterID + "." + character2ID + ".svg",
          generatedSVGs.svgs[0]);
    } else {
      Lightning::saveStringAsFile(comicID + "." + characterID + "-1.svg",
                                  generatedSVGs.svgs[0]);

      Lightning::saveStringAsFile(comicID + "." + character2ID + "-2.svg",
                                  generatedSVGs.svgs[1]);
    }
  } else {
    Lightning::saveStringAsFile(comicID + "." + characterID + ".svg",
                                generatedSVGs.svgs[0]);
  }

  if (enablePng) {
    Lightning::saveBytesToFile(comicID + "." + characterID + ".png",
                               *pngImageData);
  }

  if (enableWebp) {
    Lightning::saveBytesToFile(comicID + "." + characterID + ".webp",
                               *webpImageData);
  }

  return 0;
}
