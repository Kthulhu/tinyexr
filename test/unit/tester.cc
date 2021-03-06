#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <sstream>
#include <fstream>

#define TINYEXR_IMPLEMENTATION
#include "../../tinyexr.h"

// path to https://github.com/openexr/openexr-images
const char *kOpenEXRImagePath = "../../../openexr-images/";

std::string GetPath(const char *basename)
{
  std::string s;
  s = std::string(kOpenEXRImagePath) + std::string(basename);
  return s;
}

TEST_CASE("asakusa", "[Load]") {
  EXRVersion exr_version;
  EXRImage exr_image;
  EXRHeader exr_header;
  const char* err = NULL;
  int ret = ParseEXRVersionFromFile(&exr_version, "../../asakusa.exr");
  REQUIRE(TINYEXR_SUCCESS == ret);

  ret = ParseEXRHeaderFromFile(&exr_header, &exr_version, "../../asakusa.exr", &err);
  REQUIRE(NULL == err);
  REQUIRE(TINYEXR_SUCCESS == ret);
}

TEST_CASE("ScanLines", "[Load]") {
  std::vector<std::string> inputs;
  inputs.push_back("ScanLines/Blobbies.exr");
  inputs.push_back("ScanLines/CandleGlass.exr");
  //inputs.push_back("ScanLines/Cannon.exr"); // Cannon.exr will fail since it uses b44 compression which is not yet supported on TinyEXR.
  inputs.push_back("ScanLines/Desk.exr");
  inputs.push_back("ScanLines/MtTamWest.exr");
  inputs.push_back("ScanLines/PrismsLenses.exr");
  inputs.push_back("ScanLines/StillLife.exr");
  inputs.push_back("ScanLines/Tree.exr");

  for (size_t i = 0; i < inputs.size(); i++) {
    EXRVersion exr_version;
    std::string filepath = GetPath(inputs[i].c_str());
    std::cout << "Loading" << filepath << std::endl;
    int ret = ParseEXRVersionFromFile(&exr_version, filepath.c_str());
    REQUIRE(TINYEXR_SUCCESS == ret);
    REQUIRE(false == exr_version.tiled);
    REQUIRE(false == exr_version.non_image);
    REQUIRE(false == exr_version.multipart);

    EXRVersion version;
    EXRHeader header;
    EXRImage image;
    InitEXRHeader(&header);
    InitEXRImage(&image);

    const char* err;
    ret = ParseEXRHeaderFromFile(&header, &exr_version, filepath.c_str(), &err);
    REQUIRE(TINYEXR_SUCCESS == ret);


    ret= LoadEXRImageFromFile(&image, &header, filepath.c_str(), &err);
    REQUIRE(TINYEXR_SUCCESS == ret);

    FreeEXRHeader(&header);
    FreeEXRImage(&image);
  }
}

TEST_CASE("Chromaticities", "[Load]") {
  std::vector<std::string> inputs;
  inputs.push_back("Chromaticities/Rec709.exr");
  inputs.push_back("Chromaticities/Rec709_YC.exr");
  inputs.push_back("Chromaticities/XYZ.exr");
  inputs.push_back("Chromaticities/XYZ_YC.exr");

  for (size_t i = 0; i < inputs.size(); i++) {
    EXRVersion exr_version;
    std::string filepath = GetPath(inputs[i].c_str());
    std::cout << "Loading" << filepath << std::endl;
    int ret = ParseEXRVersionFromFile(&exr_version, filepath.c_str());
    REQUIRE(TINYEXR_SUCCESS == ret);
    REQUIRE(false == exr_version.tiled);
    REQUIRE(false == exr_version.non_image);
    REQUIRE(false == exr_version.multipart);

    EXRVersion version;
    EXRHeader header;
    EXRImage image;
    InitEXRHeader(&header);
    InitEXRImage(&image);

    const char* err;
    ret = ParseEXRHeaderFromFile(&header, &exr_version, filepath.c_str(), &err);
    REQUIRE(TINYEXR_SUCCESS == ret);


    ret= LoadEXRImageFromFile(&image, &header, filepath.c_str(), &err);
    REQUIRE(TINYEXR_SUCCESS == ret);

    FreeEXRHeader(&header);
    FreeEXRImage(&image);
  }
}

