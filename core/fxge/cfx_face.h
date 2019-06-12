// Copyright 2019 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CORE_FXGE_CFX_FACE_H_
#define CORE_FXGE_CFX_FACE_H_

#include "core/fxcrt/observed_ptr.h"
#include "core/fxcrt/retain_ptr.h"
#include "core/fxge/fx_freetype.h"
#include "third_party/base/span.h"

class CFX_Face : public Retainable, public Observable {
 public:
  static RetainPtr<CFX_Face> New(FT_Library library,
                                 pdfium::span<const FT_Byte> file_span,
                                 FT_Long face_index);

  static RetainPtr<CFX_Face> Open(FT_Library library,
                                  const FT_Open_Args* args,
                                  FT_Long face_index);

  ~CFX_Face() override;

  FXFT_FaceRec* GetRec() { return m_pRec.get(); }

 private:
  explicit CFX_Face(FXFT_FaceRec* pRec);

  ScopedFXFTFaceRec const m_pRec;
};

#endif  // CORE_FXGE_CFX_FACE_H_
