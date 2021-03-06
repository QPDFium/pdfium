// Copyright 2018 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <string>

#include "core/fxge/cfx_folderfontinfo.h"
#include "core/fxge/cfx_fontmapper.h"
#include "core/fxge/cfx_gemodule.h"
#include "core/fxge/fx_font.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "testing/utils/path_service.h"
#include "third_party/base/check.h"

TEST(FXFontTest, PDF_UnicodeFromAdobeName) {
  EXPECT_EQ(static_cast<wchar_t>(0x0000), PDF_UnicodeFromAdobeName("nonesuch"));
  EXPECT_EQ(static_cast<wchar_t>(0x0000), PDF_UnicodeFromAdobeName(""));
  EXPECT_EQ(static_cast<wchar_t>(0x00b6),
            PDF_UnicodeFromAdobeName("paragraph"));
  EXPECT_EQ(static_cast<wchar_t>(0x00d3), PDF_UnicodeFromAdobeName("Oacute"));
  EXPECT_EQ(static_cast<wchar_t>(0x00fe), PDF_UnicodeFromAdobeName("thorn"));
  EXPECT_EQ(static_cast<wchar_t>(0x0384), PDF_UnicodeFromAdobeName("tonos"));
  EXPECT_EQ(static_cast<wchar_t>(0x2022), PDF_UnicodeFromAdobeName("bullet"));
}

TEST(FXFontTest, PDF_AdobeNameFromUnicode) {
  EXPECT_STREQ("", PDF_AdobeNameFromUnicode(0x0000).c_str());
  EXPECT_STREQ("divide", PDF_AdobeNameFromUnicode(0x00f7).c_str());
  EXPECT_STREQ("Lslash", PDF_AdobeNameFromUnicode(0x0141).c_str());
  EXPECT_STREQ("tonos", PDF_AdobeNameFromUnicode(0x0384).c_str());
  EXPECT_STREQ("afii57513", PDF_AdobeNameFromUnicode(0x0691).c_str());
  EXPECT_STREQ("angkhankhuthai", PDF_AdobeNameFromUnicode(0x0e5a).c_str());
  EXPECT_STREQ("Euro", PDF_AdobeNameFromUnicode(0x20ac).c_str());
}

TEST(FXFontTest, ReadFontNameFromMicrosoftEntries) {
  std::string test_data_dir;
  PathService::GetTestDataDir(&test_data_dir);
  DCHECK(!test_data_dir.empty());

  CFX_FontMapper font_mapper(nullptr);

  {
    // |folder_font_info| has to be deallocated before the |font_mapper| or we
    // run into UnownedPtr class issues with ASAN.
    CFX_FolderFontInfo folder_font_info;
    folder_font_info.AddPath(
        (test_data_dir + PATH_SEPARATOR + "font_tests").c_str());

    font_mapper.SetSystemFontInfo(
        CFX_GEModule::Get()->GetPlatform()->CreateDefaultSystemFontInfo());
    ASSERT_TRUE(folder_font_info.EnumFontList(&font_mapper));
  }

  ASSERT_EQ(1u, font_mapper.GetFaceSize());
  ASSERT_EQ("Test", font_mapper.GetFaceName(0));
}
