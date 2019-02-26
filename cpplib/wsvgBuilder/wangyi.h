//
//  wangyi.h
//  Lightning
//
//  Created by Yingying Wang on 7/16/18.
//

#ifndef wangyi_h
#define wangyi_h

#endif /* wangyi_h */

using namespace std;
#include <vector> 

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <utility>



/*
 switch layer
 brow R: shock,mad,sad,happy,neutral
 brow L: shock,mad,sad,happy,neutral
 eyelid R: shock,mad,sad,happy,neutral [1-5]
 eyelid L: shock,mad,sad,happy,neutral [1-5]
 eye R: shock,mad,sad,happy,neutral
 eye L: shock,mad,sad,happy,neutral
 mouth: shock,frown,happy,neutral [1-4]
 
*/


void wangyiGetJson(std::string& strCharacterJson, std::string& strComicJson, std::string& strPanelTxt); 
void wangyiGenAnimation(std::string strInputPath, std::string strOutputPath);


#define BONE_B1 0
#define BONE_SP1 1
#define BONE_SP2 2
#define BONE_NECK 3
#define BONE_HEAD 4

#define BONE_B21 5
#define BONE_BICEP_R 6
#define BONE_FORE_R 7
#define BONE_HAND_R 8

#define BONE_B20 9
#define BONE_BICEP_L 10
#define BONE_FORE_L 11
#define BONE_HAND_L 12

#define BONE_B19 13
#define BONE_THIGH_R 14
#define BONE_SHIN_R 15
#define BONE_FOOT_R 16
#define BONE_TOE_R 17

#define BONE_THIGH_L 18
#define BONE_SHIN_L 19
#define BONE_FOOT_L 20
#define BONE_TOE_L 21


//holy shit, this is another bone settings
#define B2_root 0//skip
#define B2_pelvis 1
#define B2_Torso_Bone 2
//neck_bone 16
//head does not exist

#define B2_bicep_left 3
#define B2_forearm_left 4
#define B2_hand_left 5

#define B2_bicep_right 6
#define B2_forearm_right 7
#define B2_hand_right 8

#define B2_thigh_left 9
#define B2_shin_left 10
#define B2_foot_left 11

#define B2_thigh_right 12
#define B2_shin_right 13
#define B2_foot_rght 14

#define B2_Body_Size 15
#define B2_neck_bone 16
#define B2_Torso_Smart_Bone 17
#define B2_Hand_Positions_Right 18
#define B2_Hand_Positions_Left 19
#define B2_Foot_Pose_Left 20
#define B2_Foot_Pose_Right 21




struct BimojiBoneDOF
{
    static std::string s_strDOFName[22];
    static std::string s_strDOFName_B2[22];
    std::string m_strName;
    int m_dIndex;

    float m_fPosX;
    float m_fPosY;
    float m_fRotA;
};

struct BimojiSwitchLayerDOF
{
    /* value from MOHO: =========================================================
     mouth: shock,frown,happy,neutral [1-4]
     eye R: shock,mad,sad,happy,neutral
     eyelid R: shock,mad,sad,happy,neutral [1-5]
     eye L: shock,mad,sad,happy,neutral
     eyelid L: shock,mad,sad,happy,neutral [1-5]
     brow L: shock,mad,sad,happy,neutral
     brow R: shock,mad,sad,happy,neutral
     
     example:  
     mouth:happy 2
     eye R:happy
     eyelid R:sad 5
     eye L:happy
     eyelid L:sad 5
     brow L:sad
     brow R:sad
     */
    
    /*bimoji =======================================================================
     "mouth": 4, // mouth emotion
     1 = neutral
     2 = happy
     *3 = sad or angry*
     4 = surprised
     
     "lipsync": 3, // mouth open state
     Values for mouth states of openness:
     1 = mouth closed
     2 = teeth showing
     3 = open
     4 = open wide
     
     "eye_R": 1, // right eye emotion
     "eye_L": 1, // left eye emotion
     "brow_R": 1, // right eyebrow emotion
     "brow_L": 1, // left eyebrow emotion
     1 = neutral
     2 = happy
     3 = sad
     4 = angry
     5 = surprised
     
     "lids": [3,3] // eyelids open or closed [left, right]
     1 = wide open (no visible eyelids)
     2 = top lids partially closed
     3 = bottom lids partially closed
     4 = top and bottom lids partially closed (squinting)
     5 = top and bottom lids fully closed

     */
    std::string m_strName;
    std::string m_strValue;
    int m_dIndex;
    
    void UpdateEmotionState(); 
    int m_dEmotion;
    int m_dState;
    
};

struct CameraSettings
{
    float m_fAspect;
    float m_fDocHeight = 400;
    float m_fDocWidth = 400;
    
    float m_fPosX;
    float m_fPosY;
    float m_fPosZ;
    float m_fZoom;
    float m_fRoll;
    float m_fTilt;
    float m_fPan;
    
    void GetPointOfInterestInPixel(float& x, float& y, float& z);
    void GetProjectionPos(float& x, float& y, float& z);
    float GetProjectionFactor(float fLayerZ = 0);
};

struct LayerTransform
{
    float m_fPosX = 0;
    float m_fPosY = 0;
    float m_fPosZ = 0;
    
    float m_fRotX = 0;
    float m_fRotY = 0;
    float m_fRotZ = 0;
    
    float m_fScaleX = 1;
    float m_fScaleY = 1;
    float m_fScaleZ = 1;
    
    float m_fOriginX = 0;
    float m_fOriginY = 0; 
};

struct BimojiSequence;
struct BimojiFrame
{
    CameraSettings m_cam;
    LayerTransform m_layerTrans;
    
    BimojiBoneDOF m_arBoneDOF[22];
    BimojiSwitchLayerDOF m_arSwitchLayerDOF[7];
    
    BimojiSequence* m_pSeq = NULL;
    
    int m_dBodyOrientation = 1;
    int m_dHeadOrientation = 1;
    
    std::string getAnglesString();
    std::string getAnglesString_B2();
    std::string GenPanelString(std::string strPanelBase);
    std::string GenPanelString_B2(std::string strPanelBase);
    void GetRootPos(float& x, float& y);
    void GetRootAngle(float&a);
};

struct BimojiAction
{
    std::string m_strActionName;
    std::map<std::string, std::vector<float>> m_mapChannel;
    std::pair<float,float> GetActionValue(float fSmartBoneValue, std::string strActionName, std::string strDOFName);
};
struct BimojiSequence
{
    std::vector<BimojiFrame> m_arFrame;
    void LoadAnimationFromMohoExport(std::string strInputPath);
    void LoadAnimationFromMohoExportByFrame(std::string strInputPath);
    void LoadAnimationFromMohoExportByFrame_B2(std::string strInputPath);
    void GenSVGSequence(std::string strOutputPath);
    
    //smart actions
    std::map<std::string, BimojiAction> m_mapAction;
    std::pair<float, float> GetActionValue(float fSmartBoneValue, std::string strActionName, std::string strDOFName);
};