TEST_CASE("TestImages", "[Load]") {
  std::vector<std::string> inputs;
  inputs.push_back("TestImages/AllHalfValues.exr");
  inputs.push_back("TestImages/BrightRings.exr");
  inputs.push_back("TestImages/BrightRingsNanInf.exr");
  //inputs.push_back("TestImages/GammaChart.exr"); // disable since this uses pxr24 compression
  //inputs.push_back("TestImages/GrayRampsDiagonal.exr"); // pxr24
  //inputs.push_back("TestImages/GrayRampsHorizontal.exr"); // pxr24
  //inputs.push_back("TestImages/RgbRampsDiagonal.exr"); // pxr24
  //inputs.push_back("TestImages/SquaresSwirls.exr"); // pxr24
  inputs.push_back("TestImages/WideColorGamut.exr");
  //inputs.push_back("TestImages/WideFloatRange.exr"); // pxr24

  for (size_t i = 0; i < inputs.size(); i++) {
    EXRVersion exr_version;
    std::string filepath = GetPath(inputs[i].c_str());
    std::cout << "Loading" << filepath << std::endl;
    int ret = ParseEXRVersionFromFile(&exr_version, filepath.c_str());
    REQUIRE(TINYEXR_SUCCESS == ret);
    REQUIRE(false == exr_version.tiled);
    REQUIRE(false == exr_version.non_image);
    REQUIRE(false == exr_version.multipart);

    EXRVersion version;
    EXRHeader header;
    EXRImage image;
    InitEXRHeader(&header);
    InitEXRImage(&image);

    const char* err;
    ret = ParseEXRHeaderFromFile(&header, &exr_version, filepath.c_str(), &err);
    REQUIRE(TINYEXR_SUCCESS == ret);


    ret= LoadEXRImageFromFile(&image, &header, filepath.c_str(), &err);
    REQUIRE(TINYEXR_SUCCESS == ret);

    FreeEXRHeader(&header);
    FreeEXRImage(&image);
  }
}

TEST_CASE("LuminanceChroma", "[Load]") {
  std::vector<std::string> inputs;
  //inputs.push_back("LuminanceChroma/CrissyField.exr"); // b44
  //inputs.push_back("LuminanceChroma/Flowers.exr"); // b44
  //inputs.push_back("LuminanceChroma/Garden.exr"); // tiled
  inputs.push_back("LuminanceChroma/MtTamNorth.exr");
  inputs.push_back("LuminanceChroma/StarField.exr");

  for (size_t i = 0; i < inputs.size(); i++) {
    EXRVersion exr_version;
    std::string filepath = GetPath(inputs[i].c_str());
    std::cout << "Loading" << filepath << std::endl;
    int ret = ParseEXRVersionFromFile(&exr_version, filepath.c_str());
    REQUIRE(TINYEXR_SUCCESS == ret);
    REQUIRE(false == exr_version.tiled);
    REQUIRE(false == exr_version.non_image);
    REQUIRE(false == exr_version.multipart);

    EXRVersion version;
    EXRHeader header;
    EXRImage image;
    InitEXRHeader(&header);
    InitEXRImage(&image);

    const char* err;
    ret = ParseEXRHeaderFromFile(&header, &exr_version, filepath.c_str(), &err);
    REQUIRE(TINYEXR_SUCCESS == ret);

    ret= LoadEXRImageFromFile(&image, &header, filepath.c_str(), &err);
    REQUIRE(TINYEXR_SUCCESS == ret);

    FreeEXRHeader(&header);
    FreeEXRImage(&image);
  }
}

