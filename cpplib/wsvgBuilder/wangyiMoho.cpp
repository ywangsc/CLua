//
//  wangyi.cpp
//  Lightning
//
//  Created by Yingying Wang on 7/24/18.
//

#include <stdio.h>
#include "wangyiMoho.h"

#include <Lightning/Core/Exceptions.h>
#include <Lightning/Core/Json.h>
#include <Lightning/Core/SharedConstants.h>
#include <Lightning/ImageGeneration/SvgToImageControlFlow.h>
#include <Lightning/Interface/LightningInterface.h>
#include <Lightning/Parsers/CharacterDataParser.h>
#include <Lightning/Parsers/GenerateSingleSvg.h>
#include <Lightning/Utilities/FileUtilities.h>
#include <Lightning/Utilities/XmlUtilities.h>
#include <LodePNG/lodepng.h>

#include "../lightningTestApp/HTTPDownloader.hpp"
  
#include <fstream>
#include <string>


void wangyiSimplified() {
  try {
    Lightning::initialize();
  } catch (std::exception& e) {
    exit(1);
  }

  std::string strComicID = std::string("10227217");
  std::string strCharacterID = std::string("219051060");
  std::string strComicUrl =
      COMIC_DATA_URL_PREFIX + strComicID + COMIC_DATA_URL_POSTFIX;
  std::string strCharacterUrl = CHARACTER_SERVICE_URL_PREFIX + strCharacterID +
                                CHARACTER_SERVICE_URL_BITMOJI_POSTFIX;

  HTTPDownloader downloader;
  const std::string strCharacterJson = downloader.downloadJSON(strCharacterUrl);
  const std::string strComicJson = downloader.downloadJSON(strComicUrl);
  std::cout << "*************comic data url: " << strComicUrl << std::endl
            << "*************character data url: " << strCharacterUrl
            << std::endl;

  rapidjson::Document docComic = Lightning::loadJSONFromString(strComicJson);
  rapidjson::StringBuffer strPanel;
  rapidjson::Writer<rapidjson::StringBuffer> panelWriter(strPanel);
  docComic["strips"][0]["panels"][0].Accept(panelWriter);

  Lightning::PerFrameData perFrameData;
  perFrameData.assetLayerStates = std::vector<Lightning::AssetLayerState>(
      3, Lightning::AssetLayerState::ACTIVE);
  perFrameData.comicImagePath = "";
  perFrameData.jsonPanelData = strPanel.GetString();

  std::ifstream fin(
      "/Users/Yiyang.Wang/Snapchat/Dev/monorepo/rendering/lightning/"
      "wangyiPanel2.txt");
  std::string strPanel2;
  fin >> strPanel2;
  fin.close();
  Lightning::PerFrameData perFrameData2;
  perFrameData2.assetLayerStates = std::vector<Lightning::AssetLayerState>(
      3, Lightning::AssetLayerState::ACTIVE);
  perFrameData2.comicImagePath = "";
  perFrameData2.jsonPanelData = strPanel2;

  Lightning::RequestData requestData;
  requestData.characterData["1"] = strCharacterJson;  //该character
  requestData.isExperimental = true;
  requestData.comicId = strComicID;
  requestData.comicFrameData.push_back(perFrameData);   //每一帧可能不同
  requestData.comicFrameData.push_back(perFrameData2);  //每一帧可能不同

  requestData.scale = 1;

  Lightning::GeneratedSVGs generatedSVGs;
  Lightning::Metrics perfMetrics;
  for (int i = 0; i < 2; ++i) {
    generatedSVGs = Lightning::generateSVGs(requestData, &perfMetrics);
  }
  Lightning::saveStringAsFile(
      "wangyi." + strComicID + "." + strCharacterID + "-1.svg",
      generatedSVGs.svgs[0]);
  Lightning::saveStringAsFile(
      "wangyi." + strComicID + "." + strCharacterID + "-43.svg",
      generatedSVGs.svgs[1]);

  std::ofstream fout(
      "/Users/Yiyang.Wang/Snapchat/Dev/monorepo/rendering/lightning/"
      "wangyiComicJson.txt");
  fout << strComicJson;
  fout.flush();
  fout.close();

  fout.open(
      "/Users/Yiyang.Wang/Snapchat/Dev/monorepo/rendering/lightning/"
      "wangyiCharacterJson.txt");
  fout << strCharacterJson;
  fout.flush();
  fout.close();

  fout.open(
      "/Users/Yiyang.Wang/Snapchat/Dev/monorepo/rendering/lightning/"
      "wangyiPanel.txt");
  fout << strPanel.GetString();
  fout.flush();
  fout.close();
}

