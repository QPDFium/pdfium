// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef XFA_FXFA_PARSER_CXFA_DOCUMENT_BUILDER_H_
#define XFA_FXFA_PARSER_CXFA_DOCUMENT_BUILDER_H_

#include <memory>
#include <utility>

#include "core/fxcrt/fx_string.h"
#include "core/fxcrt/retain_ptr.h"
#include "xfa/fxfa/fxfa_basic.h"

class CFX_XMLDocument;
class CFX_XMLNode;
class CXFA_Document;
class CXFA_Node;
class CFX_XMLInstruction;

class CXFA_DocumentBuilder {
 public:
  explicit CXFA_DocumentBuilder(CXFA_Document* pFactory);
  ~CXFA_DocumentBuilder();

  CFX_XMLNode* Build(std::unique_ptr<CFX_XMLDocument> pXML);
  bool BuildDocument(std::unique_ptr<CFX_XMLDocument> pXML,
                     XFA_PacketType ePacketID);
  std::unique_ptr<CFX_XMLDocument> GetXMLDoc() { return std::move(xml_doc_); }

  void ConstructXFANode(CXFA_Node* pXFANode, CFX_XMLNode* pXMLNode);
  CXFA_Node* GetRootNode() const;

 private:
  CXFA_Node* ParseAsXDPPacket(CFX_XMLNode* pXMLDocumentNode,
                              XFA_PacketType ePacketID);
  CXFA_Node* ParseAsXDPPacket_XDP(CFX_XMLNode* pXMLDocumentNode);
  CXFA_Node* ParseAsXDPPacket_Config(CFX_XMLNode* pXMLDocumentNode);
  CXFA_Node* ParseAsXDPPacket_Template(CFX_XMLNode* pXMLDocumentNode);
  CXFA_Node* ParseAsXDPPacket_Form(CFX_XMLNode* pXMLDocumentNode);
  CXFA_Node* ParseAsXDPPacket_Data(CFX_XMLNode* pXMLDocumentNode);
  CXFA_Node* ParseAsXDPPacket_LocaleConnectionSourceSet(
      CFX_XMLNode* pXMLDocumentNode,
      XFA_PacketType packet_type,
      XFA_Element element);
  CXFA_Node* ParseAsXDPPacket_Xdc(CFX_XMLNode* pXMLDocumentNode);
  CXFA_Node* ParseAsXDPPacket_User(CFX_XMLNode* pXMLDocumentNode);
  CXFA_Node* NormalLoader(CXFA_Node* pXFANode,
                          CFX_XMLNode* pXMLDoc,
                          XFA_PacketType ePacketID,
                          bool bUseAttribute);
  CXFA_Node* DataLoader(CXFA_Node* pXFANode,
                        CFX_XMLNode* pXMLDoc,
                        bool bDoTransform);
  void ParseContentNode(CXFA_Node* pXFANode,
                        CFX_XMLNode* pXMLNode,
                        XFA_PacketType ePacketID);
  void ParseDataValue(CXFA_Node* pXFANode,
                      CFX_XMLNode* pXMLNode,
                      XFA_PacketType ePacketID);
  void ParseDataGroup(CXFA_Node* pXFANode,
                      CFX_XMLNode* pXMLNode,
                      XFA_PacketType ePacketID);
  void ParseInstruction(CXFA_Node* pXFANode,
                        CFX_XMLInstruction* pXMLInstruction,
                        XFA_PacketType ePacketID);

  UnownedPtr<CXFA_Document> m_pFactory;
  std::unique_ptr<CFX_XMLDocument> xml_doc_;
  // TODO(dsinclair): Figure out who owns this.
  CXFA_Node* m_pRootNode = nullptr;
  size_t m_ExecuteRecursionDepth = 0;
};

#endif  // XFA_FXFA_PARSER_CXFA_DOCUMENT_BUILDER_H_