TEST_CASE("DisplayWindow", "[Load]") {
  std::vector<std::string> inputs;
  inputs.push_back("DisplayWindow/t01.exr");
  inputs.push_back("DisplayWindow/t02.exr");
  inputs.push_back("DisplayWindow/t03.exr");
  inputs.push_back("DisplayWindow/t04.exr");
  inputs.push_back("DisplayWindow/t05.exr");
  inputs.push_back("DisplayWindow/t06.exr");
  inputs.push_back("DisplayWindow/t07.exr");
  inputs.push_back("DisplayWindow/t08.exr");
  inputs.push_back("DisplayWindow/t09.exr");
  inputs.push_back("DisplayWindow/t10.exr");
  inputs.push_back("DisplayWindow/t11.exr");
  inputs.push_back("DisplayWindow/t12.exr");
  inputs.push_back("DisplayWindow/t13.exr");
  inputs.push_back("DisplayWindow/t14.exr");
  inputs.push_back("DisplayWindow/t15.exr");
  inputs.push_back("DisplayWindow/t16.exr");

  for (size_t i = 0; i < inputs.size(); i++) {
    EXRVersion exr_version;
    std::string filepath = GetPath(inputs[i].c_str());
    std::cout << "Loading" << filepath << std::endl;
    int ret = ParseEXRVersionFromFile(&exr_version, filepath.c_str());
    REQUIRE(TINYEXR_SUCCESS == ret);
    REQUIRE(false == exr_version.tiled);
    REQUIRE(false == exr_version.non_image);
    REQUIRE(false == exr_version.multipart);

    EXRVersion version;
    EXRHeader header;
    EXRImage image;
    InitEXRHeader(&header);
    InitEXRImage(&image);

    const char* err;
    ret = ParseEXRHeaderFromFile(&header, &exr_version, filepath.c_str(), &err);
    REQUIRE(TINYEXR_SUCCESS == ret);

    ret= LoadEXRImageFromFile(&image, &header, filepath.c_str(), &err);
    REQUIRE(TINYEXR_SUCCESS == ret);

    FreeEXRHeader(&header);
    FreeEXRImage(&image);
  }
}


TEST_CASE("Tiles/GoldenGate.exr", "[Version]") {
  EXRVersion exr_version;
  std::string filepath = GetPath("Tiles/GoldenGate.exr");
  int ret = ParseEXRVersionFromFile(&exr_version, filepath.c_str());
  REQUIRE(TINYEXR_SUCCESS == ret);
  REQUIRE(true == exr_version.tiled);
}

TEST_CASE("Tiles/GoldenGate.exr|Load", "[Load]") {
  EXRVersion exr_version;
  std::string filepath = GetPath("Tiles/GoldenGate.exr");
  int ret = ParseEXRVersionFromFile(&exr_version, filepath.c_str());
  REQUIRE(TINYEXR_SUCCESS == ret);
  REQUIRE(true == exr_version.tiled);
  REQUIRE(false == exr_version.non_image);
  REQUIRE(false == exr_version.multipart);

  EXRVersion version;
  EXRHeader header;
  EXRImage image;
  InitEXRHeader(&header);
  InitEXRImage(&image);

  const char* err;
  ret = ParseEXRHeaderFromFile(&header, &exr_version, filepath.c_str(), &err);
  REQUIRE(TINYEXR_SUCCESS == ret);


  ret= LoadEXRImageFromFile(&image, &header, filepath.c_str(), &err);
  REQUIRE(TINYEXR_SUCCESS == ret);

  FreeEXRHeader(&header);
  FreeEXRImage(&image);
}

TEST_CASE("LuminanceChroma/Garden.exr|Load", "[Load]") {
  EXRVersion exr_version;
  std::string filepath = GetPath("LuminanceChroma/Garden.exr");
  int ret = ParseEXRVersionFromFile(&exr_version, filepath.c_str());
  REQUIRE(TINYEXR_SUCCESS == ret);
  REQUIRE(true == exr_version.tiled);
  REQUIRE(false == exr_version.non_image);
  REQUIRE(false == exr_version.multipart);

  EXRVersion version;
  EXRHeader header;
  EXRImage image;
  InitEXRHeader(&header);
  InitEXRImage(&image);

  const char* err;
  ret = ParseEXRHeaderFromFile(&header, &exr_version, filepath.c_str(), &err);
  REQUIRE(TINYEXR_SUCCESS == ret);


  ret= LoadEXRImageFromFile(&image, &header, filepath.c_str(), &err);
  REQUIRE(TINYEXR_SUCCESS == ret);

  FreeEXRHeader(&header);
  FreeEXRImage(&image);
}


TEST_CASE("Tiles/Ocean.exr", "[Load]") {
  EXRVersion exr_version;
  std::string filepath = GetPath("Tiles/Ocean.exr");
  int ret = ParseEXRVersionFromFile(&exr_version, filepath.c_str());
  REQUIRE(TINYEXR_SUCCESS == ret);
  REQUIRE(true == exr_version.tiled);
  REQUIRE(false == exr_version.non_image);
  REQUIRE(false == exr_version.multipart);

  EXRVersion version;
  EXRHeader header;
  EXRImage image;
  InitEXRHeader(&header);
  InitEXRImage(&image);

  const char* err;
  ret = ParseEXRHeaderFromFile(&header, &exr_version, filepath.c_str(), &err);
  REQUIRE(TINYEXR_SUCCESS == ret);


  ret= LoadEXRImageFromFile(&image, &header, filepath.c_str(), &err);
  REQUIRE(TINYEXR_SUCCESS == ret);

  FreeEXRHeader(&header);
  FreeEXRImage(&image);
}

#if 0 // Spirals.exr uses pxr24 compression
TEST_CASE("Tiles/Spirals.exr", "[Load]") {
  EXRVersion exr_version;
  std::string filepath = GetPath("Tiles/Spirals.exr");
  int ret = ParseEXRVersionFromFile(&exr_version, filepath.c_str());
  REQUIRE(TINYEXR_SUCCESS == ret);
  REQUIRE(true == exr_version.tiled);
  REQUIRE(false == exr_version.non_image);
  REQUIRE(false == exr_version.multipart);

  EXRVersion version;
  EXRHeader header;
  EXRImage image;
  InitEXRHeader(&header);
  InitEXRImage(&image);

  const char* err;
  ret = ParseEXRHeaderFromFile(&header, &exr_version, filepath.c_str(), &err);
  REQUIRE(TINYEXR_SUCCESS == ret);


  ret= LoadEXRImageFromFile(&image, &header, filepath.c_str(), &err);
  REQUIRE(TINYEXR_SUCCESS == ret);

  FreeEXRHeader(&header);
  FreeEXRImage(&image);
}
#endif

TEST_CASE("Beachball/multipart.0001.exr", "[Version]") {
  EXRVersion exr_version;
  std::string filepath = GetPath("Beachball/multipart.0001.exr");
  int ret = ParseEXRVersionFromFile(&exr_version, filepath.c_str());
  REQUIRE(TINYEXR_SUCCESS == ret);
  REQUIRE(true == exr_version.multipart);

  EXRHeader *headers;
}

TEST_CASE("Beachball/multipart.0001.exr|Load", "[Load]") {
  EXRVersion exr_version;
  std::string filepath = GetPath("Beachball/multipart.0001.exr");
  int ret = ParseEXRVersionFromFile(&exr_version, filepath.c_str());
  REQUIRE(TINYEXR_SUCCESS == ret);
  REQUIRE(true == exr_version.multipart);

  EXRHeader **exr_headers; // list of EXRHeader pointers.
  int num_exr_headers;
  const char* err;

  ret = ParseEXRMultipartHeaderFromFile(&exr_headers, &num_exr_headers, &exr_version, filepath.c_str(), &err);
  REQUIRE(TINYEXR_SUCCESS == ret);

  REQUIRE(10 == num_exr_headers);

  std::vector<EXRImage> images(num_exr_headers);
  for (int i =0; i < num_exr_headers; i++) {
    InitEXRImage(&images[i]);
  }

  ret = LoadEXRMultipartImageFromFile(&images.at(0), const_cast<const EXRHeader**>(exr_headers), num_exr_headers, filepath.c_str(), &err);
  REQUIRE(TINYEXR_SUCCESS == ret);

  for (int i =0; i < num_exr_headers; i++) {
    FreeEXRImage(&images.at(i));
  }

  for (int i =0; i < num_exr_headers; i++) {
    FreeEXRHeader(exr_headers[i]);
    free(exr_headers[i]);
  }
  free(exr_headers);
}

TEST_CASE("Beachbal multiparts", "[Load]") {
  int num = 8;
  char buf[1024];
  for (int i = 0; i < num+1; i++) {
    sprintf(buf, "Beachball/multipart.%04d.exr", i);
    EXRVersion exr_version;
    std::string filepath = GetPath(buf);
    int ret = ParseEXRVersionFromFile(&exr_version, filepath.c_str());

    if (i == 0) { // multipart.0000.exr does not exist.
      REQUIRE(TINYEXR_ERROR_CANT_OPEN_FILE == ret);
      continue;
    }

    REQUIRE(TINYEXR_SUCCESS == ret);
    REQUIRE(true == exr_version.multipart);

    EXRHeader **exr_headers; // list of EXRHeader pointers.
    int num_exr_headers;
    const char* err;

    ret = ParseEXRMultipartHeaderFromFile(&exr_headers, &num_exr_headers, &exr_version, filepath.c_str(), &err);
    REQUIRE(TINYEXR_SUCCESS == ret);

    REQUIRE(10 == num_exr_headers);

    std::vector<EXRImage> images(num_exr_headers);
    for (int i =0; i < num_exr_headers; i++) {
      InitEXRImage(&images[i]);
    }

    ret = LoadEXRMultipartImageFromFile(&images.at(0), const_cast<const EXRHeader**>(exr_headers), num_exr_headers, filepath.c_str(), &err);
    REQUIRE(TINYEXR_SUCCESS == ret);

    for (int i =0; i < num_exr_headers; i++) {
      FreeEXRImage(&images.at(i));
    }

    for (int i =0; i < num_exr_headers; i++) {
      FreeEXRHeader(exr_headers[i]);
      free(exr_headers[i]);
    }
    free(exr_headers);
  }
}

TEST_CASE("Beachbal singleparts", "[Load]") {
  int num = 8;
  char buf[1024];
  for (int i = 0; i < num+1; i++) {
    sprintf(buf, "Beachball/singlepart.%04d.exr", i);
    EXRVersion exr_version;
    std::string filepath = GetPath(buf);
    int ret = ParseEXRVersionFromFile(&exr_version, filepath.c_str());

    if (i == 0) { // multipart.0000.exr does not exist.
      REQUIRE(TINYEXR_ERROR_CANT_OPEN_FILE == ret);
      continue;
    }

    REQUIRE(TINYEXR_SUCCESS == ret);
    REQUIRE(false == exr_version.tiled);
    REQUIRE(false == exr_version.non_image);
    REQUIRE(false == exr_version.multipart);

    EXRVersion version;
    EXRHeader header;
    EXRImage image;
    InitEXRHeader(&header);
    InitEXRImage(&image);

    const char* err;
    ret = ParseEXRHeaderFromFile(&header, &exr_version, filepath.c_str(), &err);
    REQUIRE(TINYEXR_SUCCESS == ret);


    ret= LoadEXRImageFromFile(&image, &header, filepath.c_str(), &err);
    REQUIRE(TINYEXR_SUCCESS == ret);

    REQUIRE(image.tiles == NULL);
    REQUIRE(image.images);

    FreeEXRHeader(&header);
    FreeEXRImage(&image);
  }
}

